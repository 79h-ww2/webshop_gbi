<?php
?>

<div class="popupRegistrierung">
	<div class="haken_sprechblase" >
	</div>
	<div class="contentPopupRegistrierung" >
		<div id="popup_reg_fensterteiler">
			<div id="popup_reg_anmeldungsteil" >
				<form method="post" action="" name="anmeldung" >
					<label for="anmedlung_email" >
						Email:
					</label>
					<input type="email" name="anmedlung_email" /> 
					<label for="anmedlung_passwort" >
						Passwort:
					</label>
					<input type="password" name="anmedlung_passwort" />
					
					<input type="submit" name="anmeldung_submit" value="Login" />
					
					<a href="" title="Passwort vergessen" id="passwort_link" >
						Passwort vergessen
					</a>
					
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
