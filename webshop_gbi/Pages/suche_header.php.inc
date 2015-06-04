<?php
?>
<script type="text/javascript" src="Funktions/JS/suche.js" ></script>
<div id="box_form_suche_normal" >
	<form name="form_suche_normal" method="get" action="./" id="form_suche_normal" >
		<input name="feld_suche_normal" type="text" autocomplete="off" id="feld_suche_normal" placeholder="Suchbegriff eingeben ..."  onkeyup="autovervollstaendigung_normale_suche();" />
		<input name="page" value ="such_erg" type="hidden" />
		<input type="submit" value="Go" title="Suchen" id="suchbutton_normal" />
	</form>
	<div id="form_suche_normal_autovervollstaendigung_platzhalter" >
		<div id="form_suche_normal_autovervollstaendigung_box" >
		</div>
	</div>
</div>
<a id="link_zur_erweiterten_suche" href="#" >
	erweiterte Suche
</a>
