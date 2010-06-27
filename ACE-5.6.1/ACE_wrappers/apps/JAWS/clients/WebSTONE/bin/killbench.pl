#!/pkg/gnu/bin//perl5
#
#$Id: killbench.pl 32986 2000-06-04 22:02:08Z brunsch $
#

push(@INC, "$wd/bin");
require('WebStone-common.pl');

html_begin();

print CLIENT "<P>Killing WebStone processes<PRE>";
system("$wd/bin/killbench");
print CLIENT "</PRE><P>Done.";

html_end();

# end
