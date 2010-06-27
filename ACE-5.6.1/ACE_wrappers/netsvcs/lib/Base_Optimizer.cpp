// $Id: Base_Optimizer.cpp 35486 2000-10-10 22:16:31Z nanbor $

#if !defined (BASE_OPTIMIZER_CPP)
#define BASE_OPTIMIZER_CPP

#include "Base_Optimizer.h"

ACE_RCSID(lib, Base_Optimizer, "$Id: Base_Optimizer.cpp 35486 2000-10-10 22:16:31Z nanbor $")

template<class Base, class Member>
Base_Optimizer<Base, Member>::Base_Optimizer (void)
{
}

template<class Base, class Member>
Base_Optimizer<Base, Member>::Base_Optimizer (const Base &base,
                                              const Member &member)
  : Base (base),
    m_ (member)
{
}

template<class Base, class Member>
Base_Optimizer<Base, Member>::Base_Optimizer (const Base &base)
  : Base (base)
{
}

#endif /* BASE_OPTIMIZER_CPP */
