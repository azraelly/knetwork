// $Id: createfile.cpp 79056 2007-07-29 21:01:01Z sowayaa $

#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_string.h"
#include "ace/ACE.h"

ACE_RCSID(Dump_Restore, createfile, "$Id: createfile.cpp 79056 2007-07-29 21:01:01Z sowayaa $")

int 
main (int argc, char **argv)
{
  FILE *infile, *outfile;
  char buf[BUFSIZ];

  if ((infile = ACE_OS::fopen (argv[1], "r")) == 0)
    return -1;

  if ((outfile = ACE_OS::fopen (argv[2], "w")) == 0)
    return -1;

  int count = 0;
  while (ACE_OS::fgets (buf, BUFSIZ, infile))
    {
      buf[ACE_OS::strlen(buf) - 1] = '\0';
      ACE_OS::fputs (buf, outfile);
      if (count % 2 == 0)
        ACE_OS::fputs (" ", outfile);
      else
        ACE_OS::fputs ("\n", outfile);
      count++;
    }

  ACE_OS::fclose (outfile);
  ACE_OS::fclose (infile);
}
