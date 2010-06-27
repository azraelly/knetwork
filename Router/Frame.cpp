#include "stdafx.h"
#include "Frame.h"

#define MAX_VALIDATE_LEN	2048

CFrame::CFrame(void)
: m_pReceivedBuffer(NULL)
, m_nReceivedBufferLength(0)
, m_nReceivedDataLen(0)
, m_bValidate(false)
{
}

CFrame::~CFrame(void)
{
	Reset();
}

void CFrame::Reset(void)
{
	if (m_pReceivedBuffer)
	{
		free(m_pReceivedBuffer);
		m_pReceivedBuffer=NULL;
	}

	m_nReceivedBufferLength=(0);
	m_nReceivedDataLen=(0);
	m_bValidate = false;
}

bool CFrame::OnReceivedData(const char*pData,unsigned int nLen)
{
	if (pData==NULL || nLen<=0)
	{
		return false;
	}

	//alloc buffer
	if (m_pReceivedBuffer==NULL)
	{
		m_nReceivedBufferLength=nLen*2;
		if (m_nReceivedBufferLength<1024)
			m_nReceivedBufferLength=1024;

		m_pReceivedBuffer=(char*)malloc(m_nReceivedBufferLength);
		if (m_pReceivedBuffer==NULL)
		{
			return false;
		}
	}

	//alloc more buffer
	if (m_nReceivedDataLen+nLen>m_nReceivedBufferLength)
	{
		m_nReceivedBufferLength=(m_nReceivedDataLen+nLen)*2;
		char*pTempBuffer=(char*)malloc(m_nReceivedBufferLength);
		if (pTempBuffer==NULL)
		{
			free(m_pReceivedBuffer);
			m_pReceivedBuffer=NULL;
			return false;
		}
		memcpy(pTempBuffer,m_pReceivedBuffer,m_nReceivedDataLen);
		free(m_pReceivedBuffer);
		m_pReceivedBuffer=pTempBuffer;
	}
	
	//save data
	memcpy(m_pReceivedBuffer+m_nReceivedDataLen,pData,nLen);
	m_nReceivedDataLen+=nLen;

	//read header
	char*pFrameData=m_pReceivedBuffer;
	unsigned int nReceivedDataLen=m_nReceivedDataLen;
	while (nReceivedDataLen>4)
	{
		if(m_bValidate == false)
		{
			if(nReceivedDataLen < 8)
			{
				break;
			}

			unsigned int ulLen = ntohl(*(unsigned int*)(pFrameData+4));
			if(ulLen > MAX_VALIDATE_LEN)
			{
				return false;
			}
			if(nReceivedDataLen < ulLen + 8)
			{
				break;
			}

			unsigned int ulType = ntohl(*(unsigned int*)pFrameData);
			if(OnReceivedValidate(ulType,pFrameData + 8,ulLen) == false)
			{
				return false;
			}
			m_bValidate = true;

			pFrameData += (ulLen + 8);
			nReceivedDataLen -= (ulLen + 8);
		}
		else
		{
			unsigned int nFrameDataLen=ntohl(*(unsigned int*)(pFrameData));
			if (nFrameDataLen+4<=nReceivedDataLen)
			{
				//skip header
				pFrameData+=4;
				nReceivedDataLen-=4;

				if(OnReceivedFrame(pFrameData,nFrameDataLen) == false)
				{
					return false;
				}

				//skip this frame
				pFrameData+=nFrameDataLen;
				nReceivedDataLen-=nFrameDataLen;
			}
			else
			{
				break;
			}
		}
	}

	//save left received data
	if (nReceivedDataLen>0)
	{
		memmove(m_pReceivedBuffer,pFrameData,nReceivedDataLen);
		m_nReceivedDataLen=nReceivedDataLen;
	}
	else
	{
		m_nReceivedDataLen=0;
	}
	return true;
}
