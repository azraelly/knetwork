eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 76543 2007-01-24 12:33:06Z johnnyw $
# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::Run_Test;

$TEST = new PerlACE::Process ("test");

$status = $TEST->SpawnWaitKill (20);

$status = 1 if ($status < 0);

exit $status;
