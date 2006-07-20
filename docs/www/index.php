<?php
   include_once("utility.php");
   generate_header("clipsmm");
?>

<h1>clipsmm - C++ CLIPS Interface</h1>

<h2>What</h2>
<p class="level2">
<a href="http://clipsmm.sourceforge.net">clipsmm</a> is a C++ interface and library for <a href="http://www.ghg.net/clips/CLIPS.html">CLIPS.</a></p>

<p class="level2">
CLIPS is an environment for creating rule-based and/or object-based expert systems. clipsmm extends the CLIPS C API in several ways:
<ul>
<li>CLIPS Environments are encapsulated in an Environment object as are many of the other CLIPS concepts such as templates (fact templates, not C++ templates), rules, etc.
<li>Making external functions available to the CLIPS inference engine are simplified using sigc++ slots. This also:
<ul>
<li>Provides the benefit of compiler type checks on external functions.
<li>Makes it simple to not only make external functions available, but also external methods of C++ classes.
</ul>
</ul>
</p>

<?php
   generate_footer();
?>

