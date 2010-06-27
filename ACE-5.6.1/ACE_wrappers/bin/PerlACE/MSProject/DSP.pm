# $Id: DSP.pm 37875 2001-03-01 21:39:06Z brunsch $

package PerlACE::MSProject::DSP;

use strict;
use PerlACE::MSProject;

our @ISA = ("PerlACE::MSProject");

###############################################################################

# Constructor

sub new  
{
    my $proto = shift;
    my $class = ref ($proto) || $proto;
    my $self = $class->SUPER::new (@_);
    
    $self->{COMPILER} = "msdev.com";

    bless ($self, $class);
    return $self;
}

###############################################################################

1;