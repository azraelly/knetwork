// file      : Utility/ExH/StringStreamConverter.ipp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html

namespace Utility
{
  namespace ExH
  {
    template <>
    inline std::string
    converter (std::ostringstream const& t)
    {
      return t.str ();
    }
  }
}
//$Id: StringStreamConverter.ipp 66067 2005-05-24 04:33:13Z turkaye $
