// $Id: Timer_List.cpp 72183 2006-04-19 19:14:12Z jwillemsen $

#include "ace/Timer_List.h"
#include "ace/Synch_Traits.h"
#include "ace/Recursive_Thread_Mutex.h"

ACE_RCSID(ace, Timer_List, "$Id: Timer_List.cpp 72183 2006-04-19 19:14:12Z jwillemsen $")

#if defined (ACE_HAS_BROKEN_HPUX_TEMPLATES)
#include "ace/Timer_Hash.h"
#include "ace/Timer_List_T.cpp"
#endif /* ACE_HAS_BROKEN_HPUX_TEMPLATES */

