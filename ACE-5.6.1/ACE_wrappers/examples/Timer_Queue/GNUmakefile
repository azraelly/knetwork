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

all: Timer_Queue_Library Timer_Queue_Async Timer_Queue_Reactor Timer_Queue_Thread

REMAINING_TARGETS := $(subst all, , $(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	@$(MAKE) -f GNUmakefile.Timer_Queue_Library $(@)
	@$(MAKE) -f GNUmakefile.Timer_Queue_Async $(@)
	@$(MAKE) -f GNUmakefile.Timer_Queue_Reactor $(@)
	@$(MAKE) -f GNUmakefile.Timer_Queue_Thread $(@)

.PHONY: Timer_Queue_Library
Timer_Queue_Library:
	@$(MAKE) -f GNUmakefile.Timer_Queue_Library all

.PHONY: Timer_Queue_Async
Timer_Queue_Async: Timer_Queue_Library
	@$(MAKE) -f GNUmakefile.Timer_Queue_Async all

.PHONY: Timer_Queue_Reactor
Timer_Queue_Reactor: Timer_Queue_Library
	@$(MAKE) -f GNUmakefile.Timer_Queue_Reactor all

.PHONY: Timer_Queue_Thread
Timer_Queue_Thread: Timer_Queue_Library
	@$(MAKE) -f GNUmakefile.Timer_Queue_Thread all

project_name_list:
	@echo Timer_Queue_Async
	@echo Timer_Queue_Library
	@echo Timer_Queue_Reactor
	@echo Timer_Queue_Thread
