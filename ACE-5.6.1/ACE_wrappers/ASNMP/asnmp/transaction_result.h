/* -*-C++-*- */
#ifndef TRANSACTION_RESULT_H_
#define TRANSACTION_RESULT_H_
//=============================================================================
/**
 *  @file    transaction_result.h
 *
 *  $Id: transaction_result.h 71437 2006-03-08 10:45:52Z jwillemsen $
 *
 *  An object respresenting a request/reply operation between mgr/agent
 *
 *
 *  @author Michael R. MacFaden
 */
//=============================================================================


class transaction;
class ASNMP_Export transaction_result
{
  public:
    virtual ~transaction_result();
    virtual void result(transaction * trans, int) = 0;
};

#endif
