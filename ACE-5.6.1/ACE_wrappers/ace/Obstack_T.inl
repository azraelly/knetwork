// -*- C++ -*-
//
// $Id: Obstack_T.inl 74069 2006-08-16 10:18:47Z johnnyw $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

template <class CHAR> ACE_INLINE size_t
ACE_Obstack_T<CHAR>::length () const
{
  return this->size_ / sizeof (CHAR);
}

template <class CHAR> ACE_INLINE size_t
ACE_Obstack_T<CHAR>::size () const
{
  return this->size_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
