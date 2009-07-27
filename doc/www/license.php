<?php
   include_once("utility.php");
   generate_header($site["project_name"] + " library license");
?>



<h1><?php print $site["project_name"]?></h1>
<p>
The <?php print $site["project_name"]?> library distribution contains various components. Each component is released under the following licenses:
<ul>
<li>Source Code:
<p><a href="http://www.gnu.org/copyleft/gpl.html"><img src="images/gnu-head-sm.png" width="100" height="100"/>&nbsp;&nbsp;GNU GPL version 2</a>
<li>Images:
<p><!--Creative Commons License--><a rel="license" href="http://creativecommons.org/licenses/by-sa/2.5/"><img alt="Creative Commons License" border="0" src="http://creativecommons.org/images/public/somerights20.png"/></a><br/>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/2.5/">Creative Commons Attribution-ShareAlike2.5 License</a>.<!--/Creative Commons License--><!-- <rdf:RDF xmlns="http://web.resource.org/cc/" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
		<Work rdf:about="">
			<license rdf:resource="http://creativecommons.org/licenses/by-sa/2.5/" />
	<dc:type rdf:resource="http://purl.org/dc/dcmitype/StillImage" />
		</Work>
		<License rdf:about="http://creativecommons.org/licenses/by-sa/2.5/"><permits rdf:resource="http://web.resource.org/cc/Reproduction"/><permits rdf:resource="http://web.resource.org/cc/Distribution"/><requires rdf:resource="http://web.resource.org/cc/Notice"/><requires rdf:resource="http://web.resource.org/cc/Attribution"/><permits rdf:resource="http://web.resource.org/cc/DerivativeWorks"/><requires rdf:resource="http://web.resource.org/cc/ShareAlike"/></License></rdf:RDF> -->
<li>This website and accompanying documentation:
<p><a href="http://www.gnu.org/licenses/fdl.html"><img src="images/philosophical-gnu-sm.png" width="80" height="100"/>&nbsp;&nbsp;GNU Free Documentation License 1.2</a>
</ul>

<?php
   generate_footer();
?>

