/* -*- C++ -*- */
//=============================================================================
/**
 *  @file    Gadget_Factory.h
 *
 *  $Id: Gadget_Factory.h 41424 2001-08-29 12:02:09Z schmidt $
 *
 *  @author Christopher Kohlhoff <chris@kohlhoff.com>
 */
//=============================================================================

#ifndef GADGET_FACTORY_H
#define GADGET_FACTORY_H

#include "Gadget.h"

/**
 * @class Gadget_Factory
 *
 * @brief Used to create Gadget instances.
 */
class Gadget_Factory
{
public:
  /// Create an instance of a gadget. Ownership of the object is automatically
  /// transferred to the caller since we return a Gadget_var. This also means
  /// that the object will be deleted automatically if the caller "forgets" to
  /// collect the return value.
  static Gadget_var create_gadget (void);
};

#endif /* GADGET_FACTORY_H */
