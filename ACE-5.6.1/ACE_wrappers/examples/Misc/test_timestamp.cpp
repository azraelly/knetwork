// $Id: test_timestamp.cpp 74073 2006-08-16 13:23:37Z johnnyw $

// Test the ACE::timestamp method.

#include "ace/OS_main.h"
#include "ace/ACE.h"
#include "ace/Log_Msg.h"

ACE_RCSID(Misc, test_timestamp, "$Id: test_timestamp.cpp 74073 2006-08-16 13:23:37Z johnnyw $")

int
ACE_TMAIN (int, ACE_TCHAR *[])
{
  ACE_TCHAR day_and_time[35];
  ACE::timestamp (day_and_time,
                  sizeof day_and_time);

  ACE_DEBUG ((LM_DEBUG, "%s", day_and_time));

  return 0;
}
