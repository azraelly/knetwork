eval '(exit $?0)' && eval 'exec perl -w -S $0 ${1+"$@"}'
    & eval 'exec perl -w -S $0 $argv:q'
    if 0;

# ******************************************************************
#      Author: Chad Elliott
#        Date: 6/17/2002
#         $Id: mwc.pl 1094 2006-12-05 03:32:14Z elliott_c $
# ******************************************************************

# ******************************************************************
# Pragma Section
# ******************************************************************

require 5.006;

use strict;
use FindBin;
use File::Spec;
use File::Basename;

my($basePath) = $FindBin::Bin;
if ($^O eq 'VMS') {
  $basePath = File::Spec->rel2abs(dirname($0)) if ($basePath eq '');
  $basePath = VMS::Filespec::unixify($basePath);
}
unshift(@INC, $basePath . '/modules');

require Driver;

# ************************************************************
# Subroutine Section
# ************************************************************

sub getBasePath {
  return $basePath;
}

# ************************************************************
# Main Section
# ************************************************************

my($driver) = new Driver($basePath, basename($0));
exit($driver->run(@ARGV));
