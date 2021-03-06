# -*- Makefile -*-

#----------------------------------------------------------------------------
#       $Id: rules.bin.GNU 76121 2006-12-21 12:11:59Z johnnyw $
#
#       Build binaries
#       GNU version
#       Requires GNU make
#----------------------------------------------------------------------------

ifdef BIN
  VBIN = $(BIN:%=%$(VAR))
  # VBIN always depends on idl_stubs and libraries, if they exist.
  ifdef IDL_SRC
    $(VBIN): $(IDL_SRC)
  endif
  ifdef VLIBS
    $(VBIN): $(LIB_INSTALL) $(VLIBS)
  endif
else # !BIN
  ifndef BIN_UNCHECKED
    @echo Warning: rules.bin.GNU included, but no BIN targets detected.
  endif # !BIN_UNCHECKED
endif # BIN

VOBJS = $(addsuffix .$(OBJEXT),$(addprefix $(VDIR),$(basename $(SRC))))

ifneq ($(IDL_SRC),)
  $(VBIN): $(IDL_SRC)
endif

# Needed for depend.
PSRC += $(addsuffix .cpp, $(CLEANUP_BIN))

CLEANUP_INSTALL += $(CLEANUP_BIN:%=$(INSBIN)/%$(VAR)$(EXEEXT))

CHORUSLINK ?=
VXWORKSLINK ?=
using_aix_vacpp ?=

ifeq ($(VXWORKSLINK),true)
$(BIN): $(DEFAULTRULE)
	mv $(DEFAULTRULE) $@
else # !VXWORKSLINK
  ifeq (1,$(using_aix_vacpp))
$(BIN): %: %.icc $(SRC)
	vacbld_r $< -severitylevel=warning
  else # !using_aix_vacpp
$(BIN): %: $(VDIR)%.$(OBJEXT) $(VOBJS)
	$(LINK.cc) $(LDFLAGS) $(CC_OUTPUT_FLAG) $@ $(sort $(VDIR)$@.$(OBJEXT) $(VOBJS)) $(VLDLIBS) $(POSTLINK)
  endif # using_aix_vacpp
endif
