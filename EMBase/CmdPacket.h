#ifndef __CMDPACKET_H__
#define __CMDPACKET_H__

#define atoul(str)		strtoul(str,NULL,10)


typedef std::map<std::string,std::string>	MapNameToValue;
class CCmdPacket
{
public:
	CCmdPacket(const std::string& szXns,const std::string& szCmd,unsigned int ulFromUID,unsigned int ulToUID);
	CCmdPacket(const char* pData,unsigned int ulDataLen);
	CCmdPacket(CCmdPacket& rCmdPacket);
	CCmdPacket(void);
	~CCmdPacket(void);
public:
	void SetXns(const std::string& szXns);
	void SetCmd(const std::string& szCmd);
	void SetFromUID(unsigned int ulFromUID);
	void SetToUID(unsigned int ulToUID);

	std::string GetXns(void);
	std::string GetCmd(void);
	unsigned int GetFromUID(void);
	unsigned int GetToUID(void);

	void PutAttrib(const std::string& strName,const std::string& strValue);
	//void PutAttribUL(const std::string& strName,unsigned long ulValue);
	void PutAttribUN(const std::string& strName,unsigned int nValue);
	void PutAttribUS(const std::string& strName,unsigned short usValue);
	void PutAttribUC(const std::string& strName,unsigned char ucValue);
	void PutAttribBL(const std::string& strName,bool bValue);
	void PutAttribDT(const char* pData,unsigned int ulDataLen);

	std::string GetAttrib(const std::string& strName);
	//unsigned long GetAttribUL(const std::string& strName);
	unsigned int GetAttribUN(const std::string& strName);
	unsigned short GetAttribUS(const std::string& strName);
	unsigned char GetAttribUC(const std::string& strName);
	bool GetAttribBL(const std::string& strName);
	char* GetAttribDT(unsigned int& ulDataLen);

	std::string GetString();
	void SetString(const std::string& strText);
	unsigned int GetData(char** pData);
	void SetData(const std::string& szText,const char* pAttribData,unsigned int ulAttribDataLen);
	void SetData(const char* pData,unsigned int ulDataLen);

	void RemoveAttrib(const char* szName);
public:
	MapNameToValue	m_MapNameToValue;
	char*			m_pAttribData;
	unsigned int	m_ulAttribDataLen;
};

#endif