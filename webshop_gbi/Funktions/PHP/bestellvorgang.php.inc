<?php
	include_once 'Classes/bestellungen.php.inc';
	include_once 'Classes/bankeinzug.php.inc';
	
	$bankeinzug_eingabe_unguelig = false;
	$eingabe_ungueltig_adresse = false;
	$eingabe_check = "";
	
	//lädt die aktuell zwischengespeicherte Bestellung
	$bestellungen = new Bestellungen();
	$aktuelle_bestellung = $bestellungen->get_zwischengespeicherte_bestellungseinstellungen();

	//####################################################################
	//Die Versandart wird zwischengespeichert
	if ($_POST['type'] == 'bestellvorgang_versandart' && isset($_POST['versandart']) && $_POST['versandart'] != ""){		
		$aktuelle_bestellung->set_versandart($_POST['versandart']);
		$aktuelle_bestellung->set_durchgefuehrte_schritte(1);
		$bestellungen->set_zwischengespeicherte_bestellungseinstellungen($aktuelle_bestellung);
	}
	
	//####################################################################
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
		if (!$bankeinzug_fehler) {
			$aktuelle_bestellung->set_durchgefuehrte_schritte(3);
			header("location:./?page=bestellung&schritt=4");
		}
	}
	
	//####################################################################
	//Die Lieferadresse wird zwischengespeichert
	elseif ($_POST['type'] == 'bestellvorgang_lieferart' && isset($_POST['adresse']) && $_POST['adresse'] != ""){
		
		include_once 'Classes/Kunde.php.inc';
		
		$adresse_fehler = false;
				
		//Die Adressenart wird zwischengespeichert
		$aktuelle_bestellung->set_lieferadresse_art($_POST['adresse']);
		
		//Wenn angekreuzt wurde, dass eine andere Adresse verwendet werden soll
		$kunde1 = new Kunden();
		if ($_POST['adresse'] == 'andere'){
			//Adresse wurde geändert
			if ( isset($_POST['vorname']) && isset($_POST['name']) && isset($_POST['strasse']) && isset($_POST['plz']) && isset($_POST['hausnr']) && isset($_POST['ort']) && isset($_POST['geschlecht']) ){
						
				//Überprüft, ob die Eingabe gültig ist
				$eingabe_check_result_adresse = $kunde1->ueberpruefeEingabeAdresseAendern($_POST['vorname'], $_POST['name'], $_POST['strasse'], $_POST['plz'], $_POST['hausnr'], $_POST['ort']);
				$eingabe_ungueltig_adresse = ($eingabe_check_result_adresse->get_fehlermeldung() != '');
			
				//wenn sie gültig ist, werden die Werte in Zwischengespeichert
				if (!$eingabe_ungueltig_adresse){
					$aktuelle_bestellung->set_liefer_geschlecht($_POST['geschlecht']);
					$aktuelle_bestellung->set_liefer_hausnr($_POST['hausnr']);
					$aktuelle_bestellung->set_liefer_name($_POST['name']);
					$aktuelle_bestellung->set_liefer_ort($_POST['ort']);
					$aktuelle_bestellung->set_liefer_plz($_POST['plz']);
					$aktuelle_bestellung->set_liefer_strasse($_POST['strasse']);
					$aktuelle_bestellung->set_liefer_vorname($_POST['vorname']);
				}else{
					$adresse_fehler = true;
				}
			}
		}
		//speichert die Kundenadresse als Lieferadresse
		else{
			//Kundennr bestimmen
			$kid = $kunde1->get_kid_from_email($_SESSION['angemeldet']);
			
			$aktuelle_bestellung->set_liefer_geschlecht($kunde1->get_geschlecht_from_kid($kid));
			$aktuelle_bestellung->set_liefer_hausnr($kunde1->get_hausnr_from_kid($kid));
			$aktuelle_bestellung->set_liefer_name($kunde1->get_name_from_kid($kid));
			$aktuelle_bestellung->set_liefer_ort($kunde1->get_ort_from_kid($kid));
			$aktuelle_bestellung->set_liefer_plz($kunde1->get_plz_from_kid($kid));
			$aktuelle_bestellung->set_liefer_strasse($kunde1->get_strasse_from_kid($kid));
			$aktuelle_bestellung->set_liefer_vorname($kunde1->get_vorname_from_kid($kid));
		}
		
		//Daten werden in der SESSION-Variable zwischengespeichert
		$bestellungen->set_zwischengespeicherte_bestellungseinstellungen($aktuelle_bestellung);
		
		//wenn alle Eingaben gültig waren wird zur nächsten Seite weitergeleitet
		if (!$adresse_fehler) {
			$aktuelle_bestellung->set_durchgefuehrte_schritte(4);
			header("location:./?page=bestellung&schritt=5");
		}
	}
?>