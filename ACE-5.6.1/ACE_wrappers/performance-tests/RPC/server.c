/*
 * $Id: server.c 27900 1999-08-23 21:54:22Z coryan $
 */

#include "ping.h"
#include <rpc/rpc.h>
#include <stdio.h>

static int return_value = 0;

int* ping_1_svc (int* value, struct svc_req* r)
{
  return_value = *value;
  return &return_value;
}
