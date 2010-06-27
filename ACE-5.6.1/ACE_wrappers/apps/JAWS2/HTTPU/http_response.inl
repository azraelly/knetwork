// -*- c++ -*-
// $Id: http_response.inl 73790 2006-07-27 20:43:46Z wotte $

#if !defined (ACE_HAS_INLINED_OSCALLS)
# undef ACE_INLINE
# define ACE_INLINE
#endif /* ACE_HAS_INLINED_OSCALLS */

ACE_INLINE
HTTP_Response::HTTP_Response (void)
{
}

ACE_INLINE
HTTP_Response::~HTTP_Response (void)
{
}

ACE_INLINE Parse_HTTP_Response *
HTTP_Response::response_line (void)
{
  return &(this->response_);
}
