/* -*- C++ -*- */
// $Id: SMR_Server.h 16777 1998-10-20 02:34:57Z levine $

// ============================================================================
//
// = LIBRARY
//    drwho
//
// = FILENAME
//    SMR_Server.h
//
// = AUTHOR
//    Douglas C. Schmidt
//
// ============================================================================

#ifndef _SMR_SERVER_H
#define _SMR_SERVER_H

#include "SM_Server.h"

class SMR_Server : public SM_Server
{
public:
  SMR_Server (short port_number);
  ~SMR_Server (void);
};

#endif /* _SMR_SERVER_H */
