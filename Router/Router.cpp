#include "StdAfx.h"
#include "Router.h"

CRouter::CRouter(CRcvFactory& rRcvFactory)
: m_bWantToStop(false)
, m_rRcvFactory(rRcvFactory)
{
}

CRouter::~CRouter(void)
{
	ReleaseConnections();
}

void CRouter::ReleaseConnections(void)
{
	m_bWantToStop = true;
	CThread::WaitForStop();

	m_rRcvFactory.ReleaseConnections();
}

bool CRouter::Connect(void)
{
	return CThread::StartThread();
}

void CRouter::ThreadProcMain(void)
{
	unsigned int nLastCheckTime = GetTimestamp();
	while(m_bWantToStop==false)
	{
		bool bRet = false;
		if(m_rRcvFactory.ProcessFrameDataPool())
		{
			bRet = true;
		}

		if(bRet == false)
		{
			PSleep(1);
		}
	}
}