// $Id: Timer_Hash.cpp 72183 2006-04-19 19:14:12Z jwillemsen $

#include "ace/Timer_Hash.h"
#include "ace/Synch_Traits.h"
#include "ace/Recursive_Thread_Mutex.h"

#if defined (ACE_HAS_BROKEN_HPUX_TEMPLATES)
#include "ace/Timer_Hash_T.cpp"
#endif /* ACE_HAS_BROKEN_HPUX_TEMPLATES */

ACE_RCSID(ace, Timer_Hash, "$Id: Timer_Hash.cpp 72183 2006-04-19 19:14:12Z jwillemsen $")

