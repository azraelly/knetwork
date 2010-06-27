// $Id: HTTP_Policy.cpp 32270 2000-04-27 23:43:23Z jxh $

#include "HTTP_Policy.h"

ACE_RCSID(PROTOTYPE, HTTP_Policy, "$Id: HTTP_Policy.cpp 32270 2000-04-27 23:43:23Z jxh $")

HTTP_Policy::HTTP_Policy (JAWS_Concurrency_Base *concurrency)
  : concurrency_ (concurrency)
{
}

JAWS_Concurrency_Base *
HTTP_Policy::update (void *)
{
  /* for now, we always return the same concurrency strategy */
  return this->concurrency_;
}
