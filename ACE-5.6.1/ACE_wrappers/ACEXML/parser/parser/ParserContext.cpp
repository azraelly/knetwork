// $Id: ParserContext.cpp 72203 2006-04-20 09:59:58Z jwillemsen $

#include "ACEXML/parser/parser/ParserContext.h"

#if !defined (__ACEXML_INLINE__)
# include "ACEXML/parser/parser/ParserContext.inl"
#endif /* __ACEXML_INLINE__ */

ACEXML_Parser_Context::~ACEXML_Parser_Context()
{
  delete this->instream_;
  this->instream_ = 0;
  delete this->locator_;
  this->locator_ = 0;
}

