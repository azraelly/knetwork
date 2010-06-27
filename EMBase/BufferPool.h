#ifndef __BUFFERPOOL_H__
#define __BUFFERPOOL_H__

#include "DataBuffer.h"

class CBufferPool
{
public:
	CBufferPool(void);
	virtual ~CBufferPool(void);
public:
	virtual void SetDataBuffer(CDataBuffer*pDataBuffer);
	virtual CDataBuffer*GetDataBuffer(void);
	virtual int GetCount(void);
	virtual void Flush(void);
protected:
	CCritSec			m_CritSec;
	CListPtr				m_listDataBuffer;
};

#endif
