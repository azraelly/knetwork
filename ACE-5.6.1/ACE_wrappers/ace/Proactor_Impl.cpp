// $Id: Proactor_Impl.cpp 76373 2007-01-06 00:13:33Z shuston $

#include "ace/Proactor_Impl.h"

ACE_RCSID (ace,
           Proactor_Impl,
           "$Id: Proactor_Impl.cpp 76373 2007-01-06 00:13:33Z shuston $")

#if defined (ACE_HAS_WIN32_OVERLAPPED_IO) || defined (ACE_HAS_AIO_CALLS)
// This only works on standard Win32 platforms and on Unix platforms supporting
// aio calls.

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_Proactor_Impl::~ACE_Proactor_Impl (void)
{
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif
