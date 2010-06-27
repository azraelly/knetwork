#ifndef __EMBASE_H__
#define __EMBASE_H__

#include <stack>
#include <set>
#include <map>
#include <list>
#include <string>

#include "AutoLock.h"
#include "ListPtr.h"
#include "Thread.h"
#include "DataPacket.h"
#include "BufferPool.h"
#include "CmdPacket.h"

std::string UL2STR(unsigned int ulValue);
unsigned int GenerateSSRC(void);
unsigned int GetTimestamp(void);
unsigned short STR2US(const std::string& szStr);
unsigned char STR2UC(const std::string& szStr);
unsigned int STR2UN(const std::string& szStr);
void PSleep(unsigned int ulMS);

#endif