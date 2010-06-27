// -*- C++ -*-
//
// $Id: MMAP_Memory_Pool.inl 72149 2006-04-19 12:01:10Z jwillemsen $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_Mem_Map const &
ACE_MMAP_Memory_Pool::mmap (void) const
{
  return mmap_;
}

ACE_INLINE
ACE_Mem_Map &
ACE_MMAP_Memory_Pool::mmap (void)
{
  return mmap_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
