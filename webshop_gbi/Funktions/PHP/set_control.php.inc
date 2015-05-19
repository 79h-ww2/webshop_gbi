<?php
	//lädt die von der Seite benötigten Funktionen
	if (isset($_POST['type'])){
		switch ($_POST['type']){
			
			//Skript zur Durchführung der Registrierung ausführen
			case 'reg':
				include_once './Funktions/PHP/registrierung_durchfuehren.php.inc';
			break;
			
			//Skript zur Durchführung der Anmeldung ausführen
			case 'anmeldung':
				include_once './Funktions/PHP/anmeldung_durchfuehren.php.inc';
			break;
		}
	}
	
	//aktiviert den neuen Kunden
	if (isset($_GET['account-activate'])){
		include_once './Funktions/PHP/kunde_aktivieren.php.inc';
	}
?>