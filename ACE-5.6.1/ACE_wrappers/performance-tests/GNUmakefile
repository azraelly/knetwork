# -*- makefile -*-
#----------------------------------------------------------------------------
#       GNU ACE Workspace
#
# $Id: GNUACEWorkspaceCreator.pm 77499 2007-03-02 18:19:05Z elliott_c $
#
# This file was generated by MPC.  Any changes made directly to
# this file will be lost the next time it is generated.
#
# MPC Command:
# /export/anduriltmp/bczar/DOC_ROOT/stage-29192/ACE_wrappers/bin/mwc.pl -type gnuace -exclude TAO/TAO_*.mwc,TAO/CIAO/CIAO_*.mwc -recurse -hierarchy -relative ACE_ROOT=/export/anduriltmp/bczar/DOC_ROOT/stage-29192/ACE_wrappers -relative TAO_ROOT=/export/anduriltmp/bczar/DOC_ROOT/stage-29192/ACE_wrappers/TAO -relative CIAO_ROOT=/export/anduriltmp/bczar/DOC_ROOT/stage-29192/ACE_wrappers/TAO/CIAO
#
#----------------------------------------------------------------------------

MAKEFILE = GNUmakefile

ifeq ($(findstring k,$(MAKEFLAGS)),k)
  KEEP_GOING = -
endif

include $(ACE_ROOT)/include/makeinclude/macros.GNU

all: Misc_Basic_Perf Misc_Childbirth_Time Misc_Context_Switch_Time Misc_Preempt Misc_Test_Mutex Misc_Test_Naming Misc_Test_Singleton SCTP_SOCK_SEQPACK_Association_Test SCTP_SOCK_STREAM_Srv SCTP_SOCK_STREAM_Clt SCTP_SOCK_SEQPACK_Clt SCTP_SOCK_SEQPACK_Srv Svr_Conc_Leader_Follower Svr_Conc_Leader_Follower_RT_CORBA Svr_Conc_Queue_Based_Workers Svr_Conc_Queue_Based_Workers_RTCorba Synch_Lib Synch_Benchmarks_Base_Test Synch_Benchmarks Synch_Benchmarks_Perf_Test TCP-target UDP-target

REMAINING_TARGETS := $(subst all, , $(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Basic_Perf $(@)
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Childbirth_Time $(@)
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Context_Switch_Time $(@)
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Preempt $(@)
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Test_Mutex $(@)
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Test_Naming $(@)
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Test_Singleton $(@)
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_SEQPACK_Association_Test $(@)
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_STREAM_Srv $(@)
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_STREAM_Clt $(@)
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_SEQPACK_Clt $(@)
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_SEQPACK_Srv $(@)
	@cd Server_Concurrency/Leader_Follower && $(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower $(@)
	@cd Server_Concurrency/Leader_Follower && $(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower_RT_CORBA $(@)
	@cd Server_Concurrency/Queue_Based_Workers && $(MAKE) -f GNUmakefile.Svr_Conc_Queue_Based_Workers $(@)
	@cd Server_Concurrency/Queue_Based_Workers && $(MAKE) -f GNUmakefile.Svr_Conc_Queue_Based_Workers_RTCorba $(@)
	@cd Synch-Benchmarks/Synch_Lib && $(MAKE) -f GNUmakefile.Synch_Lib $(@)
	@cd Synch-Benchmarks/Base_Test && $(MAKE) -f GNUmakefile.Synch_Benchmarks_Base_Test $(@)
	@cd Synch-Benchmarks && $(MAKE) -f GNUmakefile.Synch_Benchmarks $(@)
	@cd Synch-Benchmarks/Perf_Test && $(MAKE) -f GNUmakefile.Synch_Benchmarks_Perf_Test $(@)
	@cd TCP && $(MAKE) -f GNUmakefile.TCP $(@)
	@cd UDP && $(MAKE) -f GNUmakefile.UDP $(@)

.PHONY: Misc_Basic_Perf
Misc_Basic_Perf:
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Basic_Perf all

.PHONY: Misc_Childbirth_Time
Misc_Childbirth_Time:
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Childbirth_Time all

.PHONY: Misc_Context_Switch_Time
Misc_Context_Switch_Time:
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Context_Switch_Time all

.PHONY: Misc_Preempt
Misc_Preempt:
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Preempt all

.PHONY: Misc_Test_Mutex
Misc_Test_Mutex:
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Test_Mutex all

.PHONY: Misc_Test_Naming
Misc_Test_Naming:
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Test_Naming all

.PHONY: Misc_Test_Singleton
Misc_Test_Singleton:
	@cd Misc && $(MAKE) -f GNUmakefile.Misc_Test_Singleton all

.PHONY: SCTP_SOCK_SEQPACK_Association_Test
SCTP_SOCK_SEQPACK_Association_Test:
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_SEQPACK_Association_Test all

.PHONY: SCTP_SOCK_STREAM_Srv
SCTP_SOCK_STREAM_Srv:
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_STREAM_Srv all

.PHONY: SCTP_SOCK_STREAM_Clt
SCTP_SOCK_STREAM_Clt: SCTP_SOCK_STREAM_Srv
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_STREAM_Clt all

.PHONY: SCTP_SOCK_SEQPACK_Clt
SCTP_SOCK_SEQPACK_Clt: SCTP_SOCK_STREAM_Srv SCTP_SOCK_STREAM_Clt
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_SEQPACK_Clt all

.PHONY: SCTP_SOCK_SEQPACK_Srv
SCTP_SOCK_SEQPACK_Srv: SCTP_SOCK_STREAM_Srv
	@cd SCTP && $(MAKE) -f GNUmakefile.SCTP_SOCK_SEQPACK_Srv all

.PHONY: Svr_Conc_Leader_Follower
Svr_Conc_Leader_Follower:
	@cd Server_Concurrency/Leader_Follower && $(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower all

.PHONY: Svr_Conc_Leader_Follower_RT_CORBA
Svr_Conc_Leader_Follower_RT_CORBA:
	@cd Server_Concurrency/Leader_Follower && $(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower_RT_CORBA all

.PHONY: Svr_Conc_Queue_Based_Workers
Svr_Conc_Queue_Based_Workers:
	@cd Server_Concurrency/Queue_Based_Workers && $(MAKE) -f GNUmakefile.Svr_Conc_Queue_Based_Workers all

.PHONY: Svr_Conc_Queue_Based_Workers_RTCorba
Svr_Conc_Queue_Based_Workers_RTCorba:
	@cd Server_Concurrency/Queue_Based_Workers && $(MAKE) -f GNUmakefile.Svr_Conc_Queue_Based_Workers_RTCorba all

.PHONY: Synch_Lib
Synch_Lib:
	@cd Synch-Benchmarks/Synch_Lib && $(MAKE) -f GNUmakefile.Synch_Lib all

.PHONY: Synch_Benchmarks_Base_Test
Synch_Benchmarks_Base_Test: Synch_Lib
	@cd Synch-Benchmarks/Base_Test && $(MAKE) -f GNUmakefile.Synch_Benchmarks_Base_Test all

.PHONY: Synch_Benchmarks
Synch_Benchmarks: Synch_Lib
	@cd Synch-Benchmarks && $(MAKE) -f GNUmakefile.Synch_Benchmarks all

.PHONY: Synch_Benchmarks_Perf_Test
Synch_Benchmarks_Perf_Test: Synch_Lib
	@cd Synch-Benchmarks/Perf_Test && $(MAKE) -f GNUmakefile.Synch_Benchmarks_Perf_Test all

.PHONY: TCP-target
TCP-target:
	@cd TCP && $(MAKE) -f GNUmakefile.TCP all

.PHONY: UDP-target
UDP-target:
	@cd UDP && $(MAKE) -f GNUmakefile.UDP all

project_name_list:
	@echo Misc_Basic_Perf
	@echo Misc_Childbirth_Time
	@echo Misc_Context_Switch_Time
	@echo Misc_Preempt
	@echo Misc_Test_Mutex
	@echo Misc_Test_Naming
	@echo Misc_Test_Singleton
	@echo SCTP_SOCK_SEQPACK_Association_Test
	@echo SCTP_SOCK_SEQPACK_Clt
	@echo SCTP_SOCK_SEQPACK_Srv
	@echo SCTP_SOCK_STREAM_Clt
	@echo SCTP_SOCK_STREAM_Srv
	@echo Svr_Conc_Leader_Follower
	@echo Svr_Conc_Leader_Follower_RT_CORBA
	@echo Svr_Conc_Queue_Based_Workers
	@echo Svr_Conc_Queue_Based_Workers_RTCorba
	@echo Synch_Benchmarks_Base_Test
	@echo Synch_Benchmarks
	@echo Synch_Benchmarks_Perf_Test
	@echo Synch_Lib
	@echo TCP-target
	@echo UDP-target
