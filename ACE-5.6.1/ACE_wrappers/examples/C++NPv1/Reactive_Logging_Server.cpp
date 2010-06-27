/*
** $Id: Reactive_Logging_Server.cpp 78634 2007-06-28 14:14:06Z johnnyw $
**
** Copyright 2001 Addison Wesley. All Rights Reserved.
*/

#include "ace/Log_Msg.h"
#include "Reactive_Logging_Server.h"

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  Reactive_Logging_Server server;

  if (server.run (argc, argv) == -1)
    ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "server.run()"), 1);
  return 0;
}
