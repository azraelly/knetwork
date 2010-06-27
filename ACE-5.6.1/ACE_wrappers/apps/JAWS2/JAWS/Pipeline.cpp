// $Id: Pipeline.cpp 32270 2000-04-27 23:43:23Z jxh $

#include "JAWS/Pipeline.h"

ACE_RCSID(JAWS, Pipeline, "$Id: Pipeline.cpp 32270 2000-04-27 23:43:23Z jxh $")

JAWS_Pipeline::JAWS_Pipeline (void)
{
}

int
JAWS_Pipeline::open (void *)
{
  // Simply call into the virtual svc() method.
  if (this->svc () == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "JAWS_Pipeline::svc"),
                      -1);
  return 0;
}

int
JAWS_Pipeline::close (u_long)
{
  return 0;
}