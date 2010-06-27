/* -*- C++ -*- */
// $Id: Atomic_Op_Sparc.h 73444 2006-07-11 12:02:36Z elliott_c $

#ifndef ACE_ATOMIC_OP_SPARC_H
#define ACE_ATOMIC_OP_SPARC_H

extern "C"
{
  unsigned long ace_atomic_add_long (volatile unsigned long *dest, long rhs);
  unsigned long ace_atomic_swap_long (volatile unsigned long *dest, unsigned long rhs);
  unsigned long ace_atomic_swap_add_long (volatile unsigned long *dest, long rhs);
}

#endif /* ACE_ATOMIC_OP_SPARC_H */
