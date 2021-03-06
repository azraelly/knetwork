// $Id: main_reactor.cpp 72205 2006-04-20 10:20:34Z jwillemsen $

// ============================================================================
//
// = LIBRARY
//    examples
//
// = FILENAME
//    main_reactor.cpp
//
// = DESCRIPTION
//      Implements an reactive timer queue.
//      This code exercises the Timer_Queue_Test_Driver class using
//      a reactor.
//
// = AUTHORS
//    Douglas Schmidt      <schmidt@cs.wustl.edu> &&
//    Sergio Flores-Gaitan <sergio@cs.wustl.edu>
//
// ============================================================================

// The following #pragma is needed to disable a warning that occurs
// in MSVC 6 due to the overly long debugging symbols generated for
// the std::auto_ptr<Timer_Queue_Test_Driver<...> > template
// instance used by some of the methods in this file.
#ifdef _MSC_VER
#  pragma warning(disable: 4786)  /* identifier was truncated to '255'
                                     characters in the browser
                                     information */
#endif  /* _MSC_VER */

#include "ace/OS_main.h"
#include "ace/Auto_Ptr.h"
#include "Reactor_Timer_Queue_Test.h"
#include "Driver.h"

ACE_RCSID (Timer_Queue,
           main_reactor,
           "$Id: main_reactor.cpp 72205 2006-04-20 10:20:34Z jwillemsen $")

typedef Timer_Queue_Test_Driver <ACE_Timer_Heap,
                                 Input_Handler,
                                 Input_Handler::ACTION>
        REACTOR_TIMER_QUEUE_TEST_DRIVER;

int
ACE_TMAIN (int, ACE_TCHAR *[])
{
  REACTOR_TIMER_QUEUE_TEST_DRIVER *tqtd;
  ACE_NEW_RETURN (tqtd, Reactor_Timer_Queue_Test_Driver, -1);
  // Auto ptr ensures that the driver memory is released
  // automatically.
  auto_ptr <REACTOR_TIMER_QUEUE_TEST_DRIVER> driver (tqtd);

  return driver->run_test ();
}

