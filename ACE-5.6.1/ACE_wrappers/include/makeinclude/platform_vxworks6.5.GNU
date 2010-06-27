# $Id: platform_vxworks6.5.GNU 78478 2007-05-24 08:30:14Z johnnyw $
# VxWorks 6.5

ifeq ($(VXWORKS_VERSION_FLAG),)
  VXWORKS_VERSION_FLAG = -DACE_VXWORKS=0x650
endif # VXWORKS_VERSION_FLAG

include $(ACE_ROOT)/include/makeinclude/platform_vxworks6.4.GNU
