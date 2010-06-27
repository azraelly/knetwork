#include "stdafx.h"
#include "CmdPacket.h"
#include "DataPacket.h"

std::string	Replace(std::string& str,const char *string_to_replace,const char* new_string)
{
	int index = str.find(string_to_replace);
	while(index != std::string::npos)
	{
		str.replace(index,strlen(string_to_replace),new_string);
		index = str.find(string_to_replace,index + strlen(new_string));
	}
	return str;
}

CCmdPacket::CCmdPacket(void)
: m_pAttribData(NULL)
, m_ulAttribDataLen(0)
{
}

CCmdPacket::CCmdPacket(const std::string& szXns,const std::string& szCmd,unsigned int ulFromUID,unsigned int ulToUID)
: m_pAttribData(NULL)
, m_ulAttribDataLen(0)
{
	SetXns(szXns);
	SetCmd(szCmd);
	SetFromUID(ulFromUID);
	SetToUID(ulToUID);
}

CCmdPacket::CCmdPacket(const char* pData,unsigned int ulDataLen)
: m_pAttribData(NULL)
, m_ulAttribDataLen(0)
{
	SetData(pData,ulDataLen);
}

CCmdPacket::CCmdPacket(CCmdPacket& rCmdPacket)
: m_pAttribData(NULL)
, m_ulAttribDataLen(0)
{
	SetData(rCmdPacket.GetString(),rCmdPacket.m_pAttribData,rCmdPacket.m_ulAttribDataLen);
}

CCmdPacket::~CCmdPacket(void)
{
	m_MapNameToValue.clear();

	if(m_pAttribData)
	{
		delete []m_pAttribData;
		m_pAttribData = NULL;
	}
	m_ulAttribDataLen = 0;
}

void CCmdPacket::SetXns(const std::string& szXns)
{
	PutAttrib("xns",szXns);
}

void CCmdPacket::SetCmd(const std::string& szCmd)
{
	PutAttrib("cmd",szCmd);
}

void CCmdPacket::SetFromUID(unsigned int ulFromUID)
{
	PutAttribUN("fromuid",ulFromUID);
}

void CCmdPacket::SetToUID(unsigned int ulToUID)
{
	PutAttribUN("touid",ulToUID);
}

std::string CCmdPacket::GetXns(void)
{
	return GetAttrib("xns");
}

std::string CCmdPacket::GetCmd(void)
{
	return GetAttrib("cmd");
}

unsigned int CCmdPacket::GetFromUID(void)
{
	return GetAttribUN("fromuid");
}

unsigned int CCmdPacket::GetToUID(void)
{
	return GetAttribUN("touid");
}

void CCmdPacket::PutAttrib(const std::string& strName,const std::string& strValue)
{
	std::string szNewValue = strValue;
	Replace(szNewValue,">","/:}");
	m_MapNameToValue[strName]=szNewValue;
}

//void CCmdPacket::PutAttribUL(const std::string& strName,unsigned long ulValue)
//{
//	char szValue[128]="";
//	sprintf(szValue,"%lu",ulValue);
//	m_MapNameToValue[strName]=szValue;
//}

void CCmdPacket::PutAttribUN(const std::string& strName,unsigned int nValue)
{
	char szValue[128]="";
	sprintf(szValue,"%u",nValue);
	m_MapNameToValue[strName]=szValue;
}

void CCmdPacket::PutAttribUS(const std::string& strName,unsigned short usValue)
{
	char szValue[128]="";
	sprintf(szValue,"%u",usValue);
	m_MapNameToValue[strName]=szValue;
}

void CCmdPacket::PutAttribUC(const std::string& strName,unsigned char ucValue)
{
	char szValue[128]="";
	sprintf(szValue,"%u",ucValue);
	m_MapNameToValue[strName]=szValue;
}

void CCmdPacket::PutAttribBL(const std::string& strName,bool bValue)
{
	char szValue[128]="";
	sprintf(szValue,"%u",bValue ? 1 : 0);
	m_MapNameToValue[strName]=szValue;
}

void CCmdPacket::PutAttribDT(const char* pData,unsigned int ulDataLen)
{
	if(pData == NULL || ulDataLen == 0)
	{
		return;
	}

	if(m_pAttribData)
	{
		delete []m_pAttribData;
		m_pAttribData = NULL;

		m_ulAttribDataLen = 0;
	}

	m_pAttribData = new char[ulDataLen];
	if(m_pAttribData)
	{
		memcpy(m_pAttribData,pData,ulDataLen);
		m_ulAttribDataLen = ulDataLen;
	}
	else
	{
		m_ulAttribDataLen = 0;
	}
}

std::string CCmdPacket::GetAttrib(const std::string& strName)
{
	std::string strValue = "";
	MapNameToValue::iterator it=m_MapNameToValue.find(strName);
	if (it!=m_MapNameToValue.end())
	{
		strValue=(*it).second;
		Replace(strValue,"/:}",">");
	}
	return strValue;
}

//unsigned long CCmdPacket::GetAttribUL(const std::string& strName)
//{
//	unsigned long ulValue = 0;
//	MapNameToValue::iterator it=m_MapNameToValue.find(strName);
//	if (it!=m_MapNameToValue.end())
//	{
//		ulValue=atoul((*it).second.c_str());
//	}
//	return ulValue;
//}

unsigned int CCmdPacket::GetAttribUN(const std::string& strName)
{
	unsigned int nValue = 0;
	MapNameToValue::iterator it=m_MapNameToValue.find(strName);
	if (it!=m_MapNameToValue.end())
	{
		nValue=atoul((*it).second.c_str());
	}
	return nValue;
}

unsigned short CCmdPacket::GetAttribUS(const std::string& strName)
{
	unsigned short usValue = 0;
	MapNameToValue::iterator it=m_MapNameToValue.find(strName);
	if (it!=m_MapNameToValue.end())
	{
		usValue=atoul((*it).second.c_str());
	}
	return usValue;
}

unsigned char CCmdPacket::GetAttribUC(const std::string& strName)
{
	unsigned char ucValue = 0;
	MapNameToValue::iterator it=m_MapNameToValue.find(strName);
	if (it!=m_MapNameToValue.end())
	{
		ucValue=atoul((*it).second.c_str());
	}
	return ucValue;
}

bool CCmdPacket::GetAttribBL(const std::string& strName)
{
	unsigned char ucValue = 0;
	MapNameToValue::iterator it=m_MapNameToValue.find(strName);
	if (it!=m_MapNameToValue.end())
	{
		ucValue=atoul((*it).second.c_str());
	}
	return (ucValue != 0);
}

char* CCmdPacket::GetAttribDT(unsigned int& ulDataLen)
{
	ulDataLen = m_ulAttribDataLen;
	return m_pAttribData;
}

std::string CCmdPacket::GetString()
{
	std::string strText="";
	MapNameToValue::iterator it=m_MapNameToValue.begin();
	while (it!=m_MapNameToValue.end())
	{
		strText+="<";
		strText+=(*it).first;
		strText+="=";
		strText+=(*it).second;
		strText+=">";
		++it;
	}
	return strText;
}

void CCmdPacket::SetString(const std::string& strText)
{
	int nStrLen=strText.length();
	if (nStrLen<=0)
		return;

	char*szText=(char*)malloc(nStrLen+2);
	if (szText==NULL)
		return;

	strcpy(szText,strText.c_str());

	char*szTemp=szText;
	m_MapNameToValue.clear();
	while(szTemp)
	{
		if (*szTemp=='<')
		{
			char*szName=szTemp+1;
			while(szTemp && *szTemp!='='){szTemp++;};
			if (*szTemp=='=')
			{
				char*szValue=szTemp+1;
				*szTemp='\0';
				szTemp=szValue;
				while(szTemp && *szTemp!='>'){szTemp++;};
				if (*szTemp=='>')
				{
					char*szNext=szTemp+1;
					*szTemp='\0';
					szTemp=szNext;
					
					PutAttrib(szName,szValue);
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}

	free(szText);
	szText=NULL;
}

unsigned int CCmdPacket::GetData(char** pData)
{
	CDataOutPacket OutPacket(false);
	std::string szText = GetString();
	OutPacket<<szText;
	if(m_pAttribData && m_ulAttribDataLen > 0)
	{
		OutPacket.WriteData((unsigned char*)m_pAttribData,m_ulAttribDataLen);
	}
	*pData = (char*)OutPacket.GetData();
	return OutPacket.GetLength();
}

void CCmdPacket::SetData(const std::string& szText,const char* pAttribData,unsigned int ulAttribDataLen)
{
	SetString(szText);
	PutAttribDT(pAttribData,ulAttribDataLen);
}

void CCmdPacket::SetData(const char* pData,unsigned int ulDataLen)
{
	CDataInPacket InPacket((char*)pData,ulDataLen);
	std::string szText = "";
	InPacket>>szText;
	SetString(szText);

	int nAttribDataLen = 0;
	char* pAttribData = (char*)InPacket.ReadData(nAttribDataLen);
	if(pAttribData && nAttribDataLen > 0)
	{
		PutAttribDT(pAttribData,nAttribDataLen);
	}
}

void CCmdPacket::RemoveAttrib(const char* szName)
{
	MapNameToValue::iterator it = m_MapNameToValue.find(szName);
	if (it != m_MapNameToValue.end())
	{
		m_MapNameToValue.erase(it);
	}
}