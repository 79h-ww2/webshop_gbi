<?php
	include_once 'Classes/Kunde.php.inc';
	$profil = new Kunden();
	
	//Kundennr bestimmen
	$kid = $profil->get_kid_from_email($_SESSION['angemeldet']);
	
	//Lieferadresseart (gespeichert)
	$lieferadreesse_art = $aktuelle_bestellung->get_leiferadresse_art();
	
	$eingabe_ungueltig_adresse = isset($eingabe_ungueltig_adresse) ? $eingabe_ungueltig_adresse : false;
	
	
	//Wenn es sich bei der zwischengespeicherten Adresse nicht um die registrierte Adresse handelt, wird sie angezeigt
	$andreAdresse = false;
	if (
			$aktuelle_bestellung->get_liefer_geschlecht() != $profil->get_geschlecht_from_kid($kid) ||
			$aktuelle_bestellung->get_liefer_hausnr() != $profil->get_hausnr_from_kid($kid) ||
			$aktuelle_bestellung->get_liefer_name() != $profil->get_name_from_kid($kid) ||
			$aktuelle_bestellung->get_liefer_ort() != $profil->get_ort_from_kid($kid) ||
			$aktuelle_bestellung->get_liefer_plz() != $profil->get_plz_from_kid($kid) ||
			$aktuelle_bestellung->get_liefer_strasse() != $profil->get_strasse_from_kid($kid) ||
			$aktuelle_bestellung->get_liefer_vorname() != $profil->get_vorname_from_kid($kid)
	) $andreAdresse = true;
	
	//Überprüft, ob der vorherige Schritt auch ausgeführt wurde
	if ($aktuelle_bestellung->get_durchgefuehrte_schritte() < 3){
		//wenn nicht wird zu den Schritt weitergeleitet, wo der Benutzer eigentlich wäre
		die("<h3>Bitte führen Sie die vorherigen Schritte des Bestellvorgangs durch</h3>");
	}else{
?>
<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
</script>
<script type="text/javascript" src="./Funktions/JS/vorcheck_profil_aendern.js" >
</script>
<script type="text/javascript" src="./Funktions/JS/vorcheck_bestellung.js" >
</script>
<article class="middleContent content_einruecken" >
	<?php if (!(isset($_GET['aendern']))) { echo '<h2>Bestellvorgang: Schritt 4 von 5</h2>'; } else {echo '<h2>Bestellvorgang: Lieferadresse &auml;ndern</h2>'; } ?>
	<form action="./?page=bestellung&schritt=4<?php if (isset($_GET['aendern'])) { echo '&aendern=1'; }?>" name="form_adresse_aendern" method="post" id="form_bestellung" onsubmit="return vorcheckLieferadresse()" >
		<h2>Lieferadresse</h2>
		<div class="reg_box_aufteilung" >
			<div class="warenkorb_iconbereich" ></div>
			<div class="form_content" >
			
			<input type="radio" name="adresse" value="reg" id="adresse_reg" <?php if($lieferadreesse_art == 'reg' || $lieferadreesse_art == '' || $lieferadreesse_art == 'andere' && !$andreAdresse  ) echo "checked=\"checked\"";?> />
			<label for="adresse_reg" >Registrierte Adresse
				<div class="gespeicherte_adresse" >
					<?php if ($profil->get_geschlecht_from_kid($kid) == 'weiblich') {echo "Frau";} else {echo "Herr";};?><br/>
					<?php echo htmlspecialchars($profil->get_vorname_from_kid($kid)." ".$profil->get_name_from_kid($kid),ENT_QUOTES,'UTF-8'); ?><br/>
					<?php echo htmlspecialchars($profil->get_strasse_from_kid($kid)." ".$profil->get_hausnr_from_kid($kid),ENT_QUOTES,'UTF-8'); ?><br/>
					<?php echo htmlspecialchars($profil->get_plz_from_kid($kid)." ".$profil->get_ort_from_kid($kid),ENT_QUOTES,'UTF-8'); ?><br/>
				</div>
			</label>
			
			<input type="radio" name="adresse" value="andere" id="adresse_andere" <?php if($lieferadreesse_art == 'andere') echo "checked=\"checked\"";?> />
			<?php		
				$disabled = array('', 'disabled="disabled"');
				$feldnamen_anhaenger = array('', '_disabled');
				$ids = array('lieferadresse_form_enabled', 'lieferadresse_form_disabled');
				
				for ($i = 0; $i < 2; $i++){
			?>
			
				<div class="lieferadresse_form" id="<?php echo $ids[$i]; ?>" >
				
					<p class="reg_form_zeile" >
						<label for="vorname<?php echo $feldnamen_anhaenger[$i]; ?>">Vorname:</label>
						<input <?php echo $disabled[$i]; ?> type="text" name="vorname<?php echo $feldnamen_anhaenger[$i]; ?>" maxlength="50"  value="<?php 
						
						//Es wird ein zwischengespeicherter Vornamen im Textfeld angezeigt
						if ($andreAdresse && !(isset($_POST['vorname']))){ 
							echo htmlspecialchars($aktuelle_bestellung->get_liefer_vorname(),ENT_QUOTES,'UTF-8');
						}
						//Es wird der über Post gehaltene Vorname angezeigt
						elseif (isset($_POST['vorname'])){
							echo htmlspecialchars($_POST['vorname'],ENT_QUOTES,'UTF-8');
						} 
					?>" class="lang_reg" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('vorname') && $i == 0  ) echo 'style="border-color:red; border-style: solid"';  ?> />
			            </p>
			            
			            <p class="reg_form_zeile" >
			                <label for="name<?php echo $feldnamen_anhaenger[$i]; ?>">Name:</label>
			                <input <?php echo $disabled[$i]; ?> type="text" name="name<?php echo $feldnamen_anhaenger[$i]; ?>" maxlength="50"  value="<?php
			               			                
			                //Es wird ein zwischengespeicherter Namen im Textfeld angezeigt
			                if ($andreAdresse && !(isset($_POST['name']))){
			                	echo htmlspecialchars($aktuelle_bestellung->get_liefer_name(),ENT_QUOTES,'UTF-8');
			                }
			                //Es wird der über Post gehaltene Name angezeigt
			                elseif (isset($_POST['name'])){
			                	echo htmlspecialchars($_POST['name'],ENT_QUOTES,'UTF-8');
			                }
			                ?>"
			                class="lang_reg" <?php if($eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('name') && $i == 0 ) echo 'style="border-color:red; border-style: solid"';  ?> />
			            </p>
			            
			             <p class="reg_form_zeile" >
			              	<span>Geschlecht:</span>
			              	<?php
			              		$gechlecht = "männlich";
			              		//Es wird ein Zwischengespeichertes Geschlecht markiert 
			              		if ( $andreAdresse && !(isset($_POST['geschlecht']))){
			              			$gechlecht = $aktuelle_bestellung->get_liefer_geschlecht();
			              		}
			              		//Es wird das über Post übermittelte Geschlecht angezeigt
			              		elseif (isset($_POST['geschlecht'])){
			              			$gechlecht = $_POST['geschlecht'];
			              		}
			              	?>
			              	<input <?php echo $disabled[$i]; ?> type="radio" name="geschlecht<?php echo $feldnamen_anhaenger[$i]; ?>" id="maennlich" value="männlich" <?php if($gechlecht == 'männlich') echo 'checked="checked"'; ?>  />
			            	<label for="maennlich<?php echo $feldnamen_anhaenger[$i]; ?>">m&auml;nnlich</label>
			            	
			            	<input <?php echo $disabled[$i]; ?> type="radio" name="geschlecht<?php echo $feldnamen_anhaenger[$i]; ?>" id="weiblich" value="weiblich" <?php if($gechlecht != 'männlich') echo 'checked="checked"'; ?> />
			            	<label for="weiblich<?php echo $feldnamen_anhaenger[$i]; ?>">weiblich</label>
			            </p>
			            
			            <p class="reg_form_zeile" >
			                <label for="strasse<?php echo $feldnamen_anhaenger[$i]; ?>" >Stra&szlig;e:</label>
			                <input <?php echo $disabled[$i]; ?> type="text" name="strasse<?php echo $feldnamen_anhaenger[$i]; ?>" maxlength="50"  value="<?php
			                
			                //Es wird eine zwischengespeicherter Straße im Textfeld angezeigt
			                if ($andreAdresse && !(isset($_POST['strasse']))){
			                	echo htmlspecialchars($aktuelle_bestellung->get_liefer_strasse(),ENT_QUOTES,'UTF-8');
			                }
			                //Es wird die über Post gehaltene Straße angezeigt
			                elseif (isset($_POST['strasse'])){
			                	echo htmlspecialchars($_POST['strasse'],ENT_QUOTES,'UTF-8');
			                }
			                
			                ?>" class="std_reg" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('strasse') && $i == 0 ) echo 'style="border-color:red; border-style: solid"';  ?> />
			                <label for="hausnr<?php echo $feldnamen_anhaenger[$i]; ?>" class="hausnr" >Haus Nr.:</label>
			                <input <?php echo $disabled[$i]; ?> type="text" name="hausnr<?php echo $feldnamen_anhaenger[$i]; ?>" maxlength="5"  value="<?php 
			                
			                //Es wird eine zwischengespeicherter Hausnimmer im Textfeld angezeigt
			                if ($andreAdresse && !(isset($_POST['hausnr']))){
			                	echo htmlspecialchars($aktuelle_bestellung->get_liefer_hausnr(),ENT_QUOTES,'UTF-8');
			                }
			                //Es wird die über Post gehaltene Hausnummer angezeigt
			                elseif (isset($_POST['hausnr'])){
			                	echo htmlspecialchars($_POST['hausnr'],ENT_QUOTES,'UTF-8');
			                }
			                
			                ?>" class="hausnr" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('hausnr') && $i == 0 ) echo 'style="border-color:red; border-style: solid"';  ?> />
			            </p>
			            
			             <p class="reg_form_zeile" >
			                <label for="plz<?php echo $feldnamen_anhaenger[$i]; ?>" >PLZ:</label>
			                <input <?php echo $disabled[$i]; ?> type="text" name="plz<?php echo $feldnamen_anhaenger[$i]; ?>" maxlength="5"  value="<?php 
			                
			                //Es wird eine zwischengespeicherter Postleitzahl im Textfeld angezeigt
			                if ($andreAdresse && !(isset($_POST['plz']))){
			                	echo htmlspecialchars($aktuelle_bestellung->get_liefer_plz(),ENT_QUOTES,'UTF-8');
			                }
			                //Es wird die über Post gehaltene Postleitzahl angezeigt
			                elseif (isset($_POST['plz'])){
			                	echo htmlspecialchars($_POST['plz'],ENT_QUOTES,'UTF-8');
			                }
			                
			                ?>" class="plz" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('plz') && $i == 0 ) echo 'style="border-color:red; border-style: solid"';  ?> />
			                
			                <label for="ort<?php echo $feldnamen_anhaenger[$i]; ?>" class="ort" >Ort:</label>
			                <input <?php echo $disabled[$i]; ?> type="text" name="ort<?php echo $feldnamen_anhaenger[$i]; ?>" maxlength="50"  value="<?php
			                
			                //Es wird ein zwischengespeicherter Ort im Textfeld angezeigt
			                if ($andreAdresse && !(isset($_POST['ort']))){
			                	echo htmlspecialchars($aktuelle_bestellung->get_liefer_ort(),ENT_QUOTES,'UTF-8');
			                }
			                //Es wird der über Post gehaltene Ort angezeigt
			                elseif (isset($_POST['ort'])){
			                	echo htmlspecialchars($_POST['ort'],ENT_QUOTES,'UTF-8');
			                }
			                
			                ?>" class="std_reg" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('ort') && $i == 0 ) echo 'style="border-color:red; border-style: solid"';  ?> />
			            </p>
				</div>
			<?php }?>
			
				<label for="adresse_andere">Andere Adresse</label>
				<div class="platzhalter_formular_lieferadresse" ></div>
			
				<p class="text_fehlermeldung" id="EingabeAdresse_fehlermeldung" >
					<?php
						//zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
						if ($eingabe_ungueltig_adresse){
							echo htmlspecialchars($eingabe_check_result_adresse->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
						} 
		            ?>
				</p>
				<div class="button_warenkorb_volle_uebersicht_rechts_ausrichten" >	
					<a href="<?php if (!(isset($_GET['aendern']))) { echo './'; } else {echo './?page=bestellung&schritt=5'; } ?>" title="Abbrechen" class="grauer_link_button" >Abbrechen</a>
					<input type="hidden" name="type" value="bestellvorgang_lieferart" />	
					<?php if (!(isset($_GET['aendern']))) echo'<a href="./?page=bestellung&schritt=3" title="Zurück" class="grauer_link_button" >Zurück</a>'; ?>	
					<?php $aufschrift = (!(isset($_GET['aendern']))) ? "Weiter" : "&Auml;ndern"; ?>			
					<input type="submit" name="submit" value="<?php echo $aufschrift; ?>" title="<?php echo $aufschrift; ?>" />
				</div>
				<div class="clear_right" ></div>
								
			</div>
		</div>
	</form>
</article>
<?php }?>
