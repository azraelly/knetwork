#include "StdAfx.h"
#include ".\rcvfactory.h"

CRcvFactory::CRcvFactory(const ACE_TCHAR *name,
						 int log_level,
						 unsigned int min_cache_size,
						 unsigned int max_cache_size)
: ProtocolFactory_T<CRcvProtocol> (name, 
								   log_level,
								   min_cache_size,
								   max_cache_size)
, m_pSndFrameBuffer(NULL)
, m_nSndFrameBufferLen(0)
{
}

CRcvFactory::~CRcvFactory(void)
{
	ReleaseConnections();
}

void CRcvFactory::OnChannelOpened(CRcvProtocol* pRcvProtocol)
{
	OnChannelClosed(pRcvProtocol);
	{
		CAutoLock l(&m_CritSecMapRcvProtocol);
		m_MapRcvProtocol.insert(MapRcvProtocol::value_type((unsigned long)pRcvProtocol,pRcvProtocol));
	}
}

void CRcvFactory::OnChannelClosed(CRcvProtocol* pRcvProtocol)
{
	CAutoLock l(&m_CritSecMapRcvProtocol);
	MapRcvProtocol::iterator it = m_MapRcvProtocol.find((unsigned long)pRcvProtocol);
	if(it != m_MapRcvProtocol.end())
	{
		m_MapRcvProtocol.erase(it);
	}
}

bool CRcvFactory::OnReadCompleted(CRcvProtocol* pRcvProtocol,const char* pData,int nLen)
{
	CCmdPacket* pCmdPacket = new CCmdPacket(pData,nLen);
	if(pCmdPacket)
	{
		pCmdPacket->SetFromUID((unsigned long)pRcvProtocol);
		{
			CAutoLock l(&m_CritSecListCmdPacket);
			m_ListCmdPacket.push_back(pCmdPacket);
		}
		return true;
	}
	
	return false;
}

bool CRcvFactory::ProcessFrameDataPool(void)
{
	CCmdPacket* pCmdPacket = NULL;
	{
		CAutoLock l(&m_CritSecListCmdPacket);
		if(m_ListCmdPacket.size() == 0)
		{
			return false;
		}
		pCmdPacket = (CCmdPacket*)m_ListCmdPacket.front();
		m_ListCmdPacket.pop_front();
	}
	if(pCmdPacket)
	{
		SendToRcvProtocol(*pCmdPacket);
		
		delete pCmdPacket;
		pCmdPacket = NULL;

		return true;
	}

	return false;
}

void CRcvFactory::SendToRcvProtocol(CCmdPacket& rCmdPacket)
{
	unsigned long ulSessionID = rCmdPacket.GetFromUID();

	char* pData = NULL;
	unsigned int nLen = rCmdPacket.GetData(&pData);
	if(pData == NULL || nLen == 0)
	{
		return;
	}

	if(m_nSndFrameBufferLen < nLen + 1024)
	{
		m_nSndFrameBufferLen = nLen + 1024;
		if(m_pSndFrameBuffer)
		{
			delete []m_pSndFrameBuffer;
			m_pSndFrameBuffer = NULL;
		}
		m_pSndFrameBuffer = new char[m_nSndFrameBufferLen];
		if(m_pSndFrameBuffer == NULL)
		{
			m_nSndFrameBufferLen = 0;
		}
	}

	if(m_pSndFrameBuffer)
	{
		*(unsigned long*)m_pSndFrameBuffer = htonl(nLen);
		memcpy(m_pSndFrameBuffer + 4,pData,nLen);

		CAutoLock l(&m_CritSecMapRcvProtocol);
		MapRcvProtocol::iterator it = m_MapRcvProtocol.begin();
		while(it != m_MapRcvProtocol.end())
		{
			CRcvProtocol* pRcvProtocol = it->second;
			if(pRcvProtocol && (unsigned long)pRcvProtocol != ulSessionID )
			{
				pRcvProtocol->SendData(m_pSndFrameBuffer,nLen + 4);
			}
			++it;
		}
	}

	if(pData)
	{
		delete []pData;
		pData = NULL;
	}
}

void CRcvFactory::ReleaseConnections(void)
{
	{
		CAutoLock l(&m_CritSecMapRcvProtocol);
		m_MapRcvProtocol.clear();
	}

	if(m_pSndFrameBuffer)
	{
		delete []m_pSndFrameBuffer;
		m_pSndFrameBuffer = NULL;
	}
	m_nSndFrameBufferLen = 0;

	{
		CAutoLock l(&m_CritSecListCmdPacket);
		while(m_ListCmdPacket.size() > 0)
		{
			CCmdPacket* pCmdPacket = (CCmdPacket*)m_ListCmdPacket.front();
			m_ListCmdPacket.pop_front();
			if(pCmdPacket)
			{
				delete pCmdPacket;
				pCmdPacket = NULL;
			}
		}
	}
}

int CRcvFactory::GetBufferCount(void)
{
	int nCount = 0;
	{
		CAutoLock l(&m_CritSecMapRcvProtocol);
		MapRcvProtocol::iterator it = m_MapRcvProtocol.begin();
		while(it != m_MapRcvProtocol.end())
		{
			CRcvProtocol* pRcvProtocol = it->second;
			if(pRcvProtocol)
			{
				nCount += pRcvProtocol->GetBufferCount();
			}
			++it;
		}
	}
	return nCount;
}