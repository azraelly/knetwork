# file      : Test/ReferenceCounting/Makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2002-2003 Boris Kolpackov
# license   : http://kolpackov.net/license.html

root := ../..

include $(root)/BuildRules/Bootstrap.rules

$(call include, $(root)/BuildRules/Recursion.pre.rules)

target_makefile_list  :=
target_directory_list := Interface DefaultImpl Inline SmartPtr StrictPtr

$(call include, $(root)/BuildRules/Recursion.post.rules)
# $Id: Makefile 66067 2005-05-24 04:33:13Z turkaye $
