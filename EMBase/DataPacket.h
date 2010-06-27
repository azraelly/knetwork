#ifndef __DATAPACKET_H__
#define __DATAPACKET_H__

class CDataOutPacket
{
public:
	CDataOutPacket(bool bAutoDelete=true,int nBufferLength=1024)
		:m_pBuffer(NULL)
		,m_nBufferLength(nBufferLength)
		,m_bAutoDelete(bAutoDelete)
	{
		m_pBuffer=(unsigned char*)malloc(m_nBufferLength);
		if (m_pBuffer==NULL)
		{
			m_nBufferLength=0;
		}
		Reset();
	}
	virtual~CDataOutPacket(void)
	{
		if (m_pBuffer && m_bAutoDelete)
		{
			free(m_pBuffer);
			m_pBuffer=NULL;
		}
	}

	void Reset()
	{
		m_pCursor = m_pBuffer;
	}

	unsigned char *GetData()
	{
		return m_pBuffer;
	}

	int GetLength()
	{
		int n;
		n=(int)(m_pCursor - m_pBuffer);
		return n;
	}

	void Write8(unsigned char b);
	void Write16(unsigned short w);
	void Write32(unsigned int dw);
	//void Write64(unsigned long lw);
	void WriteData(unsigned char *buf, unsigned int n);
	void WriteString(const char *str, unsigned int n);

	CDataOutPacket &operator <<(unsigned char b);
	CDataOutPacket &operator <<(unsigned short w);
	CDataOutPacket &operator <<(unsigned int dw);
	//CDataOutPacket &operator <<(unsigned long lw);
	CDataOutPacket &operator <<(const char *str);
	CDataOutPacket &operator <<(const std::string& str);
	CDataOutPacket &operator <<(bool b);

	unsigned char *Skip(int delta)
	{
		m_pCursor += delta;
		return (m_pCursor - delta);
	}

	unsigned char *SetCursor(unsigned char *pCur)
	{
		unsigned char *pOld = m_pCursor;
		m_pCursor = pCur;
		return pOld;
	}

protected:
	unsigned char*	m_pBuffer;
	unsigned int	m_nBufferLength;
	unsigned char*	m_pCursor;
	bool			m_bAutoDelete;
};


class CDataInPacket
{
public:
	CDataInPacket(char *d, int n)
	{
		m_pCursor = m_pData = (unsigned char *) d;
		m_nDataLen = n;
	}

	CDataInPacket &operator >>(unsigned char &b);
	CDataInPacket &operator >>(unsigned short &w);
	CDataInPacket &operator >>(unsigned int &dw);
	//CDataInPacket &operator >>(unsigned long &lw);
	CDataInPacket &operator >>(const char* &str);
	CDataInPacket &operator >>(char* str);
	CDataInPacket &operator >>(std::string& str);
	CDataInPacket &operator >>(bool &b);

	unsigned char Read8();
	//unsigned long Read64();
	unsigned int Read32();
	unsigned short Read16();
	unsigned char *ReadData(int &n);

	int Forward(int nDelta);

	int GetLength()
	{
		return m_nDataLen;
	}

protected:
	unsigned char *m_pData;
	unsigned char *m_pCursor;
	int m_nDataLen;
};

#endif
