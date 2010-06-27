#include "stdafx.h"
#include "ConfigFile.h"
#include <fstream>

CConfigFile::CConfigFile(const std::string& szConfigFile)
{
    std::ifstream file(szConfigFile.c_str());
	std::string line;
	std::string name;
	std::string value;
	std::string inSection;
	size_t posEqual;
    while (std::getline(file,line))
    {
		if ( !line.length()) continue;
		if ( line[0] == '#') continue;
		if ( line[0] == ';') continue;

		if ( line[0] == '[')
        {
			inSection=line.substr(1,line.find(']')-1);
			continue;
		}

		posEqual=line.find('=');
		name = line.substr(0,posEqual);
		value = line.substr(posEqual+1);
		size_t index = value.find('\r');
		if(index != -1)
			value = value.substr(0, index);
		index = value.find('\n');
		if(index != -1)
			value = value.substr(0, index);
		m_MapContent[inSection + '/' + name]=value;
	}
	m_bFileNotFound = (m_MapContent.empty());
}

CConfigFile::~CConfigFile(void)
{
	m_MapContent.clear();
}

std::string CConfigFile::GetValue(const std::string& szSection, const std::string& szEntry)
{
	m_bStringNotFound = false;
	MapContent::const_iterator ci = m_MapContent.find(szSection + '/' + szEntry);
	if (ci == m_MapContent.end())
    {
		m_bStringNotFound = true;
		return ""; // does not exist
    }
	return ci->second;
}
