// file      : Utility/ExH/StringConverter.ipp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

namespace Utility
{
  namespace ExH
  {
    template <>
    inline char const*
    converter (std::string const& t) throw ()
    {
      return t.c_str ();
    }
  }
}
//$Id: StringConverter.ipp 66067 2005-05-24 04:33:13Z turkaye $
