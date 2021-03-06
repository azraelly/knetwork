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
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================

#ifndef ACE_TESTS_U_TEST_H
#define ACE_TESTS_U_TEST_H


#include "ProactorTask.h"
#include "Asynch_RW.h"
#include "ace/INET_Addr.h"
#include "ace/SString.h"

class DOwner;

// *************************************************************
//   Datagram session
// *************************************************************
class DSession : public ACE_Service_Handler
{
  friend class DOwner;
 
public:
  DSession  (DOwner & owner, int index, const ACE_TCHAR * name);
  ~DSession (void);


  virtual int on_open (const ACE_INET_Addr & local,
                       const ACE_INET_Addr & remote) =0;

  virtual int on_data_received (ACE_Message_Block & mb,
                                const ACE_INET_Addr & addr) = 0;

  virtual int on_data_sent     (ACE_Message_Block & mb,
                                const ACE_INET_Addr & addr) = 0;

  const ACE_TCHAR * get_name (void) const  { return name_.c_str();  }

  size_t get_total_snd (void) { return this->total_snd_; }
  size_t get_total_rcv (void) { return this->total_rcv_; }
  long get_total_w   (void) { return this->total_w_; }
  long get_total_r   (void) { return this->total_r_; }
  int  get_pending_r_ (void) { return this->io_count_r_; }
  int  get_pending_w_ (void) { return this->io_count_w_; }

  int  index (void) { return this->index_;}

  
  void print_address (const ACE_INET_Addr& peer,
                      const ACE_TCHAR * txt);

  int open (const ACE_INET_Addr & local,
            const ACE_INET_Addr & remote);
  
protected:
  /// This is called when asynchronous <read> operation from the
  /// socket completes.
  virtual void handle_read_dgram (const ACE_Asynch_Read_Dgram::Result &result);

  /// This is called when an asynchronous <write> to the socket
  /// completes.
  virtual void handle_write_dgram (const ACE_Asynch_Write_Dgram::Result &result);


  void cancel ();
  void close  ();

  int initiate_read (void);
  int initiate_write(ACE_Message_Block &mb,
                     const ACE_INET_Addr & addr);


  ACE_TString name_;
  DOwner & owner_;
  int      index_;

  Asynch_RW_Dgram stream_;
  ACE_SYNCH_MUTEX lock_;


 
  int  io_count_r_;          // Number of currently outstanding I/O reads
  int  io_count_w_;          // Number of currently outstanding I/O writes
  int  post_count_;          // Number of currently posted messages
  size_t total_snd_;         // Number of bytes successfully sent
  size_t total_rcv_;         // Number of bytes successfully received
  long total_w_;             // Number of write operations
  long total_r_;             // Number of read operations
};

// *************************************************************
//   Receiver
// *************************************************************

class Receiver : public DSession
{
  //friend class Bridge;

public:
  Receiver  (DOwner & owner, int index);
  ~Receiver (void);


  virtual int on_open (const ACE_INET_Addr & local,
                       const ACE_INET_Addr & remote);
  
  virtual int on_data_received (ACE_Message_Block & mb,
                                const ACE_INET_Addr & addr);

  virtual int on_data_sent     (ACE_Message_Block & mb,
                                const ACE_INET_Addr & addr);

};


// *************************************************************
//   Datagram sessions owner
// *************************************************************
class DOwner 
{
  friend class DSession;
public:
  int get_number_connections (void) const { return this->connections_; }
  size_t get_total_snd    (void) const { return this->total_snd_; }
  size_t get_total_rcv    (void) const { return this->total_rcv_; }
  long get_total_w        (void) const { return this->total_w_; }
  long get_total_r        (void) const { return this->total_r_; }

  ProactorTask & task (void) const { return task_;}

  DOwner (ProactorTask &task);
  virtual ~DOwner (void);

  
  int  start_receiver(const ACE_INET_Addr & local);
  void stop (void);
  void cancel_all (void);


  void on_new_session (DSession & session);
  void on_delete_session (DSession & session);

private:
  ProactorTask & task_;

  ACE_SYNCH_RECURSIVE_MUTEX lock_;
  u_int connections_;
  DSession * list_connections_[MAX_CONNECTIONS];

  size_t total_snd_;
  size_t total_rcv_;
  long total_w_;
  long total_r_;
  int  flg_cancel_;
};



#endif // ACE_TESTS_U_TEST_H
