/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

// ============================================================================
//
// = LIBRARY
//    
//
// = FILENAME
//    PSession.h
//
// = DESCRIPTION
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================
#ifndef PSESSION_H
#define PSESSION_H

#include "ProactorTask.h"

#include "ace/Asynch_Acceptor.h"
#include "ace/Asynch_Connector.h"
#include "ace/SString.h"

#include "ace/OS_NS_sys_time.h"
#include "ace/OS_NS_string.h"

#include "Asynch_RWT.h"

class PSession;
class PSessionManager;
class PSessionFactory;

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class PSessionManager : public ACE_Handler
{
  friend class PSession;

public:
  int    get_number_connections (void) const { return this->num_connections_; }
  int    get_peak_connections (void) const { return this->peak_connections_; }

  // Sessions statistic
  size_t get_total_snd (void) const { return this->total_snd_; }
  size_t get_total_rcv (void) const { return this->total_rcv_; }
  long   get_total_w   (void) const { return this->total_w_; }
  long   get_total_r   (void) const { return this->total_r_; }

  const ACE_TCHAR * get_name (void) const { return this->name_.c_str();}

  ACE_SYNCH_RECURSIVE_MUTEX  & mutex(void) { return this->lock_;}

  ProactorTask & task (void) { return task_;}

  int    should_finish (void) const { return this->flg_cancel_;}
  int    is_safe_to_delete (void);
 
  // cancel method propagates cancel command to all 
  // active sessions and prevents creation of new sessions
  void   cancel (void);


  PSession * create_session (void);
  void       destroy_session (PSession * session);
  void       destroy_session (int index);

  PSessionManager (ProactorTask &    task, 
                   PSessionFactory & factory,
                   const ACE_TCHAR * name);

  virtual ~PSessionManager  (void);

  void set_timeout (const ACE_Time_Value & timeout);

  const ACE_Time_Value& get_timeout (void) const
    {
      return this->timeout_;
    }

  // virtual from ACE_Handler
  void handle_time_out (const ACE_Time_Value & /* tv */,
                        const void *   /* pArg */);

  void print_statistic(void);

protected:
  // evictor pattern
  void check  (void);

  void cancel_timer (void);
  void start_timer (void);

  ACE_SYNCH_RECURSIVE_MUTEX lock_;
  ProactorTask &            task_;
  PSessionFactory &         factory_;
  ACE_TString               name_;


  size_t total_snd_;  // Total bytes successfully sent
  size_t total_rcv_;  // Total bytes successfully received
  long   total_w_;    // Number of performed write operations
  long   total_r_;    // Number of performed read operations

  int    flg_cancel_; // Request to cancel

private:
  u_int                     num_connections_;
  u_int                     peak_connections_;
  PSession *                list_connections_[MAX_CONNECTIONS];
  ACE_Time_Value            timeout_;
  long                      timer_id_;
};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

class PSession : public ACE_Handler
{
  friend class PSessionManager;

public:
  PSession  (void);
  virtual ~PSession (void);

  size_t get_total_snd (void) const { return this->total_snd_; }
  size_t get_total_rcv (void) const { return this->total_rcv_; }
  long   get_total_w   (void) const { return this->total_w_; }
  long   get_total_r   (void) const { return this->total_r_; }
  int    get_ref_cnt_w (void) const { return this->ref_cnt_w_; }
  int    get_ref_cnt_r (void) const { return this->ref_cnt_r_; }


  ACE_SYNCH_MUTEX & mutex (void) { return this->lock_;}

  int    index (void) const { return this->index_; }

  PSessionManager * manager (void) const { return this->manager_; }

  ProactorTask &  task (void) const { return this->manager()->task();}

  TestCfg & config (void) const { return this->task().config(); }


  int has_pending_io (void) const
    { 
      return (get_ref_cnt_r() != 0 || get_ref_cnt_w() != 0);
    }

  virtual int open ()
    { throw 0;}

  
  // this should be pure virtual
  // get session name
  virtual const ACE_TCHAR * get_name (void) const
    { throw 0;}

  // this method is called when we have to force
  // cancellation of all outstanding requests 
  void  cancel (); 
  
  // this method is periodically called by PSessionManager
  // when timeout is expired
  void  check ();
  
  int  is_safe_to_delete (void) const;

  void update_last_time (void)
    {
      this->last_op_time_  = ACE_OS::gettimeofday ();
    }

  void set_timeout (const ACE_Time_Value & timeout)
    {
      this->timeout_ = timeout;
    }

  const ACE_Time_Value& get_timeout (void) const
    {
      return this->timeout_;
    }

protected:

  void trace_read_completion  (const ACE_Asynch_Read_Stream::Result &result,
                               const char *type);
  void trace_write_completion (const ACE_Asynch_Write_Stream::Result &result,
                               const char *type);


  //
  int  initiate_read   (u_long offset_low, u_long offset_high, size_t len);
  int  initiate_read   (u_long offset_low, u_long offset_high, ACE_Message_Block & mb);
  int  initiate_write  (u_long offset_low, u_long offset_high, ACE_Message_Block & mb);
  int  initiate_write  (u_long offset_low, u_long offset_high, const char * data, size_t len);

  
  void do_cancel ();

  void set_manager(PSessionManager * manager, int index);

  ACE_SYNCH_MUTEX lock_;

  PSessionManager * manager_;
  int    index_;


  int    ref_cnt_r_;         // Number of currently outstanding Read requests
  int    ref_cnt_w_;         // Number of currently outstanding Write requests
  size_t total_snd_;         // Total bytes successfully sent
  size_t total_rcv_;         // Total bytes successfully received
  long   total_w_;           // Number of performed write operations
  long   total_r_;           // Number of performed read operations
  ACE_Time_Value    last_op_time_;  // time of last activity
  ACE_Time_Value    timeout_;       // timeout value (0 means infinite)

  Asynch_RW_File     file_read_;
  Asynch_RW_File     file_write_;

};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

class PSessionFactory 
{
public:
  virtual ~PSessionFactory () {}
  virtual PSession*  create_session(PSessionManager & manager)=0;
};


#endif //PSESSION_H
