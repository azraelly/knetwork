#ifndef __THREAD_H__
#define __THREAD_H__

class CThread
{
public:
	CThread();
	virtual ~CThread();
public:
	bool StartThread(void);
	void WaitForStop(void);

#ifdef WIN32
	static DWORD WINAPI InitThreadProc(PVOID pObj){
		return	((CThread*)pObj)->ThreadProc();
	}
#else
	static void* InitThreadProc(void*pObj){
		((CThread*)pObj)->ThreadProc();
		return 0;
	}
#endif
	unsigned long ThreadProc(void);

protected:
	virtual void ThreadProcMain(void)=0;
protected:
#ifdef WIN32
	DWORD	m_dwThreadID;		
	HANDLE	m_hThread;			
	HANDLE	m_evStop;
#else
    pthread_t	m_thread;
    sem_t		m_semWaitForStop;
    bool		m_bThreadStopped;
#endif
};

#endif
