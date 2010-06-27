// $Id: Handle_L_CODgram.cpp 73790 2006-07-27 20:43:46Z wotte $

#include "Handle_L_CODgram.h"

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)

ACE_RCSID(server, Handle_L_CODgram, "$Id: Handle_L_CODgram.cpp 73790 2006-07-27 20:43:46Z wotte $")

const ACE_TCHAR *Handle_L_CODgram::DEFAULT_RENDEZVOUS =
  ACE_TEXT ("/tmp/foo_codgram");

#if !defined (__ACE_INLINE__)
#include "Handle_L_CODgram.inl"
#endif /* __ACE_INLINE__ */

Handle_L_CODgram local_codgram;
ACE_Service_Object_Type lc (&local_codgram, ACE_TEXT ("Local_CODgram"));

#endif /* ACE_LACKS_UNIX_DOMAIN_SOCKETS */
