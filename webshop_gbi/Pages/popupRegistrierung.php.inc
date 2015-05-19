<?php
?>

<div class="popupRegistrierung">
	<script type="text/javascript" src="./Funktions/JS/anmeldung.js" >
	</script>
	<div class="haken_sprechblase" >
	</div>
	<div class="contentPopupRegistrierung" >
		<div id="popup_reg_fensterteiler">
			<div id="popup_reg_anmeldungsteil" >
				<form method="post" action="" name="anmeldung" onsubmit="return vorcheckEingabe_anmeldung();" >
					<label for="anmedlung_email" >
						Email:
					</label>
					<input type="text" name="anmedlung_email" /> 
					<label for="anmedlung_passwort" >
						Passwort:
					</label>
					<input type="password" name="anmedlung_passwort" />
					
					<p class="fehlermeldung_anmelden" id="fehlermeldung_anmelden" >
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
				<a href="./?page=reg" titel="Registrierung" class="link_button" id="link_button_reg_popup" >
					Registrierung
				</a>
			</div>
		</div>
	</div>
</div>
