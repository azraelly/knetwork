/* -*- C++ -*- */
// $Id: PMS_All.h 16777 1998-10-20 02:34:57Z levine $

// ============================================================================
//
// = LIBRARY
//    drwho
//
// = FILENAME
//    PMS_All.h
//
// = AUTHOR
//    Douglas C. Schmidt
//
// ============================================================================

#ifndef _PMS_ALL_H
#define _PMS_ALL_H

#include "PM_Server.h"

class PMS_All : public PM_Server
{
  // = TITLE
  //   Provides the server's lookup table abstraction for `all' users...
public:
  PMS_All (void);

protected:
  virtual Protocol_Record *insert_protocol_info (Protocol_Record &protocol_record);
  virtual int encode (char *packet, int &total_bytes);
  virtual int decode (char *packet, int &total_bytes);
};

#endif /* _PMS_ALL_H */
