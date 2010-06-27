// $Id: Timer_Queue.cpp 72183 2006-04-19 19:14:12Z jwillemsen $

#include "ace/Containers.h"
#include "ace/Timer_Queue.h"
#include "ace/Synch_Traits.h"
#include "ace/Recursive_Thread_Mutex.h"

ACE_RCSID(ace, Timer_Queue, "$Id: Timer_Queue.cpp 72183 2006-04-19 19:14:12Z jwillemsen $")

#if defined (ACE_HAS_BROKEN_HPUX_TEMPLATES)
#include "ace/Timer_Hash.h"
#include "ace/Timer_Queue_T.cpp"
#endif /* ACE_HAS_BROKEN_HPUX_TEMPLATES */

