#include "stdafx.h"

#ifdef _WIN32
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#endif

std::string UL2STR(unsigned int ulValue)
{
	char szValue[128]="";
	sprintf(szValue,"%u",ulValue);
	return szValue;
}

unsigned int GenerateSSRC(void)
{
#ifdef WIN32
	LARGE_INTEGER frequence, privious;
	if(!QueryPerformanceFrequency( &frequence))
	{
		return (unsigned int)timeGetTime();
	}
	if (!QueryPerformanceCounter( &privious ))
	{
		return (unsigned int)timeGetTime();
	}

	DWORD dwRet = (DWORD)(1000000 * privious.QuadPart / frequence.QuadPart ); 
	return dwRet;
#else
	struct timeval now;
	gettimeofday(&now,NULL);
	return (unsigned int)(now.tv_sec * 1000 + now.tv_usec); 
#endif
}

unsigned int GetTimestamp(void)
{
#ifdef WIN32
	return ::timeGetTime();
#else
	struct timeval now;
	gettimeofday(&now,NULL);
	return now.tv_sec * 1000 + now.tv_usec/1000; 
#endif
}

unsigned short STR2US(const std::string& szStr)
{
	return (unsigned short)strtoul(szStr.c_str(),NULL,10);
}

unsigned char STR2UC(const std::string& szStr)
{
	return (unsigned char)strtoul(szStr.c_str(),NULL,10);
}

unsigned int STR2UN(const std::string& szStr)
{
	return (unsigned int)strtoul(szStr.c_str(),NULL,10);
}

void PSleep(unsigned int ulMS)
{
#ifdef WIN32
	Sleep(ulMS);
#else
	usleep(ulMS*1000);
#endif
}