// -*- C++ -*-
//
// $Id: Lock_Adapter_T.inl 69051 2005-10-28 16:14:56Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

template <class ACE_LOCKING_MECHANISM>
ACE_INLINE
ACE_Lock_Adapter<ACE_LOCKING_MECHANISM>::ACE_Lock_Adapter (
  ACE_LOCKING_MECHANISM &lock)
  : lock_ (&lock),
    delete_lock_ (0)
{
}

ACE_END_VERSIONED_NAMESPACE_DECL
