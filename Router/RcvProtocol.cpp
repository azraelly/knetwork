#include "StdAfx.h"
#include "RcvProtocol.h"
#include "RcvFactory.h"

CRcvProtocol::CRcvProtocol(ProtocolFactory& factory)
: Protocol(factory)
, m_pAsynchChannel(NULL)
{
}

CRcvProtocol::~CRcvProtocol(void)
{
	ReleaseConnections();
}

void CRcvProtocol::reset()
{
    CRcvFactory& RcvFactory = static_cast <CRcvFactory&> (this->get_protocol_factory());
	RcvFactory.OnChannelClosed(this);

	ReleaseConnections();
}

int CRcvProtocol::on_channel_opened(AsynchChannel *channel)
{
    channel->enable_write_notifications ();  // this is not

	{
		CAutoLock l(&m_CritSecAsynchChannel);
		m_pAsynchChannel = channel;
	}

    CRcvFactory& RcvFactory = static_cast <CRcvFactory&> (this->get_protocol_factory ());
	RcvFactory.OnChannelOpened(this);

	return 0;
}

int CRcvProtocol::on_read_completed (AsynchChannel *channel,const char* data,size_t length)
{	
	if(CFrame::OnReceivedData(data,length) == false)
	{
		return -1;
	}
	return length;
}

int CRcvProtocol::on_write_completed (Terabit::AsynchChannel *channel)
{
	int nRet = 0;
	CDataBuffer* pDataBuffer = CBufferPool::GetDataBuffer();
	if(pDataBuffer)
	{
		if(StartWrite(pDataBuffer->GetData(),pDataBuffer->GetLen()) == false)
		{
			nRet = -1;
		}
		delete pDataBuffer;
		pDataBuffer = NULL;
	}
    return nRet;
}

int CRcvProtocol::check_activity (AsynchChannel *channel,
                            const ACE_Time_Value&  last_op_time)
{
	if(last_op_time != ACE_Time_Value::zero)
	{
		ACE_Time_Value nTimeRun = ACE_OS::gettimeofday() - last_op_time;
		if(nTimeRun.msec()/1000 > 60)
		{
			return -1;
		}
	}
    return 0;
}

bool CRcvProtocol::OnReceivedFrame(const char* pFrameData,unsigned int nLen)
{
	if (pFrameData!=NULL && nLen>1)
	{
	    CRcvFactory& RcvFactory = static_cast <CRcvFactory&> (this->get_protocol_factory ());
		return RcvFactory.OnReadCompleted(this,pFrameData,nLen);
	}
	return true;
}

bool CRcvProtocol::OnReceivedValidate(unsigned int ulType,const char* pFrameData,unsigned int nLen)
{
	if(ulType != IO_C4C2S_CONNECTION)
	{
		return false;
	}

	char pCmd[8];
	*(unsigned int*)(pCmd)=htonl(ulType);
	*(unsigned int*)(pCmd + 4)=0;
	return StartWrite(pCmd,8);
}

bool CRcvProtocol::StartWrite(const char* pData,int nLen)
{
	{
		CAutoLock l(&m_CritSecAsynchChannel);
		if(m_pAsynchChannel)
		{
			return (m_pAsynchChannel->start_write(pData,nLen) == 0);
		}	
	}
	return false;
}

bool CRcvProtocol::SendData(const char* pData,int nLen)
{
	if(IsPendingWrite())
	{
		CDataBuffer* pDataBuffer = new CDataBuffer;
		if(pDataBuffer)
		{
			if(pDataBuffer->StoreData((char*)pData,nLen))
			{
				CBufferPool::SetDataBuffer(pDataBuffer);
				return true;
			}
			else
			{
				delete pDataBuffer;
				pDataBuffer = NULL;
			}
		}
	}
	else
	{
		return StartWrite(pData,nLen);
	}

	return false;
}

unsigned int CRcvProtocol::GetRemoteAddr(void)
{
	{
		CAutoLock l(&m_CritSecAsynchChannel);
		if(m_pAsynchChannel)
		{
			ACE_INET_Addr addr = m_pAsynchChannel->remote_addr();
			return addr.get_ip_address();
		}
	}
	
	return 0;
}

unsigned short CRcvProtocol::GetRemotePort(void)
{
	{
		CAutoLock l(&m_CritSecAsynchChannel);
		if(m_pAsynchChannel)
		{
			ACE_INET_Addr addr = m_pAsynchChannel->remote_addr();
			return addr.get_port_number();
		}
	}
	return 0;
}

std::string CRcvProtocol::GetRemoteIP(void)
{
	{
		CAutoLock l(&m_CritSecAsynchChannel);
		if(m_pAsynchChannel)
		{
			ACE_INET_Addr addr = m_pAsynchChannel->remote_addr();
			return addr.get_host_addr();
		}
	}
	return "";
}

void CRcvProtocol::ReleaseConnections(void)
{
	{
		CAutoLock l(&m_CritSecAsynchChannel);
		m_pAsynchChannel = NULL;
	}
	CFrame::Reset();

	CBufferPool::Flush();
}

bool CRcvProtocol::IsPendingWrite(void)
{
	{
		CAutoLock l(&m_CritSecAsynchChannel);
		if(m_pAsynchChannel)
		{
			return m_pAsynchChannel->is_pending_write();
		}
	}
	return false;
}

int CRcvProtocol::GetBufferCount(void)
{
	return CBufferPool::GetCount();
}