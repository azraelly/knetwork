// file      : Utility/Introspection/TypeId.ipp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html
// cvs-id    : $Id: TypeId.ipp 66067 2005-05-24 04:33:13Z turkaye $

namespace Utility
{
  namespace Introspection
  {
    inline TypeId::
    TypeId (std::type_info const& tid)
        : tid_ (&tid)
    {
    }


    inline bool TypeId::
    operator == (TypeId const& other) const
    {
      return *tid_ == *other.tid_;
    }

    inline bool TypeId::
    operator != (TypeId const& other) const
    {
      return *tid_ != *other.tid_;
    }

    inline bool TypeId::
    operator < (TypeId const& other) const
    {
      return tid_->before (*other.tid_);
    }
  }
}
//$Id: TypeId.ipp 66067 2005-05-24 04:33:13Z turkaye $
