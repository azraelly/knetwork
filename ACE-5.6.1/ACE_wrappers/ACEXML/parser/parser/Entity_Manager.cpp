// $Id: Entity_Manager.cpp 73790 2006-07-27 20:43:46Z wotte $

#include "ACEXML/parser/parser/Entity_Manager.h"

#if !defined (__ACEXML_INLINE__)
# include "ACEXML/parser/parser/Entity_Manager.inl"
#endif /* __ACEXML_INLINE__ */


ACEXML_Entity_Manager::ACEXML_Entity_Manager (void)
  : entities_ (0)
{

}

ACEXML_Entity_Manager::~ACEXML_Entity_Manager (void)
{
  this->reset();
}

