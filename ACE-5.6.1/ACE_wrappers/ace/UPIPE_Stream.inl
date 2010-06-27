// -*- C++ -*-
//
// $Id: UPIPE_Stream.inl 69062 2005-10-28 23:55:10Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE ACE_HANDLE
ACE_UPIPE_Stream::get_handle (void) const
{
  ACE_TRACE ("ACE_UPIPE_Stream::get_handle");
  return this->ACE_SPIPE::get_handle ();
}

ACE_END_VERSIONED_NAMESPACE_DECL
