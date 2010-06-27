// -*- C++ -*-  $Id: SAXPrint_Handler.inl 73790 2006-07-27 20:43:46Z wotte $

ACEXML_INLINE void
ACEXML_SAXPrint_Handler::inc_indent (void)
{
  this->indent_ += 1;
}

ACEXML_INLINE void
ACEXML_SAXPrint_Handler::dec_indent (void)
{
  this->indent_ -= 1;
}
