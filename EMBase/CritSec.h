// CritSec.h: interface for the CCritSec class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __CRITSEC_H__
#define __CRITSEC_H__

class CCritSec  
{
public:
	CCritSec();
	virtual ~CCritSec();
public:
    void Lock(void);
    void Unlock(void);
protected:
#ifdef WIN32
    CRITICAL_SECTION m_CritSec;
#else
	pthread_mutex_t		m_pMutex;
#endif
};

#endif 