<?php
	//Überprüft, ob der vorherige Schritt auch ausgeführt wurde
	if ($aktuelle_bestellung->get_durchgefuehrte_schritte() < 4){
		//wenn nicht wird zu den Schritt weitergeleitet, wo der Benutzer eigentlich wäre
		die("<h3>Bitte führen Sie die vorherigen Schritte des Bestellvorgangs durch</h3>");
	}else{
?>
<article class="middleContent content_einruecken" >
	<h2>Bestellvorgang: Schritt 5 von 5</h2>
	<form action="./?page=bestellung&schritt=4" name="form_adresse_aendern" method="post" id="form_bestellung" onsubmit="return vorcheckLieferadresse()" >
		<h2>Bestell&uuml;bersicht</h2>
		<div class="reg_box_aufteilung" >
			<div class="warenkorb_iconbereich" ></div>
			<div class="form_content" >
			
								
			</div>
		</div>
	</form>
</article>
<?php }?>