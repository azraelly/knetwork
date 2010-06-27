// -*- C++ -*-
//
// $Id: Ping_Socket.inl 69051 2005-10-28 16:14:56Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE char *
ACE_Ping_Socket::icmp_recv_buff (void)
{
  return this->icmp_recv_buff_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
