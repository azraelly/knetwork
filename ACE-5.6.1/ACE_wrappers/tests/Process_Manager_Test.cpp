// $Id: Process_Manager_Test.cpp 78459 2007-05-23 13:20:21Z johnnyw $

// ============================================================================
//
// = LIBRARY
//    tests
//
// = FILENAME
//    Process_Manager_Test.cpp
//
// = DESCRIPTION
//      This program tests the various methods provided by
//      <ACE_Process_Manager>.  It illustrates both the explicit <wait>
//      functions and the Reactor-style auto-reaping.  There's an
//      Exit_Handler class that can print out (in Debug mode) when a
//      child has been reaped.
//
//      The child processes spawned are simply this program itself, with
//      an integer argument specifying how long to "process" (actually,
//      the child just sleeps for the specified length of time).
//
// = AUTHOR
//    Douglas C. Schmidt <schmidt@cs.wustl.edu> and
//    Dave Madden <dhm@mersenne.com>
//
// ============================================================================

#include "test_config.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_string.h"
#include "ace/Process_Manager.h"
#include "ace/Get_Opt.h"
#include "ace/Thread.h"
#include "ace/Reactor.h"

ACE_RCSID(tests, Process_Manager_Test, "Process_Manager_Test.cpp,v 4.11 1999/09/02 04:36:30 schmidt Exp")

static u_int debug_test = 0;

class Exit_Handler : public ACE_Event_Handler
{
public:
  Exit_Handler (const char *msg): msg_ (msg) { }

  virtual ~Exit_Handler (void) { }

  virtual int handle_close (ACE_HANDLE, ACE_Reactor_Mask)
  {
    delete this;
    return 0;
  }

  virtual int handle_exit (ACE_Process *proc)
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) Exit_Handler(%s) got %d: %d\n"),
                msg_,
                int (proc->getpid ()),
                int (proc->exit_code ()) ));
    return 0;
  }
private:
  const char *msg_;
};

static void
usage (const ACE_TCHAR *argv0)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("usage: %s [-d] [sleep-seconds]\n"),
              argv0));
  ACE_OS::exit (0);
}

static pid_t
spawn_child (const ACE_TCHAR *argv0,
             ACE_Process_Manager &mgr,
             int sleep_time = 0)
{
#if defined (ACE_WIN32)
const ACE_TCHAR *cmdline_format = ACE_TEXT("\"%s\" %s %d");
#elif !defined (ACE_USES_WCHAR)
const ACE_TCHAR *cmdline_format = ACE_TEXT (".") ACE_DIRECTORY_SEPARATOR_STR ACE_TEXT("%s %s %d");
#else
const ACE_TCHAR *cmdline_format = ACE_TEXT (".") ACE_DIRECTORY_SEPARATOR_STR ACE_TEXT("%ls %ls %d");
#endif
  ACE_Process_Options opts;

  opts.command_line (cmdline_format,
                     argv0,
                     debug_test ? ACE_TEXT ("-d") : ACE_TEXT (""),
                     sleep_time);

  pid_t  result = mgr.spawn (opts);

  if (result != ACE_INVALID_PID)
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) spawned child: pid %d time %d\n"),
                int (result), sleep_time));
  else
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("spawn failed")));

  return result;
}

static int
command_line_test ()
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Testing for last character of command line\n")));
  int result = 0;
  const ACE_TCHAR *command = ACE_TEXT ("test Hello");
  size_t command_len = ACE_OS::strlen (command);
  ACE_Process_Options options (1, command_len + 1);
  options.command_line (command);
  ACE_TCHAR * const *procargv = options.command_line_argv ();
  if (ACE_OS::strcmp (procargv [1], ACE_TEXT ("Hello")) != 0)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("command_line_test failed: expected \"%s\"; got \"%s\"\n"),
                  ACE_TEXT ("Hello"),
                  procargv [1]));
      result = 1;
    }
  return result;
}

int
run_main (int argc, ACE_TCHAR *argv[])
{
  ACE_Get_Opt args (argc, argv, ACE_TEXT ("d"));

  for (int arg = args (); arg != EOF; arg = args ())
    switch (arg)
      {
      case 'd':
        debug_test = 1u;
        break;
      default:
        usage (argv[0]);
        break;
      }

  if (args.opt_ind () == argc - 1)
    {
      // child process: sleep & exit
      ACE_TCHAR lognm[MAXPATHLEN];
      int mypid (ACE_OS::getpid ());
      ACE_OS::sprintf(lognm, ACE_TEXT ("Process_Manager_Test-child-%d"), mypid);

      ACE_START_TEST (lognm);
      int secs = ACE_OS::atoi (argv[args.opt_ind ()]);
      ACE_OS::sleep (secs ? secs : 1);
      if (debug_test)
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%T: pid %P about to exit with code %d\n"),
                    secs));
      ACE_END_LOG;

      return secs;
    }

  if (args.opt_ind () != argc)      // incorrect usage
    usage (argv[0]);

  ACE_START_TEST (ACE_TEXT ("Process_Manager_Test"));

  int result = 0;
  int test_status = 0;

  if ((result = command_line_test ()) != 0)
    test_status = result;

  // Try the explicit <ACE_Process_Manager::wait> functions

  ACE_Process_Manager mgr;

  mgr.register_handler (new Exit_Handler ("default"));

  ACE_exitcode exitcode;

  // --------------------------------------------------
  // wait for a specific PID
  pid_t child1 = spawn_child (argv[0],
                              mgr,
                              1);
  result = mgr.wait (child1,
                     &exitcode);

  if (result != child1)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%P) Error: expected to reap child1 (%d); got %d\n"),
                  child1,
                  result));
      if (result == ACE_INVALID_PID)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P) %p\n"), ACE_TEXT ("error")));
      test_status = 1;
    }
  else
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) reaped child1, pid %d: %d\n"),
                child1,
                exitcode));

  // --------------------------------------------------
  // wait for a specific PID; another should finish first
  pid_t child2 = spawn_child (argv[0],
                              mgr,
                              1);
  pid_t child3 = spawn_child (argv[0],
                              mgr,
                              4);
  result = mgr.wait (child3,
                     &exitcode);

  if (result != child3)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%P) Error: expected to reap child3 (%d); got %d\n"),
                  child3,
                  result));
      if (result == ACE_INVALID_PID)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P) %p\n"), ACE_TEXT ("error")));
      test_status = 1;
    }
  else
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) reaped child 3, pid %d: %d\n"),
                child3,
                exitcode));

  // Now wait for any...should get the one that finished earlier.

  result = mgr.wait (0, &exitcode);

  if (result != child2)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%P) Error: expected to reap child2 (%d); got %d\n"),
                  child2,
                  result));
      if (result == ACE_INVALID_PID)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P) %p\n"), ACE_TEXT ("error")));
      test_status = 1;
    }
  else
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) reaped child 2, pid %d: %d\n"),
                result,
                exitcode));

  // --------------------------------------------------
  // Try the timed wait functions

  // This one shouldn't timeout:
  pid_t child4 = spawn_child (argv[0],
                              mgr,
                              1);
  result = mgr.wait (0, ACE_Time_Value (4), &exitcode);

  if (result != child4)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%P) Error: expected to reap child4 (%d); got %d\n"),
                  child4,
                  result));
      if (result == ACE_INVALID_PID)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P) %p\n"), ACE_TEXT ("error")));
      test_status = 1;
    }
  else
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) reaped child 4 pid %d: %d\n"),
                result,
                exitcode));

  // This one should timeout:
  pid_t child5 = spawn_child (argv[0],
                              mgr,
                              4);
  result = mgr.wait (0, ACE_Time_Value (1), &exitcode);
  if (result != 0)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%P) Error: expected wait to time out; got %d\n"),
                  result));
      if (result == ACE_INVALID_PID)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P) %p\n"), ACE_TEXT ("error")));
      test_status = 1;
    }
  else
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) Correctly timed out wait at child 5\n")));

  // Now wait indefinitely to clean up...
  result = mgr.wait (0, &exitcode);

  if (result != child5)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("Error: expected to reap child5 pid %d; got %d\n"),
                  child5,
                  result));
      if (result == ACE_INVALID_PID)
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P) %p\n"), ACE_TEXT ("error")));
      test_status = 1;
    }
  else
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%P) reaped child 5, pid %d: %d\n"),
                result,
                exitcode));

  // Terminate a child process and make sure we can wait for it.
  pid_t child6 = spawn_child (argv[0], mgr, 5);
  ACE_exitcode status6;
  if (-1 == mgr.terminate (child6))
    {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P) %p\n"), ACE_TEXT ("terminate child6")));
      test_status = 1;
      mgr.wait (child6, &status6);  // Wait for child to exit just to clean up
    }
  else
    {
      if (-1 == mgr.wait (child6, &status6))
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("(%P) wait on child6 reported ACE_INVALID_PID\n")));
          test_status = 1;
        }
      else
        {
          // Get the results of the termination.
#if !defined(ACE_WIN32)
          if (WIFSIGNALED (status6) != 0)
            ACE_DEBUG ((LM_DEBUG,
                        ACE_TEXT ("(%P) child6 died on signal %d - correct\n"),
                        WTERMSIG (status6)));
          else
            ACE_ERROR ((LM_ERROR,
                        ACE_TEXT ("(%P) child6 should have died on signal, ")
                        ACE_TEXT ("but didn't; exit status %d\n"),
                        WEXITSTATUS (status6)));
#else
          ACE_DEBUG
            ((LM_DEBUG,
              ACE_TEXT ("(%P) The process terminated with exit code %d\n"),
              status6));
#endif /*ACE_WIN32*/
        }
    }

#if !defined (ACE_OPENVMS)
  // --------------------------------------------------
  // Finally, try the reactor stuff...
  mgr.open (ACE_Process_Manager::DEFAULT_SIZE,
            ACE_Reactor::instance ());

  pid_t child7 = spawn_child (argv[0],
                              mgr,
                              5);
  /* pid_t child8 = */ spawn_child (argv[0],
                                    mgr,
                                    6);

  mgr.register_handler (new Exit_Handler ("specific"),
                        child7);

  ACE_Time_Value how_long (10);

  ACE_Reactor::instance ()->run_reactor_event_loop (how_long);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%P) Reactor loop done!\n") ));

  size_t nr_procs = mgr.managed ();
  if (nr_procs != 0)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%P) %d processes left in manager\n"),
                nr_procs));

#endif
  ACE_END_TEST;
  return test_status;
}

