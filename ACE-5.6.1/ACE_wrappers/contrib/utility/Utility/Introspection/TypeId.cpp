// file      : Utility/Introspection/TypeId.cpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

#include "Utility/Introspection/TypeId.hpp"

#include <ostream>

namespace Utility
{
  namespace Introspection
  {
    std::ostream&
    operator << (std::ostream& os, TypeId const& t)
    {
      return os << t.tid_->name ();
    }
  }
}
//$Id: TypeId.cpp 66067 2005-05-24 04:33:13Z turkaye $
