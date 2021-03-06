package VC6WorkspaceCreator;

# ************************************************************
# Description   : A VC6 Workspace Creator
# Author        : Chad Elliott
# Create Date   : 5/13/2002
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;

use VC6ProjectCreator;
use WinWorkspaceBase;
use WorkspaceCreator;

use vars qw(@ISA);
@ISA = qw(WinWorkspaceBase WorkspaceCreator);

# ************************************************************
# Subroutine Section
# ************************************************************


sub compare_output {
  #my($self) = shift;
  return 1;
}


sub workspace_file_extension {
  #my($self) = shift;
  return '.dsw';
}


sub pre_workspace {
  my($self) = shift;
  my($fh)   = shift;
  my($crlf) = $self->crlf();

  print $fh 'Microsoft Developer Studio Workspace File, Format Version 6.00', $crlf;
  $self->print_workspace_comment($fh,
            '#', $crlf,
            '# $Id: VC6WorkspaceCreator.pm 1145 2007-02-26 17:31:52Z elliott_c $', $crlf,
            '#', $crlf,
            '# This file was generated by MPC.  Any changes made directly to', $crlf,
            '# this file will be lost the next time it is generated.', $crlf,
            '#', $crlf,
            '# MPC Command:', $crlf,
            '# ', $self->create_command_line_string($0, @ARGV), $crlf, $crlf);
}


sub write_comps {
  my($self)     = shift;
  my($fh)       = shift;
  my($gen)      = shift;
  my($projects) = $self->get_projects();
  my($pjs)      = $self->get_project_info();
  my($crlf)     = $self->crlf();

  foreach my $project (sort { $gen->file_sorter($a, $b) } @$projects) {
    my($name) = $$pjs{$project}->[0];
    my($deps) = $self->get_validated_ordering($project);

    print $fh "###############################################################################$crlf" .
              $crlf .
              "Project: \"$name\"=" . $self->slash_to_backslash($project) .
              " - Package Owner=<4>$crlf" .
              $crlf .
              "Package=<5>$crlf" .
              "{{{$crlf" .
              "}}}$crlf" .
              $crlf .
              "Package=<4>$crlf" .
              "{{{$crlf";

    if (defined $$deps[0]) {
      foreach my $dep (@$deps) {
        print $fh "    Begin Project Dependency$crlf" .
                  "    Project_Dep_Name $dep$crlf" .
                  "    End Project Dependency$crlf";
      }
    }

    print $fh "}}}$crlf$crlf";
  }
}


sub post_workspace {
  my($self) = shift;
  my($fh)   = shift;
  my($crlf) = $self->crlf();

  print $fh "###############################################################################$crlf" .
            $crlf .
            "Global:$crlf" .
            $crlf .
            "Package=<5>$crlf" .
            "{{{$crlf" .
            "}}}$crlf" .
            $crlf .
            "Package=<3>$crlf" .
            "{{{$crlf" .
            "}}}$crlf" .
            $crlf .
            "###############################################################################$crlf" .
            $crlf;
}


1;
