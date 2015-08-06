<?php
	//Überprüft, ob der vorherige Schritt auch ausgeführt wurde
	if ($aktuelle_bestellung->get_durchgefuehrte_schritte() < 4){
		//wenn nicht wird zu den Schritt weitergeleitet, wo der Benutzer eigentlich wäre
		die("<h3>Bitte führen Sie die vorherigen Schritte des Bestellvorgangs durch</h3>");
	}else{
?>
<script type="text/javascript" src="./Funktions/JS/vorcheck_bestellung.js" >
</script>
<article class="middleContent content_einruecken" >
	<h2>Bestellvorgang: Schritt 5 von 5</h2>
	<form action="./?page=bestellung&schritt=5" name="form_ueberschicht" method="post" id="form_bestellung" onsubmit="return vorcheckAGBZugestimmt();"  >
		<h2>Bestell&uuml;bersicht</h2>
		<div class="reg_box_aufteilung" >
			<div class="warenkorb_iconbereich" ></div>
			<div class="form_content" >
			
				<div class="werte_bestellvorgang_uebersicht_ueberschrift" >Versandart:</div>
				<ul class="werte_bestellvorgang_uebersicht">
					<li>
						<?php echo htmlspecialchars(ucwords($aktuelle_bestellung->get_versandart()),ENT_QUOTES,'UTF-8'); ?>
						<a title="&Auml;ndern" href="./?page=bestellung&schritt=1&aendern=1" class="link_menge_aendern"></a>
					</li>
				</ul>
				
				<div class="werte_bestellvorgang_uebersicht_ueberschrift" >Warenkorb:</div>
				<?php include_once 'Pages/warenkorb_tabelle_bestellvorgang.php.inc'; ?>
				<div class="werte_bestellvorgang_uebersicht_ueberschrift" >Zahlungsart:</div>
				<div class="werte_bestellvorgang_uebersicht_zahlungsart" >
					<ul class="werte_bestellvorgang_uebersicht werte_bestellvorgang_uebersicht_zahlungsart_bereich">
						<li>
							<?php echo htmlspecialchars(ucwords($aktuelle_bestellung->get_zahlungsart()),ENT_QUOTES,'UTF-8'); ?>
						</li>
					</ul>
					<div class="werte_bestellvorgang_uebersicht_zahlungsart_bereich werte_bestellvorgang_uebersicht_zahlungsart_platzierung_aendern_stift_oben" >
						<a title="&Auml;ndern" href="./?page=bestellung&schritt=3&aendern=1" class="link_menge_aendern"></a>
					</div>
					<?php if ($aktuelle_bestellung->get_zahlungsart() == 'bankeinzug' ){?>
						<ul class="werte_bestellvorgang_uebersicht werte_bestellvorgang_uebersicht_zahlungsart_bereich">
							<li>Kontoinhaber: <?php echo htmlspecialchars(ucwords($aktuelle_bestellung->get_bankeinzug_daten()->get_kontoinhaber()),ENT_QUOTES,'UTF-8'); ?></li>
							<li>IBAN: <?php echo htmlspecialchars(ucwords($aktuelle_bestellung->get_bankeinzug_daten()->get_iban()),ENT_QUOTES,'UTF-8'); ?></li>
							<li>BIC: <?php echo htmlspecialchars(ucwords($aktuelle_bestellung->get_bankeinzug_daten()->get_bic()),ENT_QUOTES,'UTF-8'); ?></li>
						</ul>
						<div class="werte_bestellvorgang_uebersicht_zahlungsart_bereich werte_bestellvorgang_uebersicht_zahlungsart_platzierung_aendern_stift" >
							<a title="&Auml;ndern" href="./?page=bestellung&schritt=3&aendern=1" class="link_menge_aendern"></a>
						</div>
					<?php } ?>
				</div>
				<div class="werte_bestellvorgang_uebersicht_ueberschrift" >Lieferadresse:</div>
				<div class="werte_bestellvorgang_uebersicht_zahlungsart" >
					<ul class="werte_bestellvorgang_uebersicht werte_bestellvorgang_uebersicht_zahlungsart_bereich">
						<li><?php if ( $aktuelle_bestellung->get_liefer_geschlecht() == 'weiblich') {echo "Frau";} else {echo "Herr";};?></li>
						<li><?php echo $aktuelle_bestellung->get_liefer_vorname()." ".$aktuelle_bestellung->get_liefer_name(); ?></li>
						<li><?php echo $aktuelle_bestellung->get_liefer_strasse()." ".$aktuelle_bestellung->get_liefer_hausnr(); ?></li>
						<li><?php echo $aktuelle_bestellung->get_liefer_plz()." ".$aktuelle_bestellung->get_liefer_ort(); ?></li>
					</ul>
					<div class="werte_bestellvorgang_uebersicht_zahlungsart_bereich werte_bestellvorgang_uebersicht_zahlungsart_platzierung_aendern_stift" >
						<a title="&Auml;ndern" href="./?page=bestellung&schritt=4&aendern=1" class="link_menge_aendern"></a>
					</div>
				</div>
				<div class="werte_bestellvorgang_uebersicht_ueberschrift" >AGB:</div>
				<div class="agbtext_bestellvorgang" >
					<?php include 'Pages/AGB.php.inc'; ?>
				</div>
				<div id="checkbox_agb" >
					<input type="checkbox" name="ack_agb" value="ja" id="ack_agb" />
					<label for="ack_agb" >Ich akzeptiere die AGB.</label>
				</div>
				<p class="text_fehlermeldung" id="fehler_check_agb" >
				</p>
				<div class="button_warenkorb_volle_uebersicht_rechts_ausrichten" >	
					<a href="./" title="Abbrechen" class="grauer_link_button" >Abbrechen</a>
					<input type="hidden" name="type" value="bestellvorgang_agb" />
					<a href="./?page=bestellung&schritt=4" title="Zurück" class="grauer_link_button" >Zurück</a>			
					<input type="submit" name="submit" id="bestellenButton" value="Jetzt kostenpflichtig bestellen" title="Jetzt kostenpflichtig bestellen" />
				</div>
				<div class="clear_right" ></div>
						
			</div>
		</div>
	</form>
</article>
<?php }?>