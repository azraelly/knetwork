// $Id: test_spipe_connector.cpp 61403 2004-10-27 21:07:30Z shuston $

// ACE_SPIPE Client.

#include "SPIPE-connector.h"

ACE_RCSID(blocking, test_spipe_connector, "$Id: test_spipe_connector.cpp 61403 2004-10-27 21:07:30Z shuston $")

int 
ACE_TMAIN (int argc, ACE_TCHAR *argv[])                       
{                                                       
  // Perform Service_Config initializations
  ACE_Service_Config daemon (argv[0]);

  IPC_Client peer_connector;

  if (peer_connector.init (argc, argv) == -1)
    ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("init")), -1);
  
  return peer_connector.svc ();
}                                                       
