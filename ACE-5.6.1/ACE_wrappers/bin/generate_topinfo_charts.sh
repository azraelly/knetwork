#!/bin/sh
#
# $Id: generate_topinfo_charts.sh 70668 2006-01-26 13:21:00Z jwillemsen $
#

gnuplot <<_EOF_ >/dev/null 2>&1
  set xdata time
  set timefmt '%Y/%m/%d-%H:%M'
  set xlabel 'Date (MM/DD)'
  set ylabel 'Size (KBytes) $4'
  set terminal png small size 800,600 color
  set output "$2"
  plot '$1' using 1:2 title '$3' w l
  exit
_EOF_

