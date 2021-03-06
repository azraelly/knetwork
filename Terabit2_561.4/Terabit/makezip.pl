use Cwd;
use File::Basename;
use File::Copy;
use File::Find;
use Config;
use strict;

my  @files;
my  $dirname;
my  $dirbasename ;

sub wanted
{
        if ( m/\.cpp$/   ||
         m/\.cpp.1$/     ||
         m/\.h.1$/     ||
         m/\.h$/     ||
         m/\.c$/     ||
         m/\.i$/     ||
         m/\.inl$/   ||
         m/\.mpc$/   ||
         m/\.mpb$/   ||
         m/\.mwc$/   ||
         m/\.pem$/   ||
         m/\.sh$/    ||
         m/\.bat$/   ||
         m/\.xml$/   ||
         m/\.conf$/  ||
         m/\.cfg$/   ||
         m/\.txt$/   ||
         m/\.doc$/   ||
         m/\.txt$/   ||
         m/\.mk$/    ||
         m/\.pm$/    ||
         m/\.pl$/    )
        {

                my $x = $File::Find::name;

                $x =~ s!^$dirname(\\|/)!!;

                if ( $x =~ m/^TProactor/ ||
                     $x =~ m/^app/ ||
                     $x =~ m/^tests/ ||
                     $x =~ m/^lib/ ||
                     $x =~ m/^bin/ ||
                     $x !~ m!/!)
                {
                    push ( @files, "${dirbasename}/${x}\n" );
                }
        }
}

sub write_file
{
    my $filename  = $_[0];
    my $ref_array = $_[1];

    print "Write file $filename ...\n";

    open (FH, ">$filename" ) || die "can not open $filename : $!" ;

    print FH @{$ref_array};

    truncate  (FH, tell(FH));
    close FH;
}

sub conv_files 
{
    my $ref_array = $_[0];
   
    if ($^O =~ m/MSWin32/)
    {
        my $file;
        foreach $file (@{$ref_array})
        {
            system ( "dos2unix -U $file");
        }
    }
}


sub do_main 
{
    ## chdir ("..");

    $dirname  = getcwd();
    $dirbasename  = basename ($dirname);

    my $indir  = "$dirname";
   

    find (\&wanted, ("$indir") );

    write_file ( "$dirname/file.lst" , \@files );   

    chdir ("..");
    conv_files ( \@files );   
    chdir ( $dirname);

    my $zipname = "Terabit2_$ARGV[0]";
    my $taropt = "T";

    if ($^O =~ m/aix/)
    {
        $taropt = "L";
    }
    elsif ($^O =~ m/solaris/)
    {
        $taropt = "I"
    }
    elsif ($^O =~ m/hpux/)
    {
        $taropt = "L";
    }
   

    chdir ("..");

    print  ( "tar -cvf $zipname.tar -${taropt} $dirname/file.lst\n" );
    system ( "tar -cvf $zipname.tar -${taropt} $dirname/file.lst" );
    system ( "gzip $zipname.tar");

}

do_main ;

