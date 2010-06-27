/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file ex0.cpp  
**  
**  ex0.cpp
**   
**  This program illustrates how the TRB_Proactor can be used to
**  implement an application that does various asynchronous
**  operations.
**  
**  @author Alexander Libman <libman@terabit.com.au>
**********************************************************************/

#include "Cfg.h"

#include "IOTerabit/TcpChannel.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/ChannelAcceptor.h"
#include "IOTerabit/ChannelConnector.h"
#include "IOTerabit/ProtocolFactory_T.h"

using namespace Terabit;

static TestCfg cfg;

static ACE_TCHAR complete_message[1024] =
  ACE_TEXT ("GET / HTTP/1.1\r\n")
  ACE_TEXT ("Accept: */*\r\n")
  ACE_TEXT ("Accept-Language: C++\r\n")
  ACE_TEXT ("Accept-Encoding: gzip, deflate\r\n")
  ACE_TEXT ("User-Agent: P_Test /1.0 (non-compatible)\r\n")
  ACE_TEXT ("Connection: Keep-Alive\r\n")
  ACE_TEXT ("\r\n");

static ACE_TCHAR header [] =
  "\r\n====== begin of data===\r\n";

static ACE_TCHAR trailer [] =
  "\r\n====== end of data===\r\n";

#include "Frame.h"
#include "../EMBase/EMBase.h"

enum
{
	IO_C4C2S_CONNECTION = 0,
};
// *******************************************
//   Sender
// *******************************************
class SndProtocol : public Protocol
				  , public CFrame
{
public:
   
    SndProtocol(ProtocolFactory& factory)
        : Protocol (factory)
		, m_pSndFrameBuffer(NULL)
		, m_nSndFrameBufferLen(0)
    {
    }

    virtual ~SndProtocol() 
    {
		reset();
    }
    
    virtual void reset ()
    {
		CFrame::Reset();
		if(m_pSndFrameBuffer)
		{
			delete []m_pSndFrameBuffer;
			m_pSndFrameBuffer = NULL;
		}
		m_nSndFrameBufferLen = 0;
	}

	void SendData(AsynchChannel *channel,CCmdPacket& rCmdPacket)
	{
		char* pData = NULL;
		unsigned int nLen = rCmdPacket.GetData(&pData);
		if(pData == NULL || nLen == 0)
		{
			return;
		}

		if(m_nSndFrameBufferLen < nLen + 1024)
		{
			m_nSndFrameBufferLen = nLen + 1024;
			if(m_pSndFrameBuffer)
			{
				delete []m_pSndFrameBuffer;
				m_pSndFrameBuffer = NULL;
			}
			m_pSndFrameBuffer = new char[m_nSndFrameBufferLen];
			if(m_pSndFrameBuffer == NULL)
			{
				m_nSndFrameBufferLen = 0;
			}
		}

		if(m_pSndFrameBuffer)
		{
			*(unsigned long*)m_pSndFrameBuffer = htonl(nLen);
			memcpy(m_pSndFrameBuffer + 4,pData,nLen);

			channel->start_write(m_pSndFrameBuffer,nLen + 4);
		}

		if(pData)
		{
			delete []pData;
			pData = NULL;
		}
	}

    virtual int on_channel_opened (AsynchChannel *channel)
    {
        channel->enable_read ();                 // this is default
        channel->enable_write_notifications ();  // this is not
        channel->set_read_size (cfg.r_blksize ());

		char pCmd[8];
		*(unsigned int*)(pCmd)=htonl(IO_C4C2S_CONNECTION);
		*(unsigned int*)(pCmd + 4)=0;
        return channel->start_write(pCmd,
                           sizeof(pCmd));
    }
      
    
    virtual int on_write_completed (AsynchChannel *channel)
    {
        return 0;
    }

    virtual int on_read_completed (AsynchChannel *channel,
                                   const char    *data,
                                   size_t         length)
    {
		if(CFrame::OnReceivedData(data,length) == false)
		{
			return -1;
		}
        return length;  // all data consumed
    }

      
    virtual int on_timeout (AsynchChannel *channel,
                            const void    *arg)
    {
        return -1;
    }

    virtual int check_activity (AsynchChannel *channel,
                               const ACE_Time_Value&  last_op_time)
    {
		if(m_bValidate)
		{
			CCmdPacket SndPacket;
			SndPacket.PutAttribDT(complete_message,sizeof(complete_message));
			SendData(channel,SndPacket);
		}
        return 0;
    }

	virtual bool OnReceivedFrame(const char* pFrameData,unsigned int nLen)
	{
		if(pFrameData && nLen > 1)
		{
			//CCmdPacket RcvPacket(pFrameData,nLen);
			//std::string szStr = RcvPacket.GetString();
			//std::cout << szStr << "\r\n" << std::endl;
		}
		return true;
	}
	virtual bool OnReceivedValidate(unsigned int ulType,const char* pFrameData,unsigned int nLen)
	{
		if(ulType != IO_C4C2S_CONNECTION)
		{
			return false;
		}
		return true;
	}
private:
	char*	m_pSndFrameBuffer;
	unsigned int	m_nSndFrameBufferLen;
};
// *************************************************************
//
// *************************************************************
typedef ProtocolFactory_T<SndProtocol> SndFactory;
// *************************************************************
//   Configuration helpers
// *************************************************************
int
run (int argc, ACE_TCHAR *argv[])
{
    int rc = 0;

    // factory for TcpChannels
    TcpChannelFactory channel_factory;


    // IO Thread Pool for Channels, Acceptors, Connectors
    IOThreadPool task1 ("IOThreadPool-1",          // name for logging
                        cfg.proactor_type (),      // proactor type
                        cfg.leader_type () ,       // shared | dedicated
                        cfg.demultiplexors (),     // number or proactors
                        cfg.max_aio_operations (), // max num aio or 0
                        cfg.sig_num ());           // for legacy


    // Channel Manager
    ChannelManager manager("Manager",          // name for logging
                           task1,              // IOThreadPool for channels
                           channel_factory);   // factory of channels

    ACE_Time_Value timeout (cfg.timeout(), 0);
    manager.set_timeout (timeout);              // set check timeout
    manager.set_log_level (cfg.loglevel());     // set log level
    manager.open ();                            // open manager
 
    // Protocol Factories (user supplied)
    SndFactory  s_factory ("SndFactory",        // name for logging
                           cfg.loglevel ());    // log level

    // Connector
    ChannelConnector connector (task1,          // IOThreadPool for connecting
                                s_factory,      // factory of protocols
                                manager);       // channel manager

    connector.set_log_level (1);  // cfg.loglevel ());

    ACE_INET_Addr connect_addr (cfg.connect_port (),
                                cfg.connect_host ());

    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

    // start with IOThreadPool with N threads
    if (task1.start (cfg.threads ()) != 0)
    {
        return -1;
    }

    rc = 1;

    // start M client connects
    for (u_int i = 0; i < cfg.connections (); ++i, ++rc)
    {
        if  (connector.start (connect_addr, (const void *) i) != 0)
        {
            break;
        }
    }

    time_begin = ACE_OS::gettimeofday ();
    

    ChannelManager::Statistic stat;


    if (rc > 0)
    {
        ACE_Time_Value  sleep_time (cfg.seconds());
            
        while ( sleep_time != ACE_Time_Value::zero)
        {
            ACE_Countdown_Time countdown ( & sleep_time );

            ACE_OS::sleep (sleep_time );
        }


        if (cfg.seconds () == 0)
        {
            bool flgExit = false;
            for (;!flgExit;)
            {
                char c;
                cout << "\nEnter:"
                     << "\n1 - stop  connector"
                     << "\n3  -stop  manager"
                     << "\nP - statistic"
                     << "\nQ   quit=>" 
                     << flush;
                cin.clear ();
                cin >> c;
                switch (toupper (c))
                {
                case '1':
                    connector.cancel();
                    connector.wait ();
                    break;
               case '3':
                    manager.close ();
                    manager.wait ();
                    break;
                case 'Q':
                    flgExit = true;
                    break;
                case 'P':
                    break;
                }//switch
                manager.get_statistic(stat);
                cout << "\n*** Connector: PendingConnects="
                     << connector.get_pending_count ()
                     << "\n*** Channels: Current="
                     << stat.current_channels_
                     << " Peak="
                     << stat.peak_channels_
                     << " Total="
                     << stat.total_channels_
                     << "\n";                    
                    
            }//for
        }//if cfg.seconds
    }//if rc > 0

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) ******** Before Cancel And Wait *************\n")
        ACE_TEXT ("Connector: PendingOP=%d\n"),
                connector.get_pending_count ()   // number_pending_connects
                ));
    manager.print_statistic ();

    // Initiate cancelation of  all pending AIO 
    connector.cancel ();    // Cancel Connector
    manager.close ();       // Cancel all active connections
    
    connector.wait ();      // Wait Connector
    manager.wait ();        // Wait for termination of all active connections
    
    time_end = ACE_OS::gettimeofday ();
    time_run = time_end - time_begin;

   
    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) ******** After  Cancel And Wait *************\n")
        ACE_TEXT ("Connector: PendingOP=%d\n"),
                connector.get_pending_count ()   // number_pending_connects
                ));
    manager.print_statistic ();

    // Calclulate average transmission rate
    manager.get_statistic(stat);

    float  fsec   = (float)(time_run.msec()/1000);
    double fspeed1 = ((float) stat.total_snd_
                    +(float) stat.total_rcv_
                    );

    double fspeed2 = ((float) stat.total_w_
                    +(float) stat.total_r_
                    );

    if ( fsec > 0.1 )
    {
        fspeed1 /= fsec; 
        fspeed2 /= fsec; 
    }

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective run time = %f sec\n"),
                fsec));


    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective bytes/sec = %f   op/sec= %f\n"),
                fspeed1,
                fspeed2));

    
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Threads = %d BlkSize=%d\n"),
                cfg.threads(),
                cfg.blksize()));

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Stopping Thread Pools\n")));

    task1.stop ();
     
    return 0;
}

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("Test"));

  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  // very important for POSIX, NO-OP for Windows
  BaseThreadPool::disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  BaseThreadPool::disable_signal (SIGPIPE, SIGPIPE);
  BaseThreadPool::disable_signal (SIGIO, SIGIO);


  int rc = run (argc,argv);

  ACE_END_TEST;

  return rc;
}

