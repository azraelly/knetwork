// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Thread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThread::CThread()
{
#ifndef WIN32
	sem_init(&m_semWaitForStop,0,1);
	m_thread = -1;
	m_bThreadStopped=true;
#else
	m_dwThreadID=0;
	m_hThread=NULL;
	m_evStop = CreateEvent(NULL,TRUE,TRUE,NULL);
	SetEvent(m_evStop);
#endif
}

CThread::~CThread()
{
#ifndef WIN32
	sem_destroy(&m_semWaitForStop);
#else
	CloseHandle(m_evStop);
#endif
}

bool CThread::StartThread()
{
#ifndef WIN32
	if (pthread_create(&m_thread,NULL,InitThreadProc,(void*)this)!=0)
		return false;
	sem_wait(&m_semWaitForStop);
	m_bThreadStopped=false;
	return true;
#else
	if (!m_hThread){ 
		m_hThread = CreateThread(
					NULL,			
                    0,				
                    InitThreadProc,	
                    this,			
                    0,				
                    &m_dwThreadID
					);
                
        }

	if (m_hThread)
		ResetEvent(m_evStop);

	return	m_hThread != NULL;
#endif
}

void CThread::WaitForStop()
{	
#ifndef WIN32
	if (m_bThreadStopped==false)
	{
		sem_wait(&m_semWaitForStop);
		m_bThreadStopped=true;
		pthread_join(m_thread,NULL);
	}
#else
	WaitForSingleObject(m_evStop,INFINITE);

	HANDLE hThread = (HANDLE)InterlockedExchange((LONG *)&m_hThread, 0);
	if (hThread) {
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}
#endif
}

unsigned long  CThread::ThreadProc()
{
	ThreadProcMain();
#ifndef WIN32
	sem_post(&m_semWaitForStop);
#else
	SetEvent(m_evStop);
#endif
	return 0;
}

