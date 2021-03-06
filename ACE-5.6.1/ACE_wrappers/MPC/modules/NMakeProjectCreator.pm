package NMakeProjectCreator;

# ************************************************************
# Description   : An NMake Project Creator
# Author        : Chad Elliott
# Create Date   : 5/31/2002
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;

use ProjectCreator;
use WinProjectBase;
use MakeProjectBase;

use vars qw(@ISA);
@ISA = qw(MakeProjectBase WinProjectBase ProjectCreator);

# ************************************************************
# Subroutine Section
# ************************************************************

sub project_file_extension {
  #my($self) = shift;
  return '.mak';
}


sub get_dll_exe_template_input_file {
  #my($self) = shift;
  return 'nmakeexe';
}


sub get_dll_template_input_file {
  #my($self) = shift;
  return 'nmakedll';
}


1;
