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

all: Svr_Conc_Leader_Follower Svr_Conc_Leader_Follower_RT_CORBA

REMAINING_TARGETS := $(subst all, , $(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	@$(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower $(@)
	@$(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower_RT_CORBA $(@)

.PHONY: Svr_Conc_Leader_Follower
Svr_Conc_Leader_Follower:
	@$(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower all

.PHONY: Svr_Conc_Leader_Follower_RT_CORBA
Svr_Conc_Leader_Follower_RT_CORBA:
	@$(MAKE) -f GNUmakefile.Svr_Conc_Leader_Follower_RT_CORBA all

project_name_list:
	@echo Svr_Conc_Leader_Follower
	@echo Svr_Conc_Leader_Follower_RT_CORBA
