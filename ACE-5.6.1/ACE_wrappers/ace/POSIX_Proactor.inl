// -*- C++ -*-
//
// $Id: POSIX_Proactor.inl 69051 2005-10-28 16:14:56Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_Asynch_Pseudo_Task& ACE_POSIX_Proactor::get_asynch_pseudo_task (void)
{
  return this->pseudo_task_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
