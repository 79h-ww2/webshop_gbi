<?php
$eingabe_ungueltig_login = isset ( $eingabe_ungueltig_login ) ? $eingabe_ungueltig_login : false;
?>
<script type="text/javascript" src="./Funktions/JS/login.js">
	</script>


<?php
// Setzt die Action-Url zusammen
$url = $_SERVER ['PHP_SELF'];
if (isset ( $_GET ['page'] )) {
	$url .= "?page=" . htmlspecialchars ( $_GET ['page'], ENT_QUOTES, 'UTF-8' );
}
?>

<form method="post" action="<?php echo $url; ?>" name="form_login"
	id="login" onsubmit="return vorcheckEingabe_login();">
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
						value="<?php if ($eingabe_ungueltig_login) echo htmlspecialchars($_POST['anmedlung_passwort'],ENT_QUOTES,'UTF-8'); ?>"
						<?php if( $eingabe_ungueltig_login && $eingabe_check_result_login->get_feldstatus('anmedlung_passwort') ) echo 'style="border-color:red; border-style: solid"';  ?> />
				</p>
				<input type="hidden" name="type" value="login" />

				<p class="text_fehlermeldung" id="fehlermeldung_login">
						<?php
						// zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
						if ($eingabe_ungueltig_login) {
							echo htmlspecialchars ( $eingabe_check_result_login->get_fehlermeldung (), ENT_QUOTES, 'UTF-8' );
						}
						?>
					</p>

				<input type="submit"  value="Login" title="Login"/>

				<!--<a href="" title="Passwort vergessen" id="passwort_link" >
						Passwort vergessen
					</a>-->

				<div class="clear_right"></div>
				<div id="reg_link">
					Sie haben noch kein Konto? Registrieren Sie sich <a
						href="./?page=reg" title="Registrierung"> hier </a>
				</div>
			</div>
		</div>
	</div>
</form>
