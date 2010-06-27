#include "stdafx.h"
#include "Router.h"
#include "ConfigFile.h"

int run (int argc, ACE_TCHAR *argv[])
{
	std::string szConfigFile = "knet.cfg";
	CConfigFile Config(szConfigFile);
	if(Config.m_bFileNotFound)
    {
        ACE_ERROR((LM_ERROR, ACE_TEXT("config file %s is not found.\n"), szConfigFile.c_str()));
        return -1;
    }

	unsigned short usLocalPort = ACE_OS::atoi(Config.GetValue("", "routerport").c_str());

    // factory for TcpChannels
    TcpChannelFactory channel_factory;
  
	// IO Thread Pool for Channels, Acceptors
    IOThreadPool task1 ("IOThreadPool-1");

    // Channel Manager
    ChannelManager manager("Manager",          // name for logging
                           task1,              // IOThreadPool for channels
                           channel_factory);   // factory of channels
    ACE_Time_Value timeout (30, 0);
    manager.set_timeout (timeout);                  // set check timeout
    manager.open ();      

    CRcvFactory  r_factory ("RcvFactory");

    ChannelAcceptor  acceptor  (task1,              // IOThreadPool for accepting
                                r_factory,          // factory of protocols
                                manager);           // channel manager

    acceptor.set_log_level  (1);

    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

	if (task1.start (1) != 0)
    {
        return -1;
    }

    int rc = 0;
	ACE_INET_Addr listen_addr  (usLocalPort);
    if (acceptor.start (listen_addr, 20) == 0)
    {
        rc = 1;
    }

    time_begin = ACE_OS::gettimeofday ();

	CRouter Router(r_factory);
	if(Router.Connect() == false)
	{
		rc = -1;
	}

    ChannelManager::Statistic stat;

	if(rc > 0)
	{
        bool flgExit = false;
        for (;!flgExit;)
        {
            char c;
            cout << "\nEnter:"
                    << "\n2 - stop  acceptor"
                    << "\n3  -stop  manager"
                    << "\nP - statistic"
                    << "\nQ   quit=>" 
                    << flush;
            cin.clear ();
            cin >> c;
            switch (toupper (c))
            {
            case '2':
                acceptor.cancel ();
                acceptor.wait();
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
            cout << "\n*** Acceptor: PendingAccepts="
                    << acceptor.get_pending_count ()
                    << "\n*** Channels: Current="
                    << stat.current_channels_
                    << " Peak="
                    << stat.peak_channels_
                    << " Total="
                    << stat.total_channels_
                    << " BufferCount="
					<< r_factory.GetBufferCount()
                    << "\n";                    
                
        }//for
	}

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) ******** Before Cancel And Wait *************\n")
        ACE_TEXT ("Acceptor: PendingOP=%d\n"),
                acceptor.get_pending_count ()   // number_pending_accepts
                ));
    manager.print_statistic ();

	Router.ReleaseConnections();

    acceptor.cancel  ();    // Cancel Acceptor
    manager.close ();       // Cancel all active connections
    
    acceptor.wait ();       // Wait Acceptor
    manager.wait ();        // Wait for termination of all active connections


    time_end = ACE_OS::gettimeofday ();
    time_run = time_end - time_begin;

   
    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) ******** After  Cancel And Wait *************\n")
        ACE_TEXT ("Acceptor: PendingOP=%d\n"),
                acceptor.get_pending_count ()   // number_pending_accepts
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
                ACE_TEXT ("(%t) Stopping Thread Pools\n")));

    task1.stop ();

	return 0;
}

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("Krouter"));

  // very important for POSIX, NO-OP for Windows
  BaseThreadPool::disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  BaseThreadPool::disable_signal (SIGPIPE, SIGPIPE);
  BaseThreadPool::disable_signal (SIGIO, SIGIO);


  int rc = run (argc,argv);

  ACE_END_TEST;

  return rc;
}
