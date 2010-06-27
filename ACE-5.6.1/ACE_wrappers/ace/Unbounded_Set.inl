// -*- C++ -*-
//
// $Id: Unbounded_Set.inl 77304 2007-02-21 22:29:49Z ossama $

#include "ace/Global_Macros.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

template <class T> ACE_INLINE bool
ACE_Unbounded_Set<T>::is_empty (void) const
{
  ACE_TRACE ("ACE_Unbounded_Set<T>::is_empty");
  return this->head_ == this->head_->next_;
}

template <class T> ACE_INLINE bool
ACE_Unbounded_Set<T>::is_full (void) const
{
  ACE_TRACE ("ACE_Unbounded_Set<T>::is_full");
  return 0; // We should implement a "node of last resort for this..."
}

ACE_END_VERSIONED_NAMESPACE_DECL
