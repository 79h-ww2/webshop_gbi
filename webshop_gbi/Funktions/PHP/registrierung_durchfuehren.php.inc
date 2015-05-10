<?php
	include_once './Classes/Ueberpruefresult.php.inc';
	include_once './Classes/Kunde.php.inc';
	
	$eingabe_ungueltig = false;
	
	if ( isset($_POST['vorname']) && isset($_POST['name']) && isset($_POST['strasse']) && isset($_POST['plz']) && isset($_POST['hausnr']) && isset($_POST['ort']) && isset($_POST['email']) && isset($_POST['passwort']) && isset($_POST['wpasswort']) )
	$kunde = new Kunden();
	
	//überprüft die Eingabe auf Gültigkeit
	$eingabe_check_result = $kunde->ueberpruefeEingabe($_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['plz'], $_POST['hausnr'], $_POST['ort'], $_POST['email'], $_POST['passwort'], $_POST['wpasswort']);
	$eingabe_ungueltig = ($eingabe_check_result->get_fehlermeldung() != '');
	
	//wenn keine Eingabe ungültig war wir mit der Registierung angefangen
	if ( !$eingabe_ungueltig ){
		/*
		 * Hiewr folgt Quellcode
		 */
	}
?>