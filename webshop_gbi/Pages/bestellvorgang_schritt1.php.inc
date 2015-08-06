<?php $versandart = $aktuelle_bestellung->get_versandart(); ?>
<article class="middleContent content_einruecken" >
	<?php if (!(isset($_GET['aendern']))) { echo '<h2>Bestellvorgang: Schritt 1 von 5</h2>'; } else {echo '<h2>Bestellvorgang: Versandart &auml;ndern</h2>'; } ?>
	<form action="./?page=bestellung&schritt=<?php if (!(isset($_GET['aendern']))) {echo '2';} else {echo '5';} ?>" name="form_versandart" method="post" id="form_bestellung" >
		<h2>Versandart</h2>
		<div class="reg_box_aufteilung" >
			<div class="versandadresse_iconbereich" ></div>
			<div class="form_content" >
				<div class="radio-buttonbereich-versandart-bereich radio-buttonbereich-versandart-bereich-standardversand" >
					<input type="radio" name="versandart" value="standardversand" id="standardversand" <?php if ($versandart== 'standardversand' || $versandart == "" )  echo 'checked="checked"'; ?> >
					<label for="standardversand" >
						Standardversand
						<ul>
							<li>Bestellpreis &uuml;ber 25 &euro; : Kostenloser Versand</li>
							<li>Sonst 4 &euro; Versandkosten</li>
						</ul>
					</label>
				</div>
				<div class="radio-buttonbereich-versandart-bereich" >
					<input type="radio" name="versandart" value="expressversand" id="expressversand" <?php if ($versandart== 'expressversand' )  echo 'checked="checked"'; ?> >
					<label for="expressversand" >Expressversand
						<ul>
							<li>Innerhalb von 24 Stunden das Paket erhalten</li>
							<li>Versandkosten: 13 &euro;</li>
						</ul>
					</label>
				</div>
				<p class="text_fehlermeldung"></p>
				<div class="button_warenkorb_volle_uebersicht_rechts_ausrichten" >	
					<a href="<?php if (!(isset($_GET['aendern']))) { echo './'; } else {echo './?page=bestellung&schritt=5'; } ?>" title="Abbrechen" class="grauer_link_button" >Abbrechen</a>
					<input type="hidden" name="type" value="bestellvorgang_versandart" />
					<?php $aufschrift = (!(isset($_GET['aendern']))) ? "Weiter" : "&Auml;ndern"; ?>			
					<input type="submit" name="submit" value="<?php echo $aufschrift; ?>" title="<?php echo $aufschrift; ?>" />
				</div>
				<div class="clear_right" ></div>
			</div>
		</div>
	</form>
</article>