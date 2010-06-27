/* -*- C++ -*- */
// $Id: Select_Manager.h 65737 2005-04-30 06:56:58Z ossama $

// ============================================================================
//
// = LIBRARY
//    drwho
//
// = FILENAME
//    Select_Manager.h
//
// = AUTHOR
//    Douglas C. Schmidt
//
// ============================================================================

#ifndef _SELECT_MANAGER_H
#define _SELECT_MANAGER_H

class Select_Manager
{
public:
  virtual ~Select_Manager (void);

  virtual int mux (char *packet,
                   int &packet_length) = 0 ;

  virtual int demux (char *packet,
                     int &packet_length) = 0;
};

#endif /* _SELECT_MANAGER_H */
