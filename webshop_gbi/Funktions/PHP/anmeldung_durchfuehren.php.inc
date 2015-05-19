<?php
	include_once './Classes/Ueberpruefresult.php.inc';
	include_once './Classes/Kunde.php.inc';
	
	$eingabe_ungueltig_anmeldung = false;
	
	//überprüft, ob die Input-Felder existieren
	if( isset($_POST['anmedlung_email']) && isset($_POST['anmedlung_passwort'])){
		$kunde = new Kunden();
		
		//überprüft die Eingabe auf Gültigkeit
		$eingabe_check_result_anmeldung = $kunde->ueberpruefeEingabeAnmeldung($_POST['anmedlung_email'], $_POST['anmedlung_passwort']);
		$eingabe_ungueltig_anmeldung = ($eingabe_check_result_anmeldung->get_fehlermeldung() != '');
		
		//wenn die Eingabe gültig war, wird der Kunde angemeldet 
		if (!$eingabe_ungueltig_anmeldung){
			$_SESSION['angemeldet'] = $_POST['anmedlung_email'];
		}
	}
?>