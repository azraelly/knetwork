// -*- C++ -*-
//
// $Id: HTBP_Filter.inl 69669 2005-11-27 12:11:35Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ssize_t
ACE::HTBP::Filter::send_data_header (ssize_t, ACE::HTBP::Channel * )
{
  return 0;
}

ACE_INLINE
ssize_t
ACE::HTBP::Filter::send_data_trailer (ACE::HTBP::Channel *)
{
  return 0;
}

ACE_INLINE
int
ACE::HTBP::Filter::send_ack (ACE::HTBP::Channel *)
{
  return 0;
}

ACE_INLINE
int
ACE::HTBP::Filter::recv_ack (ACE::HTBP::Channel *)
{
  return 0;
}

ACE_INLINE
ssize_t
ACE::HTBP::Filter::recv_data_header (ACE::HTBP::Channel *)
{
  return 0;
}

ACE_INLINE
ssize_t
ACE::HTBP::Filter::recv_data_trailer(ACE::HTBP::Channel *)
{
  return 0;
}

ACE_INLINE
void
ACE::HTBP::Filter::reset_http_code (void)
{
  this->http_code_ = 0;
}

ACE_INLINE
int
ACE::HTBP::Filter::http_code (void)
{
  return this->http_code_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
