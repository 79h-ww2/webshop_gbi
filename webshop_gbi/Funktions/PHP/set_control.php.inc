<?php
	//lÃ¤dt die von der Seite benÃ¶tigten Funktionen
	if (isset($_POST['type'])){
		switch ($_POST['type']){
			
			//Skript zur DurchfÃ¼hrung der Registrierung ausfÃ¼hren
			case 'reg':
				include_once './Funktions/PHP/registrierung_durchfuehren.php.inc';
			break;
			
			case 'adresse_aendern':
			case 'email_passwort_aendern':
				include_once './Funktions/PHP/kunde_aendern.php.inc';
			break;
						
			case 'neuerArtikelimWarenkorb':
				include_once './Funktions/PHP/warenkorb.php.inc';
			break;
				
			//Skript zur DurchfÃ¼hrung der Anmeldung ausfÃ¼hren
			case 'anmeldung':
				include_once './Funktions/PHP/anmeldung_durchfuehren.php.inc';
			break;
			
			//fÃ¼hrt den Vorcheck der erweiterten Suche durch
			case 'erweiterte_suche':
				include_once './Classes/Ueberpruefresult.php.inc';
				include_once './Funktions/PHP/vorcheck_erweiterte_suche.php.inc';
			break;
		}
	}
	
	//aktiviert den neuen Kunden
	if (isset($_GET['account-activate'])){
		include_once './Funktions/PHP/kunde_aktivieren.php.inc';
	}
	
	if (isset($_GET['aktion'])){
		switch ($_GET['aktion']){
			
			//Meldet den Kunden ab
			case 'abmelden':
				session_destroy();
				session_start();
			break;
		}
	}
?>