/* -*- C++ -*- */
// $Id: Connection_Handler_Connector.h 16777 1998-10-20 02:34:57Z levine $

// ============================================================================
//
// = LIBRARY
//    gateway
//
// = FILENAME
//    Connection_Handler_Connector.h
//
// = AUTHOR
//    Doug Schmidt
//
// ============================================================================

#ifndef _IO_HANDLER_CONNECTOR
#define _IO_HANDLER_CONNECTOR

#include "ace/Connector.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/SOCK_Connector.h"
#include "Connection_Handler.h"

class Connection_Handler_Connector : public ACE_Connector<Connection_Handler, ACE_SOCK_CONNECTOR>
{
  // = TITLE
  //     A concrete factory class that setups connections to peerds
  //     and produces a new Connection_Handler object to do the dirty
  //     work...
public:
  Connection_Handler_Connector (void);

  // Initiate (or reinitiate) a connection on the Connection_Handler.
  int initiate_connection (Connection_Handler *,
                           ACE_Synch_Options & = ACE_Synch_Options::synch);

};

#endif /* _IO_HANDLER_CONNECTOR */
