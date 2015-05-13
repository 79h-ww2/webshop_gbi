<?php
	//Kunde wird durch den Aktivierungslink aktiviert
	include_once './Classes/Kunde.php.inc';
	$kunde = new Kunden();
	$erfolgreich = $kunde->aktiviere_kunde_durch_aktivierungs_code($_GET['account-activate']);
	
	//wenn der Kunde erfolgreich aktiviert wurde, wird er über eine MSG-Box darüber informiert
	if ($erfolgreich){
		$meldung = "Das auf die Email-Adresse: \"".htmlspecialchars($_SESSION['angemeldet'],ENT_QUOTES,'UTF-8')."\" registrierte Benutzerkonto wurde erfolgreich aktiviert.";
		$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung("info_kunde_aktiviert", 'Benutzerkonto aktiviert', $meldung, 'info', '', true);
	}
	//wenn die Aktivierung nicht erfolgreich war
	else{
		$meldung = "Das Benutzerkonot konnte nicht aktiviert werden";
		$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung("info_kunde_aktiviert", 'Fehler bei der Aktivierung', $meldung, 'error', '', true);
	}
?>