// file      : Protocol.h
// author    : Boris Kolpackov <boris@kolpackov.net>
// cvs-id    : $Id: Protocol.h 74253 2006-08-28 09:14:50Z boris $

#ifndef PROTOCOL_H
#define PROTOCOL_H

unsigned short const payload_size = 200;
unsigned long const message_count = 100;

struct Message
{
  unsigned long sn;

  unsigned short payload[payload_size];
};

#endif  // PROTOCOL_H
