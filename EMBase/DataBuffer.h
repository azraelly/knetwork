// DataBuffer.h: interface for the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DATABUFFER_H__
#define __DATABUFFER_H__

class CDataBuffer  
{
public:
	CDataBuffer();
	virtual ~CDataBuffer();
public:
	bool StoreData(char*pData,int nLen);
	char*GetData(void){return m_pData;}
	int GetLen(void){return m_nLen;}
protected:
	char*				m_pData;
	int					m_nLen;
	int					m_nBufferSize;
};

#endif 