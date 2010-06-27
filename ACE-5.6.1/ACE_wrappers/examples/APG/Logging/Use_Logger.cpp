// $Id: Use_Logger.cpp 60975 2004-10-06 16:28:30Z shuston $

#include "ace/Log_Msg.h"

int ACE_TMAIN (int, ACE_TCHAR *argv[])
{
  ACE_LOG_MSG->open (argv[0], 
		     ACE_Log_Msg::LOGGER, 
                     ACE_DEFAULT_LOGGER_KEY);

  ACE_TRACE ("main");

  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("%IHi Mom\n")));
  ACE_DEBUG ((LM_INFO, ACE_TEXT ("%IGoodnight\n")));

  return 0;
}
