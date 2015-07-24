<h2>Introduction</h2>
<p>Knetwork library is an example to demonstrate using ACE and Terabit frameworks to create high performance server application.</p>
<h2>Background</h2>
<p><b>Framework dependencies.</b>
<ul><li>ACE. (<a href='http://www.cs.wustl.edu/~schmidt/ACE.html'>http://www.cs.wustl.edu/~schmidt/ACE.html</a>)</li>
<li>Terabit (<a href='http://www.terabit.com.au/'>http://www.terabit.com.au/</a>)</li>
</ul></p>
<h2>Use of code</h2>
<p><b>How to compile knet project.</b>
<ul><li>Open the file knetwork\ACE-5.6.1\ACE_wrappers\ace\ace.sln to build.</li>
<li>Open the file knetwork\Terabit2_561.4\Terabit\all.sln to build.</li>
<li>Select "Tools" from the "Options" menu, and add the following directories settings as required:<ul><li>Add knetwork\ACE-5.6.1\ACE_wrappers to the Include directory list.</li>
<li>Add knetwork\ACE-5.6.1\ACE_wrappers\lib to the Library directory list.</li>
<li>Add knetwork\Terabit2_561.4\Terabit to the Include directory list.</li>
<li>Add knetwork\Terabit2_561.4\Terabit\app to the Include directory list.</li>
<li>Add knetwork\Terabit2_561.4\Terabit\lib to the Library directory list.</li>
</ul></li>
<li>Open the file knetwork\Router\Krouter.sln to build.</li>
<li>Now execute Krouter.exe to start server.</li>
<li>Execute Test.exe to start client simulator.</li>
<li>Please refer to knetwork\release\knet.cfg and test.bat for setting the config files.</li>
</ul></p>