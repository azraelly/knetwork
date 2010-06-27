// file      : Utility/ExH/Converter.tpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

namespace Utility
{
  namespace ExH
  {
    template <typename T>
    std::string
    converter (T const& t)
    {
      // Default implementation just assumes that implicit converion exist.
      return t;
    }
  }
}
//$Id: Converter.tpp 66067 2005-05-24 04:33:13Z turkaye $
