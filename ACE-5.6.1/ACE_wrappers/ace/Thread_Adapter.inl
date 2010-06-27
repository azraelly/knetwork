// -*- C++ -*-
//
// $Id: Thread_Adapter.inl 69062 2005-10-28 23:55:10Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE ACE_Thread_Manager *
ACE_Thread_Adapter::thr_mgr (void)
{
  return this->thr_mgr_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
