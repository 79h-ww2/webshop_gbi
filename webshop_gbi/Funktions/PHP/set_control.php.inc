<?php
	//lädt die von der Seite benötigten Funktionen
	if (isset($_POST['type'])){
		switch ($_POST['type']){
			
			//Skript zur Durchführung der Registrierung ausführen
			case 'reg':
				include_once './Funktions/PHP/registrierung_durchfuehren.php.inc';
			break;
			
			case 'adresse_aendern':
			case 'email_passwort_aendern':
				include_once './Funktions/PHP/kunde_aendern.php.inc';
			break;
						
			case 'neuerArtikelimWarenkorb':
			case 'markierung_loeschen_warenkorb':
			case 'warenkorb-artikel-mengenaewnderung':
				include_once './Funktions/PHP/warenkorb.php.inc';
			break;
				
			//Skript zur Durchführung der Anmeldung ausführen
			case 'anmeldung':
				include_once './Funktions/PHP/anmeldung_durchfuehren.php.inc';
			break;
			
			//fährt den Vorcheck der erweiterten Suche durch
			case 'erweiterte_suche':
				include_once './Classes/Ueberpruefresult.php.inc';
				include_once './Funktions/PHP/vorcheck_erweiterte_suche.php.inc';
			break;
			
			//arbeitet die Aufgaben ab, die mit dem Bestellvorgang zu tun haben
			case 'bestellvorgang_versandart':
			case 'bestellvorgang_zahlungsart':
			case 'bestellvorgang_lieferart':
			case 'bestellvorgang_agb':
				include_once 'Funktions/PHP/bestellvorgang.php.inc';
			break;
			
			//speichert Bewertungen
			case 'kommentar':
				include_once 'Funktions/PHP/kommentar_hochladen.php.inc';
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
			
			//Artikel aus dem Warenkorb entfernen ODER ändern der Bestellmenge eines Artikels im Warenkorb
			case 'artikel-warenkorb-entfernen':	
			case 'bestellmenge_warenkorbartikel_aendern':
				include_once './Funktions/PHP/warenkorb.php.inc';
			break;
		}
	}
?>