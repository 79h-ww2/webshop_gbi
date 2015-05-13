<?php
	include_once './Classes/Ueberpruefresult.php.inc';
	include_once './Classes/Kunde.php.inc';
	
	$eingabe_ungueltig = false;
	
	if ( isset($_POST['vorname']) && isset($_POST['name']) && isset($_POST['strasse']) && isset($_POST['plz']) && isset($_POST['hausnr']) && isset($_POST['ort']) && isset($_POST['email']) && isset($_POST['passwort']) && isset($_POST['wpasswort']) && isset($_POST['geschlecht']) )
	$kunde = new Kunden();
	
	//überprüft die Eingabe auf Gültigkeit
	$eingabe_check_result = $kunde->ueberpruefeEingabe($_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['plz'], $_POST['hausnr'], $_POST['ort'], $_POST['email'], $_POST['passwort'], $_POST['wpasswort']);
	$eingabe_ungueltig = ($eingabe_check_result->get_fehlermeldung() != '');
	
	//wenn keine Eingabe ungültig war wir mit der Registierung angefangen
	if ( !$eingabe_ungueltig ){
		
		//Kunde wird zur Datenbank hinzugefügt
		$id_neuer_kunde = $kunde->kunde_registrieren($_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['hausnr'], $_POST['plz'], $_POST['ort'], $_POST['email'], $_POST['passwort'], $_POST['geschlecht']);

		if ($id_neuer_kunde != false){
			
			//Aktivierungs-Email versenden
			$kunde->sende_aktivierungsemail_registrierung($id_neuer_kunde);
			
			//Informiert den Kunden über eine Messagebox, dass die Registrierung erfolgreich war und er das Benutzerkonto über den Email-Link aktivieren muss
			$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung('info_reg_erfolgreich', 'Registrierung erfolgreich', 'Ihr Benutzerkonto wurde erfolgreich erstellt. Bitte aktivieren Sie es über die Aktivierungs-Email, die Sie an ihrer angegebenen Email-Adresse erhalten haben sollten.', 'info', '', true);
		}else{
			//Informiert den Kunden über eine Messagebox, dass die Registrierung erfolgreich war und er das Benutzerkonto über den Email-Link aktivieren muss
			$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung('info_reg_erfolgreich', 'Fehler', 'Die Registrierung ist fehlgeschlagen', 'error', '', true);
		}
	}
?>