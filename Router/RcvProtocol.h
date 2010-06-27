#pragma once

#include "Frame.h"

class CRcvProtocol : public Terabit::Protocol
				   , public CFrame
				   , public CBufferPool
{
public:
	CRcvProtocol(ProtocolFactory& factory);
	virtual ~CRcvProtocol(void);
public:
	virtual void reset();
    virtual int on_channel_opened(AsynchChannel *channel);
    virtual int on_read_completed (AsynchChannel *channel,const char* data,size_t length);
    virtual int on_write_completed (Terabit::AsynchChannel *channel);
    virtual int check_activity (AsynchChannel *channel,
                               const ACE_Time_Value&  last_op_time);

	virtual bool OnReceivedFrame(const char* pFrameData,unsigned int nLen);
	virtual bool OnReceivedValidate(unsigned int ulType,const char* pFrameData,unsigned int nLen);

	bool StartWrite(const char* pData,int nLen);
	bool SendData(const char* pData,int nLen);
	unsigned int GetRemoteAddr(void);
	unsigned short GetRemotePort(void);
	std::string GetRemoteIP(void);
	void ReleaseConnections(void);
	bool IsPendingWrite(void);
	int GetBufferCount(void);
public:
	CCritSec	m_CritSecAsynchChannel;
	AsynchChannel*	m_pAsynchChannel;
};
