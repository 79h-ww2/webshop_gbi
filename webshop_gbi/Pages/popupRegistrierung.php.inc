<?php 
	$eingabe_ungueltig_anmeldung = isset($eingabe_ungueltig_anmeldung) ? $eingabe_ungueltig_anmeldung : false;
?>
<div class="popupRegistrierung" id="popupRegistrierung" 
<?php if($eingabe_ungueltig_anmeldung  && !isset($_POST['type1'] ))	echo 'style="visibility: visible;"' ?> >
	<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
    </script>
	<script type="text/javascript" src="./Funktions/JS/anmeldung.js" >
	</script>
	<div class="haken_sprechblase" >
	</div>
	<div class="contentPopupRegistrierung" >
		<div id="popup_reg_fensterteiler">
			<div id="popup_reg_anmeldungsteil" >
				<?php 
					//Setzt die Action-Url zusammen
					/*$url = $_SERVER['PHP_SELF']; 
					if ( isset($_GET['page'])){
						$url .= "?page=".htmlspecialchars($_GET['page'],ENT_QUOTES,'UTF-8');
					}*/	
				
					//Setzt die Action-Url zusammen
					$url = ( count($_GET) > 0 ) ?  "./?" : "./";
						
					$get_feldnamen = array_keys($_GET);
					for ( $i = 0; $i < count($_GET); $i++)
					{
						$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
						$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
						
						if ($feldname != "aktion" && $wert != "abmelden"){ //übernimmt nur die Get-Parameter, wenn sie nicht zum gleichzeitigen Abmelden führen
							if ( $i > 0) $url .= "&";
							$url .= $feldname."=".$wert;
						}
					}
				?>
				<form method="post" action="<?php echo $url; ?>" name="anmeldung" onsubmit="return vorcheckEingabe_anmeldung('anmeldung');" >
					<label for="anmedlung_email" >Email:</label>
					<input autocomplete="off" type="text" name="anmedlung_email" value="<?php if ($eingabe_ungueltig_anmeldung) echo htmlspecialchars($_POST['anmedlung_email'],ENT_QUOTES,'UTF-8'); ?>" <?php if( $eingabe_ungueltig_anmeldung && $eingabe_check_result_anmeldung->get_feldstatus('anmedlung_email') ) echo 'style="border-color:red; border-style: solid"';  ?> /> 
					<label for="anmedlung_passwort">Passwort:</label>
					<input  type="password" name="anmedlung_passwort"  <?php if( $eingabe_ungueltig_anmeldung && $eingabe_check_result_anmeldung->get_feldstatus('anmedlung_passwort') ) echo 'style="border-color:red; border-style: solid"';  ?> />
					
					<input type="hidden" name="type" value="anmeldung" />
					
					<p class="fehlermeldung_anmelden" id="fehlermeldung_anmelden" >
						<?php
		            		//zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
		            		if ($eingabe_ungueltig_anmeldung){
		            			echo htmlspecialchars($eingabe_check_result_anmeldung->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
		            		} 
		            	?>
					</p>
					
					<input type="submit" name="anmeldung_submit" value="Login" />
					
					<!--<a href="" title="Passwort vergessen" id="passwort_link" >
						Passwort vergessen
					</a>-->
					
					<div class="clear_right" >
					</div>
				</form>
			</div>
			<div id="popup_reg_registrierungsteil" >
				<a href="./?page=reg" title="Registrierung" class="link_button" id="link_button_reg_popup" >
					Registrierung
				</a>
			</div>
		</div>
	</div>
</div>
