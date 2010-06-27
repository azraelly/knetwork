// $Id: Handle_L_FIFO.cpp 73790 2006-07-27 20:43:46Z wotte $

#include "Handle_L_FIFO.h"

ACE_RCSID(server, Handle_L_FIFO, "$Id: Handle_L_FIFO.cpp 73790 2006-07-27 20:43:46Z wotte $")

#if defined (SunOS4)
extern "C"
{
  int init (void);
  int fini (void);
  void __sti__Handle_L_FIFO_C_init_();
  void __std__Handle_L_FIFO_C_init_();
}

int
init (void)
{
  __sti__Handle_L_FIFO_C_init_();
  return 0;
}

int
fini (void)
{
  __std__Handle_L_FIFO_C_init_();
  return 0;
}
#endif /* SunOS4 */

const ACE_TCHAR *Handle_L_FIFO::DEFAULT_RENDEZVOUS = ACE_TEXT("/tmp/foo_fifo");

#if !defined (__ACE_INLINE__)
#include "Handle_L_FIFO.inl"
#endif /* __ACE_INLINE__ */

Handle_L_FIFO local_fifo;
ACE_Service_Object_Type lf (&local_fifo, ACE_TEXT("Local_FIFO"));
