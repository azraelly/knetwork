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

all: Connection_Blocking_Acceptor Connection_Blocking_Connector

REMAINING_TARGETS := $(subst all, , $(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	@$(MAKE) -f GNUmakefile.Connection_Blocking_Acceptor $(@)
	@$(MAKE) -f GNUmakefile.Connection_Blocking_Connector $(@)

.PHONY: Connection_Blocking_Acceptor
Connection_Blocking_Acceptor:
	@$(MAKE) -f GNUmakefile.Connection_Blocking_Acceptor all

.PHONY: Connection_Blocking_Connector
Connection_Blocking_Connector:
	@$(MAKE) -f GNUmakefile.Connection_Blocking_Connector all

project_name_list:
	@echo Connection_Blocking_Acceptor
	@echo Connection_Blocking_Connector
