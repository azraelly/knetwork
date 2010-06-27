# $Id: platform_irix6.x_common.GNU 79422 2007-08-21 07:08:28Z johnnyw $

xt_reactor ?= 1
exceptions ?= 1
debug ?= 1
optimize ?= 1

PLATFORM_XT_CPPFLAGS=
PLATFORM_XT_LIBS=-lXm -lXt -lX11
PLATFORM_XT_LDFLAGS=

ifndef ACE_IRIX_VERS
ACE_IRIX_VERS       := $(subst .,,$(shell uname -r))
endif # ACE_IRIX_VERS

CPPFLAGS += -DACE_IRIX_VERS=$(ACE_IRIX_VERS)
