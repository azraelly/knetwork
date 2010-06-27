// -*- C++ -*-
//
// $Id: Process_Manager.inl 69051 2005-10-28 16:14:56Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE size_t
ACE_Process_Manager::managed (void) const
{
  return current_count_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
