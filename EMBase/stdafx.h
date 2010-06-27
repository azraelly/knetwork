#pragma once

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <tchar.h>

#include <windows.h>
#include <winsock2.h>

#else

#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#endif

#include "EMBase.h"