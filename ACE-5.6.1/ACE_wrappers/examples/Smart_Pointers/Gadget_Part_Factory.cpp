/* -*- C++ -*- */
//=============================================================================
/**
 *  @file    Gadget_Part_Factory.cpp
 *
 *  $Id: Gadget_Part_Factory.cpp 41424 2001-08-29 12:02:09Z schmidt $
 *
 *  @author Christopher Kohlhoff <chris@kohlhoff.com>
 */
//=============================================================================

#include "Gadget_Part_Factory.h"
#include "Gadget_Part_Impl.h"

Gadget_Part_var Gadget_Part_Factory::create_gadget_part (Gadget_ptr owner,
                                                         const char* name,
                                                         int size)
{
  return Gadget_Part_var (new Gadget_Part_Impl (owner, name, size));
}
