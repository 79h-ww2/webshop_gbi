<?php

	$zahlungsart1 = $aktuelle_bestellung->get_zahlungsart();

	$bic = (isset($_POST['bic'])) ? $_POST['bic'] : $aktuelle_bestellung->get_bankeinzug_daten()->get_bic();
	$iban = (isset($_POST['iban'])) ? $_POST['iban'] : $aktuelle_bestellung->get_bankeinzug_daten()->get_iban();
	$inhaber = (isset($_POST['inhaber'])) ? $_POST['inhaber'] : $aktuelle_bestellung->get_bankeinzug_daten()->get_kontoinhaber();
	
	//Überprüft, ob der vorherige Schritt auch ausgeführt wurde
	if ($aktuelle_bestellung->get_durchgefuehrte_schritte() < 2){
		//wenn nicht wird zu den Schritt weitergeleitet, wo der Benutzer eigentlich wäre
		die("<h3>Bitte führen Sie die vorherigen Schritte des Bestellvorgangs durch</h3>");
	}else{
	
?>
 <script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
 </script>
 <script type="text/javascript" src="./Funktions/JS/vorcheck_bestellung.js" >
</script>
<article class="middleContent content_einruecken" >
	<h2>Bestellvorgang: Schritt 3 von 5</h2>
	<form action="./?page=bestellung&schritt=3" name="form_zahlungsart" method="post" id="form_bestellung" onsubmit="return vorcheckZahlungsart();" >
		<h2>Zahlungsart</h2>
		<div class="reg_box_aufteilung" >
			<div class="warenkorb_iconbereich" ></div>
			<div class="form_content" >
			
			
				<input type="radio" name="zahlungsart" value="vorkasse" id="vorkasse"  <?php if ($zahlungsart1== 'vorkasse' || $zahlungsart1 == "" )  echo 'checked="checked"'; ?>/>
				<label for="vorkasse" >Vorkasse</label><br/>
				<input type="radio"	name="zahlungsart" value="bankeinzug" id="bankeinzug" <?php if ($zahlungsart1== 'bankeinzug')  echo 'checked="checked"'; ?> />
				
				<!-- aktiviertes Formular -->
				<div class="bankeinzug_form" id="bankeinzug_form_enabled" >
					<!--  deaktiviertes Formular -->
					<p class="reg_form_zeile" >
						<label for="inhaber" >Kontoinhaber:</label>
						<input type="text"  name="inhaber" class="lang_reg" value="<?php echo htmlspecialchars($inhaber,ENT_QUOTES,'UTF-8'); ?>"
						 <?php if (isset($bankeinzug_eingabe_unguelig) && $bankeinzug_eingabe_unguelig && $eingabe_check->get_feldstatus('inhaber')) echo 'style="border-color:red;"'; ?> />
					</p>
					<p class="reg_form_zeile" >
						<label for="iban" >IBAN:</label>
						<input type="text"  name="iban" class="lang_reg" maxlength="34" value="<?php echo htmlspecialchars($iban,ENT_QUOTES,'UTF-8'); ?>" 
						<?php if (isset($bankeinzug_eingabe_unguelig) && $bankeinzug_eingabe_unguelig && $eingabe_check->get_feldstatus('iban')) echo 'style="border-color:red;"'; ?> />
					</p>
					<p class="reg_form_zeile" >
						<label for="bic" >BIC:</label>
						<input type="text"  name="bic" class="std_reg" maxlength="11" value="<?php echo htmlspecialchars($bic,ENT_QUOTES,'UTF-8'); ?>" 
						<?php if (isset($bankeinzug_eingabe_unguelig) && $bankeinzug_eingabe_unguelig && $eingabe_check->get_feldstatus('bic')) echo 'style="border-color:red;"'; ?> />
					</p>
				</div>
				
				
				<!--  deaktiviertes Formular -->
				<div class="bankeinzug_form" id="bankeinzug_form_disabled" >
					<p class="reg_form_zeile" >
						<label for="inhaber_disabled" >Kontoinhaber:</label>
						<input type="text" disabled="disabled" name="inhaber_disabled" class="lang_reg"  />
					</p>
					<p class="reg_form_zeile" >
						<label for="iban_disabled" >IBAN:</label>
						<input type="text" disabled="disabled" name="iban_disabled" class="lang_reg" maxlength="34" />
					</p>
					<p class="reg_form_zeile" >
						<label for="bic_disabled" >BIC:</label>
						<input type="text" disabled="disabled" name="bic_disabled" class="std_reg" maxlength="11"/>
					</p>
				</div>
				
				
				<label for="bankeinzug" >Bankeinzug</label>
				<div class="platzhalter_formular_bankeinzug" ></div>
				
				<p class="text_fehlermeldung" id="zahlungsart_fehlermeldung" >
					<?php if (isset($bankeinzug_eingabe_unguelig) && $bankeinzug_eingabe_unguelig) echo htmlspecialchars($eingabe_check->get_fehlermeldung(),ENT_QUOTES,'UTF-8'); ?>
				</p>
				<div class="button_warenkorb_volle_uebersicht_rechts_ausrichten" >	
					<a href="./" title="Abbrechen" class="grauer_link_button" >Abbrechen</a>
					<input type="hidden" name="type" value="bestellvorgang_zahlungsart" />	
					<a href="./?page=bestellung&schritt=2" title="Zurück" class="grauer_link_button" >Zurück</a>		
					<input type="submit" name="submit" value="Weiter" title="Weiter" />
				</div>
				<div class="clear_right" ></div>
								
			</div>
		</div>
	</form>
</article>
<?php } ?>