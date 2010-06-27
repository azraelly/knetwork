// file      : ace/RMCast/Stack.cpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// cvs-id    : $Id: Stack.cpp 78774 2007-07-04 06:06:59Z sowayaa $

#include "Stack.h"

namespace ACE_RMCast
{
  // Out_Element
  //

  Out_Element::
  ~Out_Element ()
  {
  }

  Out_Element::
  Out_Element ()
      : out_ (0)
  {
  }

  void Out_Element::
  out_start (Out_Element* out)
  {
    out_ = out;
  }

  void Out_Element::send (Message_ptr m)
  {
    if (out_) out_->send (m);
  }

  void Out_Element::
  out_stop ()
  {
    out_ = 0;
  }


  // In_Element
  //

  In_Element::
  ~In_Element ()
  {
  }

  In_Element::
  In_Element ()
      : in_ (0)
  {
  }

  void In_Element::
  in_start (In_Element* in)
  {
    in_ = in;
  }

  void In_Element::recv (Message_ptr m)
  {
    if (in_) in_->recv (m);
  }

  void In_Element::
  in_stop ()
  {
    in_ = 0;
  }
}
