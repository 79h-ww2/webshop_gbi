<?php
	include_once 'Classes/bestellungen.php.inc';
	include_once 'Classes/bankeinzug.php.inc';
	
	$bankeinzug_eingabe_unguelig = false;
	$eingabe_check = "";
	
	//lädt die aktuell zwischengespeicherte Bestellung
	$bestellungen = new Bestellungen();
	$aktuelle_bestellung = $bestellungen->get_zwischengespeicherte_bestellungseinstellungen();

	//Die Versandart wird zwischengespeichert
	if ($_POST['type'] == 'bestellvorgang_versandart' && isset($_POST['versandart']) && $_POST['versandart'] != ""){		
		$aktuelle_bestellung->set_versandart($_POST['versandart']);
		$bestellungen->set_zwischengespeicherte_bestellungseinstellungen($aktuelle_bestellung);
	}
	
	//Die Zahlungart wird zwischengespeichert
	elseif ($_POST['type'] == 'bestellvorgang_zahlungsart' && isset($_POST["zahlungsart"]) && $_POST["zahlungsart"] != ""){
		
		$bankeinzug_fehler = false;
		
		//Die Zahlungsart wird zwischengespeichert
		$aktuelle_bestellung->set_zahlungsart($_POST["zahlungsart"]);
		
		//Wenn es sich um ein Bankeinzuhandelt, werden die Kontodaten des Benutzers zwischengespeichert
		if ( $_POST["zahlungsart"] == 'bankeinzug'){
			if ( isset($_POST['inhaber']) && isset($_POST['iban']) && isset($_POST['bic']) ){
				
				//überprüft die eingegeben Daten
				$bankeinzug = new Bankeinzug($_POST['iban'], $_POST['bic'], $_POST['inhaber']);
				$eingabe_check = $bankeinzug->daten_pruefen();
				$bankeinzug_eingabe_unguelig = ($eingabe_check->get_fehlermeldung() != "");
				
				//wenn die Eingabe gültig war
				if (!$bankeinzug_eingabe_unguelig){
					//Die Bankeinzugsdaten werden zwischen gespeichert
					$aktuelle_bestellung->set_bankeinzug_daten($bankeinzug);
				}else{
					$bankeinzug_fehler = true;
				}
			}
		}
		
		$bestellungen->set_zwischengespeicherte_bestellungseinstellungen($aktuelle_bestellung);
		
		//wenn alle Eingaben gültig waren wird zur nächsten Seite weitergeleitet
		if (!$bankeinzug_fehler) header("location: ./?page=bestellung&schritt=4");
	}
?>