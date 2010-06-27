#ifndef __FRAME_H__
#define __FRAME_H__

class CFrame
{
public:
	CFrame(void);
	~CFrame(void);
public:
	virtual void Reset(void);
	virtual bool OnReceivedData(const char*pData,unsigned int nLen);
	virtual bool OnReceivedFrame(const char* pFrameData,unsigned int nLen)=0;
	virtual bool OnReceivedValidate(unsigned int ulType,const char* pFrameData,unsigned int nLen)=0;
public:
	char*		m_pReceivedBuffer;
	unsigned int			m_nReceivedBufferLength;
	unsigned int			m_nReceivedDataLen;
	bool	m_bValidate;
};

#endif