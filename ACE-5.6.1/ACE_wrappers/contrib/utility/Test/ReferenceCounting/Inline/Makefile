# file      : Test/ReferenceCounting/Inline/Makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2002-2003 Boris Kolpackov
# license   : http://kolpackov.net/license.html

root := ../../..

include $(root)/BuildRules/Bootstrap.rules

$(call include, $(root)/BuildRules/Executable.pre.rules)


cxx_translation_units := inline.cpp unit.cpp

module_base           := inline
module_prefix         :=
module_suffix         :=


CXX_PREPROCESS_FLAGS  += -I $(root)


$(call include, $(root)/BuildRules/Executable.post.rules)
# $Id: Makefile 66067 2005-05-24 04:33:13Z turkaye $
