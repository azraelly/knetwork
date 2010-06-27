#include "stdafx.h"
#include "DataPacket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void CDataOutPacket::Write16(unsigned short w)
{
	if(m_pCursor - m_pBuffer + sizeof(w) > m_nBufferLength)
	{
		int nFilled=m_pCursor - m_pBuffer;
		m_nBufferLength=(unsigned int)(m_pCursor - m_pBuffer + sizeof(w))*2;
		m_pBuffer=(unsigned char*)realloc(m_pBuffer,m_nBufferLength);
		if (m_pBuffer==NULL)
		{
			m_nBufferLength=0;
			Reset();
			return;
		}
		m_pCursor=m_pBuffer+nFilled;
	}

	*(unsigned short *)m_pCursor = w;
	m_pCursor += sizeof(w);
}

void CDataOutPacket::Write32(unsigned int dw)
{
	if(m_pCursor - m_pBuffer + sizeof(dw) > m_nBufferLength)
	{
		int nFilled=m_pCursor - m_pBuffer;
		m_nBufferLength=(unsigned int)(m_pCursor - m_pBuffer + sizeof(dw))*2;
		m_pBuffer=(unsigned char*)realloc(m_pBuffer,m_nBufferLength);
		if (m_pBuffer==NULL)
		{
			m_nBufferLength=0;
			Reset();
			return;
		}
		m_pCursor=m_pBuffer+nFilled;
	}

	*(unsigned int *) m_pCursor = dw;
	m_pCursor += sizeof(dw);
}

//void CDataOutPacket::Write64(unsigned long lw)
//{
//	if(m_pCursor - m_pBuffer + sizeof(lw) > m_nBufferLength)
//	{
//		int nFilled=m_pCursor - m_pBuffer;
//		m_nBufferLength=(unsigned int)(m_pCursor - m_pBuffer + sizeof(lw))*2;
//		m_pBuffer=(unsigned char*)realloc(m_pBuffer,m_nBufferLength);
//		if (m_pBuffer==NULL)
//		{
//			m_nBufferLength=0;
//			Reset();
//			return;
//		}
//		m_pCursor=m_pBuffer+nFilled;
//	}
//
//	*(unsigned long *) m_pCursor = lw;
//	m_pCursor += sizeof(lw);
//}

void CDataOutPacket::WriteData(unsigned char *buf, unsigned int n)
{
	if(m_pCursor - m_pBuffer + n > m_nBufferLength)
	{
		int nFilled=m_pCursor - m_pBuffer;
		m_nBufferLength=(unsigned int)(m_pCursor - m_pBuffer + n)*2;
		m_pBuffer=(unsigned char*)realloc(m_pBuffer,m_nBufferLength);
		if (m_pBuffer==NULL)
		{
			m_nBufferLength=0;
			Reset();
			return;
		}
		m_pCursor=m_pBuffer+nFilled;
	}

	memcpy(m_pCursor, buf, n);
	m_pCursor += n;
}

void CDataOutPacket::WriteString(const char *str, unsigned int n)
{
	unsigned int len = n + 1;
	if(m_pCursor - m_pBuffer + n + sizeof(len) > m_nBufferLength)
	{
		int nFilled=m_pCursor - m_pBuffer;
		m_nBufferLength=(unsigned int)(m_pCursor - m_pBuffer + n + sizeof(len))*2;
		m_pBuffer=(unsigned char*)realloc(m_pBuffer,m_nBufferLength);
		if (m_pBuffer==NULL)
		{
			m_nBufferLength=0;
			Reset();
			return;
		}
		m_pCursor=m_pBuffer+nFilled;
	}

	*this << len;
	memcpy(m_pCursor, str, len);
	m_pCursor[n] = '\0';
	m_pCursor += len;
}

void CDataOutPacket::Write8(unsigned char b)
{
	if(m_pCursor - m_pBuffer + sizeof(b) > m_nBufferLength)
	{
		int nFilled=m_pCursor - m_pBuffer;
		m_nBufferLength=(unsigned int)(m_pCursor - m_pBuffer + sizeof(b))*2;
		m_pBuffer=(unsigned char*)realloc(m_pBuffer,m_nBufferLength);
		if (m_pBuffer==NULL)
		{
			m_nBufferLength=0;
			Reset();
			return;
		}
		m_pCursor=m_pBuffer+nFilled;
	}

	*(unsigned char *) m_pCursor = b;
	m_pCursor += sizeof(b);
}

CDataOutPacket &CDataOutPacket::operator <<(unsigned char b)
{
	Write8(b);
	return *this;
}

CDataOutPacket &CDataOutPacket::operator <<(unsigned short w)
{
	Write16(htons(w));
	return *this;
}

CDataOutPacket &CDataOutPacket::operator <<(unsigned int dw)
{
	Write32(htonl(dw));
	return *this;
}

//CDataOutPacket &CDataOutPacket::operator <<(unsigned long lw)
//{
//	Write64(htonl(lw));
//	return *this;
//}

CDataOutPacket &CDataOutPacket::operator <<(const char *str)
{
	WriteString(str, (int)strlen(str));
	return *this;
}

CDataOutPacket &CDataOutPacket::operator <<(const std::string& str)
{
	WriteString(str.c_str(), (int)strlen(str.c_str()));
	return *this;
}

CDataOutPacket &CDataOutPacket::operator <<(bool b)
{
	Write8(b ? 1 : 0);
	return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned short CDataInPacket::Read16()
{
	unsigned short w = 0;
	if (m_pCursor <= m_pData + m_nDataLen - sizeof(w))
	{
		w = *(unsigned short *) m_pCursor;
		m_pCursor += sizeof(w);
	}
	return w;
}

unsigned int CDataInPacket::Read32()
{
	unsigned int dw = 0;
	if (m_pCursor <= m_pData + m_nDataLen - sizeof(dw))
	{
		dw = *(unsigned int *) m_pCursor;
		m_pCursor += sizeof(dw);
	}
	return dw;
}

//unsigned long CDataInPacket::Read64()
//{
//	unsigned long lw = 0;
//	if (m_pCursor <= m_pData + m_nDataLen - sizeof(lw))
//	{
//		lw = *(unsigned long *) m_pCursor;
//		m_pCursor += sizeof(lw);
//	}
//	return lw;
//}

unsigned char *CDataInPacket::ReadData(int &n)
{
	n = (int)(m_nDataLen - (m_pCursor - m_pData));
	if(n == 0)
	{
		return NULL;
	}
	return m_pCursor;
}

unsigned char CDataInPacket::Read8()
{
	unsigned char b = 0;
	if (m_pCursor <= m_pData + m_nDataLen - sizeof(b))
	{
		b = *m_pCursor++;
	}
	return b;
}

CDataInPacket &CDataInPacket::operator >>(bool &b)
{
	b = (Read8() != 0);
	return *this;
}

CDataInPacket &CDataInPacket::operator >>(unsigned char &b)
{
	b = Read8();
	return *this;
}

CDataInPacket &CDataInPacket::operator >>(unsigned short &w)
{
	w = ntohs(Read16());
	return *this;
}

CDataInPacket &CDataInPacket::operator >> (unsigned int &dw)
{
	dw = ntohl(Read32());
	return *this;
}

//CDataInPacket &CDataInPacket::operator >>(unsigned long &lw)
//{
//	lw = ntohl(Read64());
//	return *this;
//}

CDataInPacket &CDataInPacket::operator >> (const char* &str)
{
	unsigned int len;
	operator >> (len);
	if(len > m_nDataLen)
	{
		str = "";
	}
	else
	{
		if (len && m_pCursor <= m_pData + m_nDataLen - len && !m_pCursor[len - 1])
		{
			str = (char *)m_pCursor;
			m_pCursor += len;
		}
		else
		{
			str = "";
		}
	}
	return *this;
}

CDataInPacket &CDataInPacket::operator >> (std::string& str)
{
	unsigned int len;
	operator >> (len);
	if(len > m_nDataLen)
	{
		str = "";
	}
	else
	{
		if (len && m_pCursor <= m_pData + m_nDataLen - len && !m_pCursor[len - 1])
		{
			str = (char *)m_pCursor;
			m_pCursor += len;
		}
		else
		{
			str = "";
		}
	}
	return *this;
}


CDataInPacket &CDataInPacket::operator >> (char* str)
{
	const char* cszStr=NULL;
	unsigned int len;
	operator >> (len);
	if(len > m_nDataLen)
	{
		cszStr = "";
	}
	else
	{
		if (len && m_pCursor <= m_pData + m_nDataLen - len && !m_pCursor[len - 1])
		{
			cszStr = (char *)m_pCursor;
			m_pCursor += len;
		}
		else
		{
			cszStr = "";
		}
	}

	strcpy(str,cszStr);
	return *this;
}

int CDataInPacket::Forward(int nDelta)
{
	int nForwardLen = m_pCursor - m_pData;
	if(nDelta > nForwardLen)
	{
		nDelta = nForwardLen;
	}
	m_pCursor -= nDelta;

	return nDelta;
}