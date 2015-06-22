<?php 

include_once 'Classes/Kunde.php.inc';
$eingabe_ungueltig_adresse = false;

//erlaubt nur das Ändern, wenn der Kunde angemeldet ist
if ( isset($_SESSION['angemeldet'])){

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
			$erfolgreich = $kunde1->adresseAendern($kid1, $_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['plz'], $_POST['hausnr'], $_POST['ort'], $_POST['geschlecht']);
			
			//Informationbox, die den Kunden informiert, ob die Änderung erfolgtreich ausgeführt wurde
			if ($erfolgreich){
				$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung('anschrift', 'Änderung der Anschrift', 'Ihre Anschrift wurde erfolgreich geändert.', 'info', '', true);
			}else{
				$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung('anschrift', 'Änderung der Anschrift', 'Beim Änder der Anschrift ist ein Fehler aufgetreten.', 'error', '', true);
			}
		}
		
	}
	//Passwort und Email-Adresse wurde geändert
	elseif (isset($_POST['email']) && isset($_POST['passwort']) && isset($_POST['wpasswort']) && isset($_POST['passwort_alt'])){
		$kunde2 = new Kunden();
		
		//überprüft, ob die Eingabe gültig ist
		$eingabe_check_result_email_passwort = $kunde2->ueberpruefeEingabeEmailUndPasswortAendern($_POST['email'], $_POST['passwort'], $_POST['wpasswort'], $_POST['passwort_alt'], $_SESSION['angemeldet']);
		$eingabe_ungueltig_email_passwort = ($eingabe_check_result_email_passwort->get_fehlermeldung() != '');
		
		//wenn die Eingabe gültig war, werden die Werte in der Datenbank geändert
		if (!$eingabe_ungueltig_email_passwort){
			$kid2 = $kunde2->get_kid_from_email($_SESSION['angemeldet']); //bestimmt aus der Kunden-Email-Adresse die Kundennummer
			
			//änder das Passwort und die Email-Adresse in der Datenbank
			$erfolgreich = $kunde2->EmailUndPasswortAendern($kid2, $_POST['email'], $_POST['passwort']);
			
			//Informationbox, die den Kunden informiert, ob die Änderung erfolgtreich ausgeführt wurde
			if ($erfolgreich){
				$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung('email_passwort_aendern', 'Passwort- und Email-Änderung', 'Die Email-Adresse und das Passwort wurden erfolgreich geändert.', 'info', '', true);
			}else{
				$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung('email_passwort_aendern', 'Passwort- und Email-Änderung', 'Die Änderung ihrer Email-Adresse und des Passworts ist fehlgeschlagen.', 'error', '', true);
			}
		} 
	}
}
//Meldung anzeigen wenn der Kunde nicht angemeldet ist
else{
	echo "Sie müssen angemeldet sein, um Ihr Profil ändern zu können.";
}
?>