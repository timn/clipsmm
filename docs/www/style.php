<?php
include_once("site.php");

function generate_css() {
global $css;
?>
<style type="text/css">
body {
background-color: <?php print $css["bgcolor"]?>;
background-attachment: fixed;
background-image: url('<?php print $css["background_image"]?>');
color: black;
font-family: Verdana, Arial, Helvetica, sans-serif;
font-size: 15px;
margin-left: 220px;
}

h1 {
width: 95%;
background-color: <?php print $css["light_color"] ?>;
color: <?php print $css["dark_color"] ?>;
border: 1px solid black;
text-align: center;
margin-left: auto;
margin-right: auto;
margin-top: 25px;
margin-bottom: 0px;
}

h2 {
width: 75%;
background-color: <?php print $css["dark_color"] ?>;
color: white;
border: 1px solid black;
text-align: center;
margin-left: auto;
margin-right: auto;
margin-top: 25px;
margin-bottom: 5px;
}

h3 {
color: <?php print $css["dark_color"] ?>;
margin-left: 3%;
margin-right: 3%;
margin-top: 10px;
margin-bottom: 5px;
}

p.level2 {
color: black;
margin-left: 3%;
margin-right: 3%;
margin-top: 5px;
margin-bottom: 5px;
}

p.level3 {
color: black;
margin-left: 6%;
margin-right: 6%;
margin-top: 5px;
margin-bottom: 5px;
}

ol.level3 {
margin-left: 6%;
margin-right: 6%;
}

ul.level3 {
margin-left: 6%;
margin-right: 6%;
}

a { text-decoration: underline }
a:link { color: #00C; }
a:visited { color: #609; }
a:hover { text-decoration: none; }
a:active { color: #C00; }

a.menu { text-decoration: underline; color: white; }
a.menu:link { text-decoration: underline; color: white; }
a.menu:visited { text-decoration: underline; color: white; }
a.menu:hover { text-decoration: none; }

b.mb { color: white; }
i.mb { color: white; }

#menu {
position: absolute;
top: 15px;
left: 8px;
width: 200px;
}

.menubox {
background-color: <?php print $css["menu_bgcolor"] ?>;
border: 5px solid black;
padding: 5px;
}

.releasebox {
background: <?php print $css["release_bgcolor"] ?>;
border: 1px solid black;
padding: 5px;
font-size: 13px;
}

.contentsbox {
background: <?php print $css["contentsbox_bgcolor"] ?>;
border: 1px solid black;
padding: 5px;
}

.center {
margin-left: auto;
margin-right: auto;
text-align: center;
}

.right {
text-align: right;
}

code
{
background-color: <?php print $css["code_bgcolor"] ?>;
color: <?php print $css["code_fgcolor"] ?>;
}

pre
{
display: block;
background-color: <?php print $css["pre_bgcolor"] ?>;
color: black;
}

pre.level2
{
display: block;
background-color: <?php print $css["pre_bgcolor"] ?>;
color: black;
margin-left: 3%;
margin-right: 3%;
}

pre.level3
{
display: block;
background-color: <?php print $css["pre_bgcolor"] ?>;
color: black;
margin-left: 6%;
margin-right: 6%;
}
</style>

<?php
}
?>
