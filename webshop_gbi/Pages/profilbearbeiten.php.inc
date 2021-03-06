    <?php
    	include_once 'Classes/Kunde.php.inc';
    	$profil = new Kunden();
    	//Kundennr bestimmen
    	$kid = $profil->get_kid_from_email($_SESSION['angemeldet']);
    	
    	$eingabe_ungueltig_email_passwort = isset($eingabe_ungueltig_email_passwort) ? $eingabe_ungueltig_email_passwort : false;
    	
 		$eingabe_ungueltig_adresse = isset($eingabe_ungueltig_adresse) ? $eingabe_ungueltig_adresse : false;
 		
 	?>
 	<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
    </script>
    <script type="text/javascript" src="./Funktions/JS/vorcheck_profil_aendern.js" >
    </script>
    <form method="post" action="./?page=profilbearbeiten&type=adressebearbeiten" onsubmit="return vorcheckEingabeAdresse();" id="form_adresse_aendern" name="form_adresse_aendern" >
        <h2>
		     Adresse ändern
		</h2>
        <div class="reg_box_aufteilung" >
        	<div class="TableRow_reg" >
	        	<div class="adresse_aendern_box_iconbereich" >
	        	</div> 
	        
		        <div class="form_content" >
		        
		            <p class="reg_form_zeile" >
		                <label for="vorname">Vorname:</label>
		                <input type="text" name="vorname" maxlength="50" value="<?php if ($eingabe_ungueltig_adresse) {echo htmlspecialchars($_POST['vorname'],ENT_QUOTES,'UTF-8');}else{ echo htmlspecialchars($profil->get_vorname_from_kid($kid),ENT_QUOTES,'UTF-8'); } ?>" class="lang_reg" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('vorname') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="name">Name:</label>
		                <input type="text" name="name" maxlength="50"  value="<?php if ($eingabe_ungueltig_adresse) { echo htmlspecialchars($_POST['name'],ENT_QUOTES,'UTF-8');}else{ echo htmlspecialchars($profil->get_name_from_kid($kid),ENT_QUOTES,'UTF-8'); } ?>" class="lang_reg" <?php if($eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('name') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		             <p class="reg_form_zeile" >
		              	<span>Geschlecht:</span>
		              	<?php
		              		$gechlecht = "männlich";
		              		//wenn das Formular schon submitet wurde und ein Feld als ausgefüllt war
		              		if ( $eingabe_ungueltig_adresse){
		              			$gechlecht = $_POST['geschlecht'];
		              		}else{ //wenn die Daten aus der Datenbank gelesen werden und das Dokument noch nicht submitted wurde
		              			$gechlecht = $profil->get_geschlecht_from_kid($kid);
		              		}
		              	?>
		              	<input type="radio" name="geschlecht" id="maennlich" value="männlich" <?php if($gechlecht == 'männlich') echo 'checked="checked"'; ?>  />
		            	<label for="maennlich">m&auml;nnlich</label>
		            	
		            	<input type="radio" name="geschlecht" id="weiblich" value="weiblich" <?php if($gechlecht != 'männlich') echo 'checked="checked"'; ?> />
		            	<label for="weiblich">weiblich</label>
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="strasse" >Stra&szlig;e:</label>
		                <input type="text" name="strasse" maxlength="50" value="<?php if ($eingabe_ungueltig_adresse) { echo htmlspecialchars($_POST['strasse'],ENT_QUOTES,'UTF-8');}else{ echo htmlspecialchars($profil->get_strasse_from_kid($kid),ENT_QUOTES,'UTF-8'); } ?>" class="std_reg" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('strasse') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		                <label for="hausnr" class="hausnr" >Haus Nr.:</label>
		                <input type="text" name="hausnr" maxlength="5"  value="<?php if ($eingabe_ungueltig_adresse) {echo  htmlspecialchars($_POST['hausnr'],ENT_QUOTES,'UTF-8'); }else{ echo htmlspecialchars($profil->get_hausnr_from_kid($kid),ENT_QUOTES,'UTF-8'); } ?>" class="hausnr" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('hausnr') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		             <p class="reg_form_zeile" >
		                <label for="plz" >PLZ:</label>
		                <input type="text" name="plz" maxlength="5"  value="<?php if ($eingabe_ungueltig_adresse) { echo htmlspecialchars($_POST['plz'],ENT_QUOTES,'UTF-8');}else{ echo htmlspecialchars($profil->get_plz_from_kid($kid),ENT_QUOTES,'UTF-8'); } ?>" class="plz" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('plz') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		                
		                <label for="ort" class="ort" >Ort:</label>
		                <input type="text" name="ort" maxlength="50"  value="<?php if ($eingabe_ungueltig_adresse) { echo htmlspecialchars($_POST['ort'],ENT_QUOTES,'UTF-8'); }else{ echo htmlspecialchars($profil->get_ort_from_kid($kid),ENT_QUOTES,'UTF-8'); } ?>" class="std_reg" <?php if( $eingabe_ungueltig_adresse && $eingabe_check_result_adresse->get_feldstatus('ort') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            		            
		            <p class="text_fehlermeldung" id="EingabeAdresse_fehlermeldung" >
		            	<?php
		            		//zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
		            		if ($eingabe_ungueltig_adresse){
		            			echo htmlspecialchars($eingabe_check_result_adresse->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
		            		} 
		            	?>
		            </p>
		            
		            <input type="hidden" name="type" value="adresse_aendern" />	            
		            
		            <input type="submit" value="Ändern" title="Ändern" />
		            <div class="clear_right" >
		            </div>
			        
		        </div>
	        </div>
        </div>
    </form>
    
    
    <form method="post" action="./?type=email_passwort_bearbeiten&page=profilbearbeiten" onsubmit="return vorcheckEingabeEmailPasswort();" id="form_email_passwort_aendern" name="form_email_passwort_aendern" >
        <h2>
		     Email-Adresse und Passwort ändern
		</h2>
        <div class="reg_box_aufteilung" >
        	<div class="TableRow_reg" >
	        	<div class="email_aendern_box_iconbereich" >
	        	</div> 
	        
		        <div class="form_content" >		            
		            <input type="hidden" name="type" value="email_passwort_aendern" />
		            		            
		            <p class="reg_form_zeile" >
		                <label for="email">Email:</label>
		                <input type="text" name="email" maxlength="50"  value="<?php if ($eingabe_ungueltig_email_passwort){ echo htmlspecialchars($_POST['email'],ENT_QUOTES,'UTF-8');} else{ echo htmlspecialchars($profil->get_email_from_kid($kid),ENT_QUOTES,'UTF-8'); } ?>" class="lang_reg" <?php if( $eingabe_ungueltig_email_passwort && $eingabe_check_result_email_passwort->get_feldstatus('email') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="passwort_alt">altes Passwort:</label>
		                <input type="password" name="passwort_alt" maxlength="50"  class="lang_reg" <?php if( $eingabe_ungueltig_email_passwort && $eingabe_check_result_email_passwort->get_feldstatus('passwort_alt') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>            
		            
		            <p class="reg_form_zeile" >
		                <label for="passwort">Passwort:</label>
		                <input type="password" name="passwort" maxlength="50"  class="lang_reg" <?php if( $eingabe_ungueltig_email_passwort && $eingabe_check_result_email_passwort->get_feldstatus('passwort') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            <p class="reg_form_zeile" >
		                <label for="wpasswort">Passwort-Wiederholung:</label>
		                <input type="password" name="wpasswort" maxlength="50" class="lang_reg"  <?php if( $eingabe_ungueltig_email_passwort && $eingabe_check_result_email_passwort->get_feldstatus('wpasswort') ) echo 'style="border-color:red; border-style: solid"';  ?>  />
		            </p>
		            
		            <p class="text_fehlermeldung" id="email_passwort_fehlermeldung" >
		            	<?php
		            		//zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
		            		if ($eingabe_ungueltig_email_passwort){
		            			echo htmlspecialchars($eingabe_check_result_email_passwort->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
		            		} 
		            	?>
		            </p>            
		            
		            <input type="submit" value="Ändern" title="Ändern" />
		            <div class="clear_right" >
		            </div>
			        
		        </div>
	        </div>
        </div>
    </form>
    
