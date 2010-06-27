#pragma once


#include "IOTerabit/test_config.h"
#include "IOTerabit/IOThreadPool.h"
#include "IOTerabit/TcpChannel.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/ChannelAcceptor.h"
#include "IOTerabit/ChannelConnector.h"
#include "IOTerabit/ProtocolFactory_T.h"

#include "../EMBase/EMBase.h"

#ifdef _DEBUG
#pragma comment(lib,"ACEd.lib")
#pragma comment(lib,"TProactord.lib")
#pragma comment(lib,"IOTerabitd.lib")
#pragma comment(lib,"../lib/debug/EMBase.lib")
#else
#pragma comment(lib,"ACE.lib")
#pragma comment(lib,"TProactor.lib")
#pragma comment(lib,"IOTerabit.lib")
#pragma comment(lib,"../lib/release/EMBase.lib")
#endif

using namespace Terabit;

enum
{
	IO_C4C2S_CONNECTION = 0,
};