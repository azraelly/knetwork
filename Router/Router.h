#pragma once
#include "RcvFactory.h"

class CRouter
	: public CThread
{
public:
	CRouter(CRcvFactory& rRcvFactory);
	virtual ~CRouter(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);

	void ThreadProcMain(void);
public:
	bool	m_bWantToStop;
	CRcvFactory& m_rRcvFactory;
};
