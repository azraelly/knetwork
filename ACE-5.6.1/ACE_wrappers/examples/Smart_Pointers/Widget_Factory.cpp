/* -*- C++ -*- */
//=============================================================================
/**
 *  @file    Widget_Factory.cpp
 *
 *  $Id: Widget_Factory.cpp 41424 2001-08-29 12:02:09Z schmidt $
 *
 *  @author Christopher Kohlhoff <chris@kohlhoff.com>
 */
//=============================================================================

#include "Widget_Factory.h"
#include "Widget_Impl.h"

Widget *Widget_Factory::create_widget (void)
{
  return new Widget_Impl;
}
