// $Id: Handle_L_Dgram.cpp 73790 2006-07-27 20:43:46Z wotte $

#include "Handle_L_Dgram.h"

ACE_RCSID(server, Handle_L_Dgram, "$Id: Handle_L_Dgram.cpp 73790 2006-07-27 20:43:46Z wotte $")

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)

const ACE_TCHAR *Handle_L_Dgram::DEFAULT_RENDEZVOUS =
  ACE_TEXT ("/tmp/foo_dgram");

#if !defined (__ACE_INLINE__)
#include "Handle_L_Dgram.inl"
#endif /* __ACE_INLINE__ */

Handle_L_Dgram local_dgram;
ACE_Service_Object_Type ld (&local_dgram, ACE_TEXT ("Local_Dgram"));
#endif /* ACE_LACKS_UNIX_DOMAIN_SOCKETS */
