// -*- C++ -*-
//
// $Id: Sig_Handler.inl 73522 2006-07-14 21:30:26Z ossama $

ACE_INLINE
ACE_Sig_Handler::ACE_Sig_Handler (void)
{
}

ACE_INLINE int
ACE_Sig_Handler::in_range (int signum)
{
  ACE_TRACE ("ACE_Sig_Handler::in_range");
  return signum > 0 && signum < ACE_NSIG;
}
