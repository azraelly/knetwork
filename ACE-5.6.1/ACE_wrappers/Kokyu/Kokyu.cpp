// $Id: Kokyu.cpp 73790 2006-07-27 20:43:46Z wotte $

#include "Kokyu.h"

#include "Default_Dispatcher_Impl.h"

#if ! defined (__ACE_INLINE__)
#include "Kokyu.inl"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Kokyu, Kokyu, "$Id: Kokyu.cpp 73790 2006-07-27 20:43:46Z wotte $")

namespace Kokyu
{

int Dispatcher::dispatch (const Dispatch_Command* cmd, const QoSDescriptor& qos)
{
  return dispatcher_impl_->dispatch (cmd, qos);
}

int Dispatcher::shutdown ()
{
  return dispatcher_impl_->shutdown ();
}

int Dispatcher::activate ()
{
  return dispatcher_impl_->activate ();
}

void Dispatcher::implementation (Dispatcher_Impl* impl)
{
  auto_ptr<Dispatcher_Impl> tmp_impl (impl);
  dispatcher_impl_ = tmp_impl;

  //I couldn't use reset because MSVC++ auto_ptr does not have reset method.
  //So in configurations where the auto_ptr maps to the std::auto_ptr instead
  //of ACE auto_ptr, this would be a problem.
  //dispatcher_impl_.reset (impl);
}

Dispatcher*
Dispatcher_Factory::
create_dispatcher(const Dispatcher_Attributes& attrs)
{
  Dispatcher* disp;
  Dispatcher_Impl* tmp;
  ACE_NEW_RETURN (tmp, Default_Dispatcher_Impl, 0);
  ACE_NEW_RETURN (disp, Dispatcher, 0);
  disp->implementation (tmp);
  tmp->init (attrs);
  return disp;
}

}
