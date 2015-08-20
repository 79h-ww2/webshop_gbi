<?php
$eingabe_ungueltig_login = isset ( $eingabe_ungueltig_login ) ? $eingabe_ungueltig_login : false;


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
<script type="text/javascript" src="./Funktions/JS/anmeldung.js" >
</script>
<form method="post" action="<?php echo $url; ?>" name="form_login"	id="login" onsubmit="return vorcheckEingabe_anmeldung('form_login');">
	<h2>
	Anmeldung
	</h2>
	<div class="reg_box_aufteilung">
		<div class="TableRow_reg">
<div class="reg_box_iconbereich" >
	        	</div> 
	        
			<div class="form_content">

				<p class="reg_form_zeile">
					<label for="anmedlung_email">Email:</label> <input
						autocomplete="off" type="text" name="anmedlung_email"
						maxlength="50"  class="lang_reg"
						value="<?php if ($eingabe_ungueltig_anmeldung) echo htmlspecialchars($_POST['anmedlung_email'],ENT_QUOTES,'UTF-8'); ?>"
						<?php if( $eingabe_ungueltig_anmeldung && $eingabe_check_result_anmeldung->get_feldstatus('anmedlung_email') ) echo 'style="border-color:red; border-style: solid"';  ?> />
				</p>
				<p class="reg_form_zeile">
					<label for="anmedlung_passwort">Passwort:</label> <input
						type="password" name="anmedlung_passwort" maxlength="50"  class="lang_reg"
						<?php if( $eingabe_ungueltig_anmeldung && $eingabe_check_result_anmeldung->get_feldstatus('anmedlung_passwort') ) echo 'style="border-color:red; border-style: solid"';  ?> />
				</p>
				<input type="hidden" name="type" value="anmeldung" />
				<input type="hidden" name="type1" value="bewertung" />

				<p class="text_fehlermeldung" id="fehlermeldung_login">
						<?php
						// zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
						if ($eingabe_ungueltig_anmeldung) {
							echo htmlspecialchars($eingabe_check_result_anmeldung->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
						}
						?>
					</p>
						

				<input type="submit"  value="Login" title="Login"/>

				<!--<a href="" title="Passwort vergessen" id="passwort_link" >
						Passwort vergessen
					</a>-->
				<div id="reg_link">
					Sie haben noch kein Konto? Registrieren Sie sich <a	href="./?page=reg" title="Registrierung" style="color:black"> hier </a>
				</div>

				<div class="clear_right"></div>
			</div>
		</div>
	</div>
</form>
