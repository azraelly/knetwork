// $Id: main.cpp 59903 2004-08-27 17:40:28Z shuston $

// Test the client-side of the ACE Name Server...

#include "ace/Service_Config.h"
#include "ace/Log_Msg.h"
#include "Dump_Restore.h"

ACE_RCSID(Dump_Restore, main, "$Id: main.cpp 59903 2004-08-27 17:40:28Z shuston $")

int 
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_Service_Config daemon (argv[0]);

  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("entering main\n")));

  // Get a handler
  Dump_Restore client_handler (argc, argv);

  ACE_Reactor::run_event_loop ();
  
  /* NOTREACHED */
  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("leaving main\n")));
  return 0;
}
