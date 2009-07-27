<!--
    Copyright (c)  2005  Rick L. Vinyard, Jr.
    Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.2
    as published by the Free Software Foundation;
    with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
    A copy of the license is included in the section entitled "GNU
    Free Documentation License".
-->

<?php
include_once("site.php");
include_once("style.php");

function href($href)
{
echo "href=\"", $href, "\"";
}

function image($img, $alt="", $border=0)
{
global $site;
echo "<img src=\"", $site["imagedir"], "/", $img, "\" alt=\"", $alt, "\" border=\"", $border, "\" />";
}

function generate_header($title)
{
global $site, $releases, $other_docs, $dependencies;

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
<?php echo "<title>", $site["project_name"], "</title>" ?>
<meta name="author" content="Rick L Vinyard Jr">
<meta name="copyright" content="Rick L. Vinyard, Jr.">
<meta name="keywords" content=<?php $site["keywords"]?> >
<meta name="description" content=<?php $site["description"]?> >
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta http-equiv="Content-Type" content="application/xhtml+xml; charset=UTF-8">
<meta http-equiv="Content-Style-Type" content="text/css">
<meta http-equiv="Expires" content="">
<?php generate_css() ?>
<link rel="icon" <?php href($site["project_url"]."/".$site["favicon"])?> type="image/x-icon" />
<link rel="shortcut icon" <?php href($site["project_url"]."/".$site["favicon"])?> type="image/x-icon" />

</head>
<body>
<div id="menu">
<div class="center" style="padding-bottom: 10px">
<a <?php href($site["project_url"])?> >
<?php image($site["square_logo"], $site["project_name"]) ?>
</a>
<br />
</div>
<div class="menubox">
<b><a class="menu" <?php href($site["project_url"])?> >
<?php echo $site["project_name"] ?> home</a></b>
<br />
      <!-- <a class="menu" href="features.shtml">Features</a><br /> -->

<a class="menu" <?php href($site["license"])?> >License</a>
<br />
<a class="menu" <?php href($site["news"])?> >News</a>
<br />
<br />
<b><a class="menu" <?php href($site["screenshots"])?> >Screenshots</a></b>
<br />
<br />
<b class="mb">Documentation</b>
<br />
<?php
foreach ($other_docs as $page) {
echo "&nbsp;&nbsp;";
echo "<a class=\"menu\" href=\"";
echo $page["url"];
echo "\">";
echo $page["name"];
echo "</a><br />";
}
?>
<br />
<b class="mb">Discussion &amp; Bugs</b>
&nbsp;&nbsp;<a class="menu" <?php href($site["mailing_lists"])?> >Mailing Lists</a>
<br />
&nbsp;&nbsp;<a class="menu" <?php href($site["bug_tracker"])?> >Bug Tracker</a>
<br />
&nbsp;&nbsp;<a class="menu" <?php href($site["submit_bug"])?> >Submit Bug</a>
<br />
<br />

<b class="mb">Downloading</b>
<br />
&nbsp;&nbsp;<a href="#latest" class="menu"><big><b>Latest Version</b></big></a>
<br />
&nbsp;&nbsp;<a class="menu" <?php href($site["download_page"])?> >Previous Versions</a>
<br />
&nbsp;&nbsp;<a class="menu" <?php href($site["cvs"])?> >CVS</a>
<br />

<br />
<a class="menu" <?php href($site["host_page"])?> >Sourceforge Page</a>
<br />
<br />
    <!-- <a class="menu" href="faq.shtml">FAQ</a><br /> -->
<a class="menu" <?php href($site["developers"])?> >Developers</a>
<br />
    <!-- <a class="menu" href="extra.shtml">Additional Resources</a><br /> -->

</div>

<br />


<div class="releasebox">
<span style="font-size: 15px">
<a name="latest"><u><b>Latest Versions</b></u></a>
<br />
</span>
<br/>

<?php
foreach ($releases as $releasename => $release) {
echo "<b>", $releasename, "</b>";
echo "<br />";
foreach ($release as $file)
echo $file["type"], "<br /><small><small><a href=\"", $file["url"], "\">", $file["name"], "</a></small></small><br /><br />";
echo "<br />";
}
?>

</div>

<br />

<div class="releasebox">
<span style="font-size: 15px">
<u><b>Dependencies</b></u>
<br />(and where to get them)
<br/>
</span>
<br/>

<?php
foreach ($dependencies as $dependency => $url) {
echo "<a href=\"",$url,"\"><b>",$dependency, "</b></a>";
echo "<br /><br />";
}
?>

</div>

</div>

<div class="contentsbox">

<div class="center">
<a <?php href($site["project_url"])?> >
<?php image($site["long_logo"], $site["project_name"])?>
</a>
<br />
</div>

<?php
}

function generate_footer() {
global $site;
?>
</div>
<div class="right">
<br />
<a href="http://sourceforge.net">
<img src=<?php echo "\"", $site["host_logo"],"\""?> width="125" height="37" border="0" alt="SourceForge.net Logo" />
</a>
&nbsp;&nbsp;&nbsp;
<a <?php href($site["donate_url"])?> >
<img src="http://images.sourceforge.net/images/project-support.jpg" width="88" height="32" border="0" alt="Support This Project" />
</a>
&nbsp;&nbsp;&nbsp;
<a href="http://validator.w3.org/check/referer">
<img src="http://validator.w3.org/images/vxhtml11" alt="Valid XHTML 1.0!" height="31" width="88" border="0" />
</a>

</div>
</body>
</html>
<?php
}

?>

