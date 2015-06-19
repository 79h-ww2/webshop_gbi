<?php 

include_once 'Classes/Kunde.php.inc';
$eingabe_ungueltig_adresse = false;
//Adresse wurde geändert
if ( isset($_POST['vorname']) && isset($_POST['name']) && isset($_POST['strasse']) && isset($_POST['plz']) && isset($_POST['hausnr']) && isset($_POST['ort'])){
	$kunde1 = new Kunden();
	$eingabe_check_result = $kunde1->ueberpruefeEingabeAdresseAendern($_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['plz'], $_POST['hausnr'], $_POST['ort']);
	
	if($eingabe_check_result->get_fehlermeldung()) echo "Test";
	
	$eingabe_ungueltig_adresse = ($eingabe_check_result->get_fehlermeldung() != '');
	
	echo($eingabe_check_result->get_fehlermeldung());
}
//Passwort und Email-Adresse wurde geändert
elseif (isset($_POST['email']) && isset($_POST['passwort']) && isset($_POST['wpasswort']) && isset($_POST['passwort_alt'])){
	die("Email");
}
?>