// $Id: Message_Queue_Test.cpp 78662 2007-06-29 19:27:23Z johnnyw $

// ============================================================================
//
// = LIBRARY
//    tests
//
// = FILENAME
//    Message_Queue_Test.cpp
//
// = DESCRIPTION
//      This is:
//      0) a test that ensures key ACE_Message_Queue features are
//         working properly, including timeouts and priorities.
//      1) a simple test of the ACE_Message_Queue that illustrates how to
//         use the forward and reverse iterators;
//      2) a simple performance measurement test for both single-threaded
//         (null synch) and thread-safe ACE_Message_Queues, and
//         ACE_Message_Queue_Vx, which wraps VxWorks message queues; and
//      3) a test/usage example of ACE_Message_Queue_Vx.
//
// = AUTHORS
//    Irfan Pyarali <irfan@cs.wustl.edu>,
//    David L. Levine <levine@cs.wustl.edu>, and
//    Douglas C. Schmidt <schmidt@vanderbilt.edu>
//
// ============================================================================

#include "test_config.h"
#include "ace/Thread_Manager.h"
#include "ace/Message_Queue.h"
#include "ace/Message_Queue_Vx.h"
#include "ace/Synch_Traits.h"
#include "ace/Null_Mutex.h"
#include "ace/Null_Condition.h"
#include "ace/High_Res_Timer.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_sys_time.h"

ACE_RCSID(tests, Message_Queue_Test, "$Id: Message_Queue_Test.cpp 78662 2007-06-29 19:27:23Z johnnyw $")

const ACE_TCHAR usage[] = ACE_TEXT ("usage: Message_Queue_Test <number of messages>\n");

typedef ACE_Message_Queue<ACE_NULL_SYNCH> QUEUE;
typedef ACE_Message_Queue_Iterator<ACE_NULL_SYNCH> ITERATOR;
typedef ACE_Message_Queue_Reverse_Iterator<ACE_NULL_SYNCH> REVERSE_ITERATOR;

static const int MAX_MESSAGES = 10000;
static const int MAX_MESSAGE_SIZE = 32;
static const char test_message[] = "ACE_Message_Queue Test Message";

static int max_messages = MAX_MESSAGES;

// Dynamically allocate to avoid a static.
static ACE_High_Res_Timer *timer = 0;

#if defined (ACE_HAS_THREADS)
typedef ACE_Message_Queue<ACE_MT_SYNCH> SYNCH_QUEUE;

struct Queue_Wrapper
{
  // = TITLE
  //     Container for data passed to sender and receiver in
  //     performance test.
  //
  // = DESCRIPTION
  //     For use in multithreaded performance test.

  ACE_Message_Queue_Base *q_;
  // The message queue.

  ACE_Message_Block **send_block_;
  // Pointer to messages blocks for sender to send to reciever.

  Queue_Wrapper (void)
    : q_ (0), send_block_ (0)
  {
  }
  // Default constructor.
};

#endif /* ACE_HAS_THREADS */

#if !defined (VXWORKS)
static int
iterator_test (void)
{
  const int ITERATIONS = 5;
  ACE_TCHAR buffer[ITERATIONS][BUFSIZ];
  // Use queue size from of 32 Kb (more if using wide-char), instead of the
  // default of 16 Kb (defined by ACE_Message_Queue_Base::DEFAULT_HWM),
  // so that the test runs on machines with 8Kb pagesizes.
#if !defined(_UNICOS)
  //  QUEUE queue (32 * 1024 * sizeof (ACE_TCHAR));
  QUEUE queue (sizeof(buffer));
#else
  // this works on the Cray, where BUFSIZ is defined as 32Kb
  QUEUE queue (ITERATIONS * BUFSIZ - 1);
#endif

  int i;

  for (i = 0; i < ITERATIONS; i++)
    {
      ACE_OS::sprintf (buffer[i],
                       ACE_TEXT ("%d"),
                       i + 1);

      ACE_Message_Block *entry;
      ACE_NEW_RETURN (entry,
                      ACE_Message_Block ((char *) buffer[i],
                                         sizeof buffer[i]),
                      -1);

      if (queue.is_full ())
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("QUEUE:: the message queue is full on iteration %u!\n"),
                           i + 1),
                          -1);

      if (queue.enqueue (entry) == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("QUEUE::enqueue\n")),
                          -1);
    }

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("\nForward Iterations\n")));
  {
    ITERATOR iterator (queue);

    for (ACE_Message_Block *entry = 0;
         iterator.next (entry) != 0;
         iterator.advance ())
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%s\n"),
                  entry->base ()));
  }

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("\nReverse Iterations\n")));
  {
    REVERSE_ITERATOR iterator (queue);

    for (ACE_Message_Block *entry = 0;
         iterator.next (entry) != 0;
         iterator.advance ())
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%s\n"),
                  entry->base ()));
  }

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("\nForward Iterations\n")));
  {
    QUEUE::ITERATOR iterator (queue);

    for (ACE_Message_Block *entry = 0;
         iterator.next (entry) != 0;
         iterator.advance ())
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%s\n"),
                  entry->base ()));
  }

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("\nReverse Iterations\n")));
  {
    QUEUE::REVERSE_ITERATOR iterator (queue);

    for (ACE_Message_Block *entry = 0;
         iterator.next (entry) != 0;
         iterator.advance ())
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%s\n"),
                  entry->base ()));
  }

  return 0;
}
#endif /* ! VXWORKS */

#if defined (ACE_HAS_THREADS)

static int
chained_block_test (void)
{

  QUEUE q;
  const char * s = "123456789";      // Will be length 10 when copied to block
  const size_t slen = 10;
  const size_t num_blks = 10;
  ACE_Message_Block b[num_blks];
  size_t i;
  int status = 0;

  for (i = 0; i < num_blks; ++i)
    {
      b[i].init (slen);
      b[i].copy (s);
    }

  // Test enqueueing single and chained blocks and be sure they end up with
  // the proper enqueued block count and sizes. Then be sure they are dequeued
  // in the proper order.
  b[0].next (&b[1]);
  b[1].next (&b[2]);
  // b[3] and b[4] are unchained.
  b[5].next (&b[6]);
  b[6].next (&b[7]);
  b[7].next (&b[8]);
  // b[9] is unchained
  q.enqueue_tail (&b[3]);
  q.enqueue_tail (&b[4]);
  int num = q.enqueue_head (&b[0]);
  if (num != 5)
    {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("Chained enqueue expected 5; has %d\n"),
                  num));
      status = -1;
    }
  num = q.enqueue_tail (&b[5]);
  if (num != 9)
    {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("Chained enqueue expected 9; has %d\n"),
                  num));
      status = -1;
    }
  num = q.enqueue_tail (&b[9]);
  if (num != 10)
    {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("Chained enqueue expected 10; has %d\n"),
                  num));
      status = -1;
    }
  size_t msgs, bytes;
  msgs = q.message_count ();
  bytes = q.message_bytes ();
  if (msgs != 10 || bytes != 100)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("Chained enqueue totals: %d msgs, %d bytes; ")
                  ACE_TEXT ("should be 10 msgs, 100 bytes\n"),
                  (int)msgs, (int)bytes));
      status = -1;
    }

  // Now see if we can dequeue them, checking the order.
  ACE_Time_Value nowait (ACE_OS::gettimeofday ());
  ACE_Message_Block *bp;
  int qstat;
  for (i = 0; i < num_blks; ++i)
    {
      qstat = q.dequeue_head (bp, &nowait);
      if (qstat == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("Checking chained blocks, pass %d: %p\n"),
                      (int)i, ACE_TEXT ("dequeue_head")));
          status = -1;
        }
      else if (bp != &b[i])
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("Checking chained blocks, pass %d: ")
                      ACE_TEXT ("block out of order\n"),
                      (int)i));
          status = -1;
        }
    }

  if (status == 0)
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Chained block test OK\n")));
  return status;
}

static int
single_thread_performance_test (int queue_type = 0)
{
  const char test_message[] =
    "ACE_Message_Queue Test Message";
  const ACE_TCHAR *message =
    ACE_TEXT ("ACE_Message_Queue<ACE_NULL_SYNCH>, single thread");
  int i = 0;

  // Create a message queue.
  ACE_Message_Queue_Base *msgq = 0;

  if (queue_type == 0)
    ACE_NEW_RETURN (msgq,
                    QUEUE,
                    -1);
#if defined (VXWORKS)
  else
    {
      ACE_NEW_RETURN (msgq,
                      ACE_Message_Queue_Vx (max_messages,
                                            MAX_MESSAGE_SIZE),
                      -1);
      message = "ACE_Message_Queue_Vx, single thread test";
    }
#elif defined (ACE_WIN32) && defined (ACE_HAS_WIN32_OVERLAPPED_IO)
  else
    {
      ACE_NEW_RETURN (msgq,
                      ACE_Message_Queue_NT,
                      -1);
      message = ACE_TEXT ("ACE_Message_Queue_NT, single thread test");
    }
#endif /* VXWORKS */

  // Create the messages.  Allocate off the heap in case messages
  // is large relative to the amount of stack space available.
  ACE_Message_Block **send_block = 0;
  ACE_NEW_RETURN (send_block,
                  ACE_Message_Block *[max_messages],
                  -1);

  for (i = 0; i < max_messages; ++i)
    ACE_NEW_RETURN (send_block[i],
                    ACE_Message_Block (test_message,
                                       MAX_MESSAGE_SIZE),
                    -1);

  ACE_Message_Block **receive_block_p = 0;
  ACE_NEW_RETURN (receive_block_p,
                  ACE_Message_Block *[max_messages],
                  -1);

#if defined (VXWORKS)
  // Set up blocks to receive the messages.  Allocate these off the
  // heap in case messages is large relative to the amount of
  // stack space available.
  ACE_Message_Block *receive_block;
  ACE_NEW_RETURN (receive_block,
                  ACE_Message_Block[max_messages],
                  -1);

  for (i = 0; i < max_messages; ++i)
    {
      receive_block[i].init (MAX_MESSAGE_SIZE);

      // For VxWorks Message Queues, the receive block pointer must be
      // assigned.  It will be used by dequeue_head ().
      receive_block_p[i] = &receive_block[i];
    }
#endif /* VXWORKS */

  timer->start ();

  // Send/receive the messages.
  for (i = 0; i < max_messages; ++i)
    {
      if (msgq->enqueue_tail (send_block[i]) == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%p\n"),
                           ACE_TEXT ("enqueue")),
                          -1);

      if (msgq->dequeue_head (receive_block_p[i]) == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%p\n"),
                           ACE_TEXT ("dequeue_head")),
                          -1);
    }

  timer->stop ();

  ACE_Time_Value tv;
  timer->elapsed_time (tv);
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%s: %u messages took %u msec (%f msec/message)\n"),
              message,
              max_messages,
              tv.msec (),
              (double) tv.msec () / max_messages));
  timer->reset ();

  delete [] receive_block_p;
#if defined (VXWORKS)
  delete [] receive_block;
#endif /* VXWORKS */

  for (i = 0; i < max_messages; ++i)
    delete send_block[i];
  delete [] send_block;
  delete msgq;

  return 0;
}

static void *
receiver (void *arg)
{
  Queue_Wrapper *queue_wrapper =
    reinterpret_cast<Queue_Wrapper *> (arg);
  int i;

  ACE_Message_Block **receive_block_p = 0;
  ACE_NEW_RETURN (receive_block_p,
                  ACE_Message_Block *[max_messages],
                  (void *) -1);

#if defined (VXWORKS)
  // Set up blocks to receive the messages.  Allocate these off the
  // heap in case messages is large relative to the amount of stack
  // space available.
  ACE_Message_Block *receive_block;
  ACE_NEW_RETURN (receive_block,
                  ACE_Message_Block[max_messages],
                  (void *) -1);

  for (i = 0; i < max_messages; ++i)
    {
      receive_block[i].init (MAX_MESSAGE_SIZE);

      // For VxWorks Message Queues, the receive block pointer must be
      // assigned.  It will be used by <dequeue_head>.
      receive_block_p[i] = &receive_block[i];
    }
#endif /* VXWORKS */

  for (i = 0; i < max_messages; ++i)
    if (queue_wrapper->q_->dequeue_head (receive_block_p[i]) == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%p\n"),
                         ACE_TEXT ("dequeue_head")),
                        0);
  timer->stop ();

  delete [] receive_block_p;
#if defined (VXWORKS)
  delete [] receive_block;
#endif /* VXWORKS */

  return 0;
}

static void *
sender (void *arg)
{
  Queue_Wrapper *queue_wrapper =
    reinterpret_cast<Queue_Wrapper *> (arg);
  int i;

  timer->start ();

  // Send the messages.
  for (i = 0; i < max_messages; ++i)
    if (queue_wrapper->q_->
        enqueue_tail (queue_wrapper->send_block_[i]) == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%p\n"),
                         ACE_TEXT ("enqueue")),
                        0);
  return 0;
}

static
int
performance_test (int queue_type = 0)
{
  Queue_Wrapper queue_wrapper;
  const ACE_TCHAR *message =
    ACE_TEXT ("ACE_Message_Queue<ACE_SYNCH>");
  int i = 0;

  // Create the messages.  Allocate off the heap in case messages is
  // large relative to the amount of stack space available.  Allocate
  // it here instead of in the sender, so that we can delete it after
  // the _receiver_ is done.
  ACE_Message_Block **send_block = 0;
  ACE_NEW_RETURN (send_block,
                  ACE_Message_Block *[max_messages],
                  -1);

  for (i = 0; i < max_messages; ++i)
    ACE_NEW_RETURN (send_block[i],
                    ACE_Message_Block (test_message,
                                       MAX_MESSAGE_SIZE),
                    -1);

  queue_wrapper.send_block_ = send_block;

  if (queue_type == 0)
    ACE_NEW_RETURN (queue_wrapper.q_,
                    SYNCH_QUEUE,
                    -1);
#if defined (VXWORKS)
  else
    {
      ACE_NEW_RETURN (queue_wrapper.q_,
                      ACE_Message_Queue_Vx (max_messages,
                                            MAX_MESSAGE_SIZE),
                      -1);
      message = "ACE_Message_Queue_Vx";
    }
#elif defined (ACE_WIN32) && defined (ACE_HAS_WIN32_OVERLAPPED_IO)
  else
    {
      ACE_NEW_RETURN (queue_wrapper.q_,
                      ACE_Message_Queue_NT,
                      -1);
      message = ACE_TEXT ("ACE_Message_Queue_NT");
    }
#endif /* VXWORKS */

  if (ACE_Thread_Manager::instance ()->spawn ((ACE_THR_FUNC) sender,
                                              &queue_wrapper,
                                              THR_BOUND) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%p\n"),
                       ACE_TEXT ("spawning sender thread")),
                      -1);

  if (ACE_Thread_Manager::instance ()->spawn ((ACE_THR_FUNC) receiver,
                                              &queue_wrapper,
                                              THR_BOUND) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%p\n"),
                       ACE_TEXT ("spawning receiver thread")),
                      -1);

  ACE_Thread_Manager::instance ()->wait ();
  ACE_Time_Value tv;
  timer->elapsed_time (tv);
  ACE_DEBUG ((LM_INFO, ACE_TEXT ("%s: %u messages took %u msec (%f msec/message)\n"),
              message,
              max_messages,
              tv.msec (),
              (double) tv.msec () / max_messages));
  timer->reset ();

  delete queue_wrapper.q_;
  queue_wrapper.q_ = 0;

  for (i = 0; i < max_messages; ++i)
    delete send_block[i];
  delete [] send_block;

  return 0;
}

// Ensure that the timedout dequeue_head() sets errno code properly.

static int
timeout_test (void)
{
  SYNCH_QUEUE mq;
  int status = 0;

  if (!mq.is_empty ())
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("New queue is not empty!\n")));
      status = 1;
    }
  else
    {
      ACE_Message_Block *b;
      ACE_Time_Value tv (ACE_OS::gettimeofday ());   // Now

      if (mq.dequeue_head (b, &tv) != -1)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("Dequeued from empty queue!\n")));
          status = 1;
        }
      else if (errno != EWOULDBLOCK)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("%p\n"),
                      ACE_TEXT ("Dequeue timeout should be EWOULDBLOCK, got")));
          status = 1;
        }
      else
        {
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("Timed dequeue test: OK\n")));
          status = 0;     // All is well
        }
    }

  return status;
}
#endif /* ACE_HAS_THREADS */

// Check to make sure that dequeue_prio() respects FIFO ordering.
// @@ At some point, this function should be enhanced to do a more
// thorough check...

static int
prio_test (void)
{
  const char S1[] = "first";
  const char S2[] = "second";
  const int PRIORITY = 50;
  QUEUE mq;
  int status;

  ACE_Message_Block mb1 (S1, sizeof S1, PRIORITY);
  ACE_Message_Block mb2 (S2, sizeof S2, PRIORITY);

  mq.enqueue_prio (&mb1);
  mq.enqueue_prio (&mb2);

  ACE_Message_Block *mb1p;
  ACE_Message_Block *mb2p;

  mq.dequeue_prio (mb1p);
  mq.dequeue_prio (mb2p);

  ACE_DEBUG ((LM_DEBUG, "message 1 = %s\nmessage 2 = %s\n",
              mb1p->rd_ptr (),
              mb2p->rd_ptr ()));

  if (ACE_OS_String::strcmp (mb1p->rd_ptr (), S1) == 0
      && ACE_OS_String::strcmp (mb2p->rd_ptr (), S2) == 0)
    status = 0;
  else
    status = 1;

  return status;
}

int
run_main (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("Message_Queue_Test"));

  if (argc == 2)
    if (!ACE_OS::strcmp (argv[1], ACE_TEXT ("-?")))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%s/n"),
                  usage));
    else
      max_messages = ACE_OS::atoi (argv[1]);

  int status = prio_test ();

#if !defined (VXWORKS)
  // The iterator test occasionally causes a page fault or a hang on
  // VxWorks.
  if (status == 0)
    status = iterator_test ();
#endif /* ! VXWORKS */

  ACE_NEW_RETURN (timer,
                  ACE_High_Res_Timer,
                  -1);

#if defined (ACE_HAS_THREADS)
  if (status == 0)
    status = timeout_test ();

  if (status == 0)
    status = chained_block_test ();

  if (status == 0)
    status = single_thread_performance_test ();

# if defined (VXWORKS) || defined (ACE_HAS_WIN32_OVERLAPPED_IO)
  // Test ACE_Message_Queue_Vx. or ACE_Message_Queue_NT
  if (status == 0)
    status = single_thread_performance_test (1);
# endif /* VXWORKS */

  if (status == 0)
    status = performance_test ();

# if defined (VXWORKS) || defined (ACE_HAS_WIN32_OVERLAPPED_IO)
  // Test ACE_Message_Queue_Vx or ACE_Message_Queue_NT
  if (status == 0)
    status = performance_test (1);
# endif /* VXWORKS */
#endif /* ACE_HAS_THREADS */

  if (status != 0)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%p\n"),
                ACE_TEXT ("test failed")));
  delete timer;
  timer = 0;

  ACE_END_TEST;
  return status;
}

