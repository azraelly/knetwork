// $Id: DLL_Test_Parent.cpp 68551 2005-10-06 22:51:08Z ossama $

#include "DLL_Test_Parent.h"
#include "ace/Log_Msg.h"

ACE_RCSID (tests,
           DLL_Test_Parent,
           "$Id: DLL_Test_Parent.cpp 68551 2005-10-06 22:51:08Z ossama $")


Parent::~Parent (void)
{
}

void
Parent::test (void)
{
  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("parent called\n")));
}
