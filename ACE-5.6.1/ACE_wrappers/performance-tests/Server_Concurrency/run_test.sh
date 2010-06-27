#!/bin/sh
#
# $Id: run_test.sh 24451 1999-06-14 21:46:14Z coryan $
#

for s in 0 25 50 75 100; do
  for w in 1 2 3 4 5 6; do
    echo ================ WORK: $s 1>&2
    echo ================ THREADS: $w 1>&2
    ./Queue_Based_Workers/workers -m 100000 -b 100000 -s $s -w $w
    ./Leader_Follower/leader_follower -m 100000 -b 100000 -s $s -w $w
  done
done
