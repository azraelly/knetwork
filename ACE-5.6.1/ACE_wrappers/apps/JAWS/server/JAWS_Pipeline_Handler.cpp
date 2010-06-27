// $Id: JAWS_Pipeline_Handler.cpp 63384 2005-01-21 02:43:25Z ossama $

#ifndef JAWS_PIPELINE_HANDLER_CPP
#define JAWS_PIPELINE_HANDLER_CPP

#include "JAWS_Pipeline_Handler.h"

ACE_RCSID(server, JAWS_Pipeline_Handler, "$Id: JAWS_Pipeline_Handler.cpp 63384 2005-01-21 02:43:25Z ossama $")

template <class TYPE>
JAWS_Pipeline_Handler<TYPE>::JAWS_Pipeline_Handler (void)
{
}

template <class TYPE> int
JAWS_Pipeline_Handler<TYPE>::put (ACE_Message_Block *mb, ACE_Time_Value *tv)
{
  TYPE *data = dynamic_cast<TYPE *> (mb->data_block ());

  int status = this->handle_input (data, tv);

  return (status != -1) ? this->put_next (mb, tv) : -1;
}

#endif /* !defined (JAWS_PIPELINE_HANDLER_CPP) */
