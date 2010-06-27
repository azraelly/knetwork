// -*- C++ -*-
//
// $Id: Activation_Queue.inl 72759 2006-05-24 16:01:04Z schmidt $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE size_t
ACE_Activation_Queue::method_count (void) const
{
  return queue_->message_count ();
}

ACE_INLINE int
ACE_Activation_Queue::is_full (void) const
{
  return queue_->is_full ();
}

ACE_INLINE int
ACE_Activation_Queue::is_empty (void) const
{
  return queue_->is_empty ();
}

ACE_INLINE ACE_Message_Queue<ACE_SYNCH> *
ACE_Activation_Queue::queue (void) const
{
  return queue_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
