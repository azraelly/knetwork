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

all: UDP_Broadcast UDP_Multicast UDP_Unicast

REMAINING_TARGETS := $(subst all, , $(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)

$(REMAINING_TARGETS):
	@$(MAKE) -f GNUmakefile.UDP_Broadcast $(@)
	@$(MAKE) -f GNUmakefile.UDP_Multicast $(@)
	@$(MAKE) -f GNUmakefile.UDP_Unicast $(@)

.PHONY: UDP_Broadcast
UDP_Broadcast:
	@$(MAKE) -f GNUmakefile.UDP_Broadcast all

.PHONY: UDP_Multicast
UDP_Multicast:
	@$(MAKE) -f GNUmakefile.UDP_Multicast all

.PHONY: UDP_Unicast
UDP_Unicast:
	@$(MAKE) -f GNUmakefile.UDP_Unicast all

project_name_list:
	@echo UDP_Broadcast
	@echo UDP_Multicast
	@echo UDP_Unicast
