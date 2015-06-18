    <?php 
 		$eingabe_ungueltig = isset($eingabe_ungueltig) ? $eingabe_ungueltig : false;
 	?>
 	<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
    </script>
    <script type="text/javascript" src="./Funktions/JS/vorcheck_profil_aendern.js" >
    </script>
    <form method="post" action="#" onsubmit="return vorcheckEingabeAdresse();" id="form_adresse_aendern" name="form_adresse_aendern" >
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
		                <input type="text" name="vorname" maxlength="50" value="<?php if ($eingabe_ungueltig) echo htmlspecialchars($_POST['vorname'],ENT_QUOTES,'UTF-8'); ?>" class="lang_reg" <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('vorname') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="name">Name:</label>
		                <input type="text" name="name" maxlength="50"  value="<?php if ($eingabe_ungueltig) echo htmlspecialchars($_POST['name'],ENT_QUOTES,'UTF-8'); ?>" class="lang_reg" <?php if($eingabe_ungueltig && $eingabe_check_result->get_feldstatus('name') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		             <p class="reg_form_zeile" >
		              	<span>Geschlecht:</span>
		              	<input type="radio" name="geschlecht" id="maennlich" value="männlich" checked="checked" />
		            	<label for="maennlich">m&auml;nnlich</label>
		            	
		            	<input type="radio" name="geschlecht" id="weiblich" value="weiblich"  />
		            	<label for="weiblich">weiblich</label>
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="strasse" >Stra&szlig;e:</label>
		                <input type="text" name="strasse" maxlength="50"  value="<?php if ($eingabe_ungueltig) echo htmlspecialchars($_POST['strasse'],ENT_QUOTES,'UTF-8'); ?>" class="std_reg" <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('strasse') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		                <label for="hausnr" class="hausnr" >Haus Nr.:</label>
		                <input type="text" name="hausnr" maxlength="5"  value="<?php if ($eingabe_ungueltig) echo htmlspecialchars($_POST['hausnr'],ENT_QUOTES,'UTF-8'); ?>" class="hausnr" <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('hausnr') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		             <p class="reg_form_zeile" >
		                <label for="plz" >PLZ:</label>
		                <input type="text" name="plz" maxlength="5"  value="<?php if ($eingabe_ungueltig) echo htmlspecialchars($_POST['plz'],ENT_QUOTES,'UTF-8'); ?>" class="plz" <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('plz') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		                
		                <label for="ort" class="ort" >Ort:</label>
		                <input type="text" name="ort" maxlength="50"  value="<?php if ($eingabe_ungueltig) echo htmlspecialchars($_POST['ort'],ENT_QUOTES,'UTF-8'); ?>" class="std_reg" <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('ort') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            		            
		            <p class="text_fehlermeldung" id="EingabeAdresse_fehlermeldung" >
		            	<?php
		            		//zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
		            		if ($eingabe_ungueltig){
		            			echo htmlspecialchars($eingabe_check_result->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
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
    
    
    <form method="post" action="#" onsubmit="return vorcheckEingabeEmailPasswort();" id="form_email_passwort_aendern" name="form_email_passwort_aendern" >
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
		                <input type="text" name="email" maxlength="50"  value="<?php if ($eingabe_ungueltig) echo htmlspecialchars($_POST['email'],ENT_QUOTES,'UTF-8'); ?>" class="lang_reg" <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('email') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="passwort">Passwort:</label>
		                <input type="password" name="passwort" maxlength="50"  class="lang_reg" <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('passwort') ) echo 'style="border-color:red; border-style: solid"';  ?> />
		            </p>
		            <p class="reg_form_zeile" >
		                <label for="wpasswort">Passwort-Wiederholung:</label>
		                <input type="password" name="wpasswort" maxlength="50" class="lang_reg"  <?php if( $eingabe_ungueltig && $eingabe_check_result->get_feldstatus('wpasswort') ) echo 'style="border-color:red; border-style: solid"';  ?>  />
		            </p>
		            
		            <p class="text_fehlermeldung" id="email_passwort_fehlermeldung" >
		            	<?php
		            		//zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
		            		if ($eingabe_ungueltig){
		            			echo htmlspecialchars($eingabe_check_result->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
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
    