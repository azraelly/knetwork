#include "stdafx.h"
#include "BufferPool.h"

CBufferPool::CBufferPool(void)
{
}

CBufferPool::~CBufferPool(void)
{
	Flush();
}

void CBufferPool::SetDataBuffer(CDataBuffer*pDataBuffer)
{
	CAutoLock l(&m_CritSec);

	m_listDataBuffer.push_back(pDataBuffer);
}

CDataBuffer*CBufferPool::GetDataBuffer(void)
{
	CAutoLock l(&m_CritSec);

	if (m_listDataBuffer.size())
	{
		CDataBuffer*pDataBuffer=(CDataBuffer*)m_listDataBuffer.front();
		m_listDataBuffer.pop_front();
		return pDataBuffer;
	}

	return NULL;
}

int CBufferPool::GetCount(void)
{
	CAutoLock l(&m_CritSec);
	return m_listDataBuffer.size();
}

void CBufferPool::Flush(void)
{
	CAutoLock l(&m_CritSec);

	while (m_listDataBuffer.size())
	{
		CDataBuffer*pDataBuffer=(CDataBuffer*)m_listDataBuffer.front();
		m_listDataBuffer.pop_front();
		delete pDataBuffer;
		pDataBuffer=NULL;
	}
}
