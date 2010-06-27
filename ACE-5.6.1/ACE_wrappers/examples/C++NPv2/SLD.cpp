/*
** $Id: SLD.cpp 72205 2006-04-20 10:20:34Z jwillemsen $
**
** Copyright 2002 Addison Wesley. All Rights Reserved.
*/

#include "ace/Log_Msg.h"

#include "Reactor_Logging_Server_Adapter.h"
#include "Logging_Acceptor.h"
#include "SLD_export.h"

typedef Reactor_Logging_Server_Adapter<Logging_Acceptor>
        Server_Logging_Daemon;

ACE_FACTORY_DEFINE (SLD, Server_Logging_Daemon)

