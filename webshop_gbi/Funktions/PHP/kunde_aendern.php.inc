<?php 

include_once 'Classes/Kunde.php.inc';
$eingabe_ungueltig_adresse = false;
//Adresse wurde geändert
if ( isset($_POST['vorname']) && isset($_POST['name']) && isset($_POST['strasse']) && isset($_POST['plz']) && isset($_POST['hausnr']) && isset($_POST['ort']) && isset($_POST['geschlecht']) ){
	
	
	$kunde1 = new Kunden();
	
	//Überprüft, ob die Eingabe gültig ist
	$eingabe_check_result_adresse = $kunde1->ueberpruefeEingabeAdresseAendern($_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['plz'], $_POST['hausnr'], $_POST['ort']);
	$eingabe_ungueltig_adresse = ($eingabe_check_result_adresse->get_fehlermeldung() != '');
	
	//wenn sie gültig ist, werden die Werte in der Datenbank geändert
	if (!$eingabe_ungueltig_adresse){
		$kid1 = $kunde1->get_kid_from_email($_SESSION['angemeldet']); //bestimmt aus der Kunden-Email-Adresse die Kundennummer
		
		//ändert die Kundenwerte  in der Datenbank
		$kunde1->adresseAendern($kid1, $_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['plz'], $_POST['hausnr'], $_POST['ort'], $_POST['geschlecht']);
	}
	
}
//Passwort und Email-Adresse wurde geändert
elseif (isset($_POST['email']) && isset($_POST['passwort']) && isset($_POST['wpasswort']) && isset($_POST['passwort_alt'])){
	die("Email");
}
?>