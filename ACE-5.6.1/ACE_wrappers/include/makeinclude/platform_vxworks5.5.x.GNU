# $Id: platform_vxworks5.5.x.GNU 79409 2007-08-20 12:29:21Z johnnyw $
# VxWorks 5.5.x (x > 0).

#### Notes:
#### 1) This file requires that the WIND_BASE and WIND_HOST_TYPE environment
####    variables be set.  If the target CPU is not SIMNT, then your CPU
####    environment variable must be set.
#### 2) If you have problems with munch output not being compilable
####    because it contains identifiers with ".", e.g., ".cpp", in them:
####    add a global variable or function to that .cpp file.  See
####    ace/IOStream_T.cpp for an explanation and example.
#### 3) The TOOL environment variable may be set to "diab" (default is "gnu").
#### 4) If perl is not on your path, you'll also need to set your PERL_PATH
####    environment variable to the full path to perl.

VXWORKS = 1
CROSS-COMPILE = 1

ifneq (,$(HOST_ROOT))
  TAO_IDL := $(HOST_ROOT)/bin/tao_idl.exe
  TAO_IDL_DEP := $(TAO_IDL)
  TAO_IDLFLAGS += -g $(HOST_ROOT)/bin/gperf
endif

debug ?= 1
optimize ?= 1
threads ?= 1
exceptions ?= 1
xerces ?= 0

ifeq ($(static_libs),1)
  shared_libs = 0
else
  static_libs = 0
endif
versioned_so ?= 0

# VxWorks doesn't have rwho
rwho = 0

ifeq (,$(WIND_BASE))
  default:
	@ERROR: you must set your WIND_BASE environment variable
endif # WIND_BASE

ifeq (,$(WIND_HOST_TYPE))
  default:
	@ERROR: you must set your WIND_HOST_TYPE environment variable
endif # WIND_HOST_TYPE

ifeq ("$(WIND_HOST_TYPE)","x86-win32")
ifneq ($(MAKE_MODE), unix)
vxworks_ntbuild = 1
MKDIR_NTSTYLE = 1
lacks_touch = 1
endif
endif

HOST_DIR = $(WIND_BASE)/host/$(WIND_HOST_TYPE)

ifeq (,$(PERL_PATH))
  PERL_PATH = perl
endif # ! PERL_PATH

ifeq ($(VXWORKS_VERSION_FLAG),)
  VXWORKS_VERSION_FLAG = -DACE_VXWORKS=0x551
endif # VXWORKS_VERSION_FLAG

ifeq ($(TOOL),)
  override TOOL = gnu
else
  override TOOL := $(TOOL)
endif
override TOOL_FAMILY := $(TOOL)

ifeq ("$(TOOL)","gnu")
  templates ?= automatic
endif

PRJ_TYPE = vxApp
TARGET_DIR = $(WIND_BASE)/target/h
TGT_DIR = $(WIND_BASE)/target

ifeq ($(CPU),)
  # default CPU
  CPU = SIMNT
else
  override CPU := $(CPU)
endif

ifeq ($(findstring PPC, $(CPU)), PPC)
  CCFLAGS += -mlongcall
endif

ifeq ($(shared_libs),1)
  SHARED_LIBS = 1
endif
ifeq ($(shared_libs_only),1)
  SHARED_LIBS = 1
endif

ifeq ($(SHARED_LIBS),1)
  ACELIB = -L./
  #### There's no difference between non-shared and shared object code.
  VSHDIR = $(VDIR)
endif # shared_libs

BIN_UNCHECKED ?=
SHLIB_UNCHECKED ?=

ifneq ("$(BIN_UNCHECKED)","")
VX_APP_BUILD := 1
else
  ifeq ($(SHARED_LIBS),1)
    ifneq ("$(SHLIB_UNCHECKED)","")
	  VX_SO_BUILD := 1
    endif
  endif
  ifneq ($(VX_SO_BUILD),1)
    VX_LIB_BUILD := 1
  endif
endif

ifneq ($(VX_LIB_BUILD),1)
  VXWORKSLINK = true
  ifeq ($(VX_APP_BUILD),1)
    ## set variables for VxWorks linktarget identification
    PRJ_FILE = $(basename $(notdir $(BIN_UNCHECKED))).vxworks
    EXEEXT = .out
    PRJ_DIR = .
    CLEANUP_OBJS := ctdt.c $(PRJ_DIR)/$(PRJ_FILE) $(CLEANUP_OBJS)
  else
    ## set variables for VxWorks .SO linktarget identification
    PRJ_FILE = $(basename $(notdir $(SHLIB_UNCHECKED))).vxworks
    PRJ_DIR = .
    CLEANUP_OBJS := ctdt.c $(PRJ_DIR)/$(PRJ_FILE) *.out $(CLEANUP_OBJS)
  endif
endif

include $(TARGET_DIR)/make/defs.default
include $(TARGET_DIR)/make/defs.$(WIND_HOST_TYPE)
include $(TARGET_DIR)/make/defs.$(PRJ_TYPE)
include $(TARGET_DIR)/tool/$(TOOL_FAMILY)/make.$(CPU)$(TOOL)

## make sure we don't use that stupid, crippled vxrm.bat script.
override RM=rm -f

ifeq ("$(VXWORKSLINK)","true")
  # prevent possible clash with static LIB rules
  # in VxWorks make includes and rules.lib.GNU
  override ARCHIVE =
  override LARGE_PROJECT =
  PRJ_OBJS = $(addprefix $(VDIR), $(OBJS)) $(VSHOBJS)
  ifeq ($(SHARED_LIBS),1)
    ##LD_PARTIAL += -L$(ACE_ROOT)/lib -L./ $(LDLIBPATH) $(LD_LINK_PATH)
    PRJ_OBJS_FOR_LD_PARTIAL=$(addprefix $(VDIR), $(OBJS)) $(VSHOBJS)
	  ifeq ($(VX_SO_BUILD),1)
	  ## Shared lib builds for VxWorks will also build 'import' libraries
    LIB_INSTALL += $(VLIB:%=$(INSLIB)/%)
    CLEANUP_INSTALL += $(CLEANUP_VLIB:%=$(INSLIB)/%)
	  REALCLEAN_FILES += $(CLEANUP_LIB:%=%) $(CLEANUP_LIB:%=%_debug) $(CLEANUP_LIB:%=%_profile) $(CLEANUP_LIB:%=%_optimize)
	  endif
  else
    LD_PARTIAL += -L$(ACE_ROOT)/ace -L./ $(LDLIBPATH) $(LD_LINK_PATH)
    ifeq (1,$(repo))
    PRJ_OBJS_FOR_LD_PARTIAL=$(addprefix $(VDIR), $(OBJS)) $(VSHOBJS) $(shell set AR=$(AR) && set RANLIB=$(RANLIB) && perl $(ACE_ROOT)/bin/vx_repo_link.pl $(VLDLIBS)) $(ACE_SHLIBS)
    ifneq (1,$(VX_KEEP_PRELINK_LIB))
      POSTLINK = rmdir /s/q .lib && rmdir /s/q $(subst /,\,$(VDIR))
      REALCLEAN_FILES += .lib
    else
      POSTLINK = rmdir /s/q $(subst /,\,$(VDIR))
    endif
    else
    PRJ_OBJS_FOR_LD_PARTIAL=$(addprefix $(VDIR), $(OBJS)) $(VSHOBJS) $(VLDLIBS) $(ACE_SHLIBS)
    endif
  endif
  PRJ_OBJS_FOR_LD=$(addprefix $(VDIR), $(OBJS)) $(VSHOBJS)
  PRJ_OBJS_FOR_NM=$(addprefix $(VDIR), $(OBJS)) $(VSHOBJS)
  PRJ_OBJS_FOR_AR=$(addprefix $(VDIR), $(OBJS)) $(VSHOBJS)
  POST_BUILD_RULE = $(POSTLINK)
  COMPILE_TRADITIONAL = $(CC) $(OPTION_OBJECT_ONLY) $(OPTION_DOLLAR_SYMBOLS)\
			  $(filter-out -ansi, $(CFLAGS))

  ## make sure default target stays the ACE/TAO default target
  ##
default: all

endif

CPPFLAGS += $(VXWORKS_VERSION_FLAG)

ifeq ($(debug),1)
  DCFLAGS += -g
  DCCFLAGS += -g
  CPPFLAGS +=
endif

ifeq ("$(TOOL)","gnu")
# Test for template instantiation, add to SOFLAGS if SONAME set,
# add -E to LDFLAGS if using GNU ld
include $(ACE_ROOT)/include/makeinclude/platform_g++_common.GNU

ifeq ("$(templates)","automatic")
	ifdef repo
		ifeq ("$(VXWORKSLINK)","true")
  		ifeq ($(VX_APP_BUILD),1)
				ifneq ($(SHARED_LIBS),1)
      	LD_PARTIAL += -frepo
				endif
  		endif
		else
  	#ace_lib_prelink := 1
  	  LINK.cc          = override
  	  LINK.cc.override = $(LD_PARTIAL) -frepo
  	  LDFLAGS          = $(ACE_SHLIBS)
		endif
	else
  C++FLAGS += -fmerge-templates
	endif
endif

# TEMPLATES_FLAG is set by platform_g++_common.GNU
ifneq ($(TEMPLATES_FLAG),) # If specified, add it to the CCFLAGS
  CPPFLAGS += $(TEMPLATES_FLAG)
endif
endif  # TOOL == gnu

ifeq ("$(TOOL)","diab")
ifeq ($(exceptions),1)
  C++FLAGS += -Xexceptions
else
  C++FLAGS += -Xexceptions-off
endif
else
ifeq ("$(TOOL)","gnu")
C++FLAGS += -ftemplate-depth-50
ifeq ($(exceptions),1)
  C++FLAGS += -fexceptions
else
  C++FLAGS += -fno-exceptions
endif
endif
endif

ifneq ($(findstring $(VX_CPU_FAMILY),ppc arm),)
ifeq ("$(TOOL)","diab")
  C++FLAGS += -Xchar-signed
else
ifeq ("$(TOOL)","gnu")
  C++FLAGS += -fsigned-char
endif
endif
endif

ifeq ($(CPU),SIMNT)
override MUNCH_FLAGS := -asm $(TOOLENV)
endif

ifneq ($(optimize),1)
  CC_OPTIM_NORMAL =
endif

CCFLAGS         += $(C++FLAGS)

PIC              =

ifeq ("$(VXWORKSLINK)","true")

  ifdef repo
    ifeq ($(SHARED_LIBS),1)
      BACKUP_RPO_RULE = for %f in ($(basename $(addprefix $(VDIR), $(OBJS)) $(VSHOBJS))) do if exist %f.rpo mv %f.rpo %f.rpobak $(ACE_NUL_STDERR)
      POST_BUILD_RULE = for %f in ($(basename $(addprefix $(VDIR), $(OBJS)) $(VSHOBJS))) do if exist %f.rpobak mv %f.rpobak %f.rpo $(ACE_NUL_STDERR)
    endif
  endif

.PHONY: $(PRJ_DIR)/$(PRJ_FILE)
  ## special target to satisfy VxWorks dependencies for images
$(PRJ_DIR)/$(PRJ_FILE):
  ifdef repo
    ifeq ($(SHARED_LIBS),1)
    #### execute prelink step to make compiler instantiate all needed
    #### templates; discard image and repo files (*.rpo) after linkstep
    #### this step holds for both .SO as well as 'app' images so use both VSHOBJS and OBJS
	-$(LD_PARTIAL) -frepo -L$(ACE_ROOT)/ace -L./ $(LDLIBPATH) $(LD_LINK_PATH)$(LINK_OUTPUT_FLAG) ace-templ_inst $? $(ACE_SHLIBS) $(addprefix $(VDIR), $(OBJS)) $(VSHOBJS)
	-$(RM) ace-templ_inst
    #### We need to backup the .RPO files or otherwise the link step of the final image will
    #### start instantiating templates again even if we do not specify '-frepo'!
	-$(BACKUP_RPO_RULE)
      ifeq ($(VX_SO_BUILD),1)
    #### build library of objects in .SO to use as a sort of import library for VxWorks
	echo $(filter %.o, $(VSHOBJS)) | xargs $(AR) $(ARFLAGS) $(VLIB) $(AREXTRA)
	-chmod a+r $(VLIB)
        ifneq (,$(RANLIB))
	-$(RANLIB) $(VLIB)
        endif # RANLIB
      endif # VX_SO_BUILD
    endif
  endif
	@echo 1>$@

endif
