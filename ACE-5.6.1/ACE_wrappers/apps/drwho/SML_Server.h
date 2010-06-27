/* -*- C++ -*- */
// $Id: SML_Server.h 16777 1998-10-20 02:34:57Z levine $

// ============================================================================
//
// = LIBRARY
//    drwho
//
// = FILENAME
//    SML_Server.h
//
// = AUTHOR
//    Douglas C. Schmidt
//
// ============================================================================

#ifndef _SML_SERVER_H
#define _SML_SERVER_H

#include "SM_Server.h"

class SML_Server : public SM_Server
{
public:
  SML_Server (void);
  virtual ~SML_Server (void);
};

#endif /* _SML_SERVER_H */
