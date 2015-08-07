<?php
	//Überprüft, ob der vorherige Schritt auch ausgeführt wurde
	if ($aktuelle_bestellung->get_durchgefuehrte_schritte() < 1){
		//wenn nicht wird zu den Schritt weitergeleitet, wo der Benutzer eigentlich wäre
		die("<h3>Bitte führen Sie die vorherigen Schritte des Bestellvorgangs durch</h3>");
	}else{
		if ($aktuelle_bestellung->get_durchgefuehrte_schritte() < 2) $aktuelle_bestellung->set_durchgefuehrte_schritte(2);
?>
<article class="middleContent content_einruecken" >
	<h2>Bestellvorgang: Schritt 2 von 5</h2>
	<form action="./?page=bestellung&schritt=2" name="form_warenkorb" method="post" id="form_bestellung" >
		<h2>Warenkorb</h2>
		<div class="reg_box_aufteilung" >
			<div class="warenkorb_iconbereich" ></div>
			<div class="form_content" >
				
				<?php include_once 'Pages/warenkorb_tabelle_bestellvorgang.php.inc'; ?>
					
				<p class="text_fehlermeldung" ></p>
				<div class="button_warenkorb_volle_uebersicht_rechts_ausrichten" >	
					<a href="./" title="Abbrechen" class="grauer_link_button" >Abbrechen</a>
					<a href="./?page=bestellung" title="Zurück" class="grauer_link_button" >Zurück</a>
					<a href="./?page=bestellung&schritt=3" title="Weiter" class="grauer_link_button" >Weiter</a>
				</div>
				<div class="clear_right" ></div>	
					
			</div>
		</div>
	</form>
</article>
<?php }?>