// $Id: dll.cpp 72205 2006-04-20 10:20:34Z jwillemsen $
#include "dll.h"

int test_variable = 0;

int
test_function ()
{
  test_variable = RETVAL;
  return RETVAL;
}

int
test_class::method ()
{
  return RETVAL;
}

test_class *
get_dll_singleton ()
{
  return TEST_SINGLETON::instance ();
}

#if defined (ACE_HAS_EXPLICIT_STATIC_TEMPLATE_MEMBER_INSTANTIATION)
template ACE_Singleton<test_class, ACE_Null_Mutex> *ACE_Singleton<test_class, ACE_Null_Mutex>::singleton_;
#endif /* ACE_HAS_EXPLICIT_STATIC_TEMPLATE_MEMBER_INSTANTIATION */
