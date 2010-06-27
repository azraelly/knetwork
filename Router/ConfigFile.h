#pragma once

typedef std::map<std::string, std::string> MapContent;
class CConfigFile  
{
public:
	CConfigFile(const std::string& szConfigFile);
	virtual ~CConfigFile(void);
	
	std::string GetValue(const std::string& szSection, const std::string& szEntry);
public:
	bool m_bFileNotFound;
	bool m_bStringNotFound;
    MapContent m_MapContent;
};

