// -*- C++ -*-  $Id: XMLFilterImpl.inl 73790 2006-07-27 20:43:46Z wotte $

ACEXML_INLINE int
ACEXML_XMLFilterImpl::setupParser (void)
{
  if (this->parent_ == 0)
    return -1;

  this->parent_->setEntityResolver (this);
  this->parent_->setDTDHandler (this);
  this->parent_->setContentHandler (this);
  this->parent_->setErrorHandler (this);
  return 0;
}
