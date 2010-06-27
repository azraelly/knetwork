#pragma once

#include "RcvProtocol.h"

typedef std::map<unsigned long,CRcvProtocol*>	MapRcvProtocol;

class CRcvFactory : public ProtocolFactory_T<CRcvProtocol>
{
public:
    CRcvFactory (const ACE_TCHAR *name, 
                 int log_level = 2,
                 unsigned int min_cache_size = 0, 
                 unsigned int max_cache_size = (unsigned)-1);
	virtual ~CRcvFactory(void);

	void OnChannelOpened(CRcvProtocol* pRcvProtocol);
	void OnChannelClosed(CRcvProtocol* pRcvProtocol);
	bool OnReadCompleted(CRcvProtocol* pRcvProtocol,const char* pData,int nLen);

	bool ProcessFrameDataPool(void);
	void SendToRcvProtocol(CCmdPacket& rCmdPacket);
	void ReleaseConnections(void);
	int GetBufferCount(void);
private:
	CCritSec	m_CritSecMapRcvProtocol;
	MapRcvProtocol	m_MapRcvProtocol;

	char*	m_pSndFrameBuffer;
	unsigned int	m_nSndFrameBufferLen;

	CCritSec	m_CritSecListCmdPacket;
	CListPtr	m_ListCmdPacket;
};
