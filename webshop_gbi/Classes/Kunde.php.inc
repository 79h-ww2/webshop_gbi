<?php
	include_once './Classes/Ueberpruefresult.php.inc';

	class Kunden{
		
		
		public function ueberpruefeEingabe ($vorname, $name, $strasse, $plz, $hausnr, $ort, $email, $passwort, $wpasswort){
			
			//Objekt, über das der Funktionsrückgabewert übergeben werden soll
			$return = new Ueberpruefresult();
						
			//Array mit allen Feldern, die ausgefüllt sein müssen
			$felder = array($vorname, $name, $strasse, $plz, $hausnr, $ort, $email, $passwort, $wpasswort);
			$feldnamen = array('vorname', 'name', 'strasse', 'hausnr', 'plz', 'ort', 'email', 'passwort', 'wpasswort');
			
			//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
			$meldungswort = array('ihren Vornamen', 'ihren Namen', 'ihre Straße', 'ihre Hausnummer', 'ihr Postleitzahl', 'ihr Ort', 'ihre Email-Adresse', 'ein Passwort', 'die Passwort-Wiederholung');
			
			//Variable, wo die Fehlermeldung zwischengespeichert wird
			$fehlermeldung = "";
			
			//Array, wo alle nicht ausgefüllten Felder gespeichert werden sollen
			$nicht_ausgefuellte_felder = array();
			
			//überprüft jedes Feld
			$z = 0;
			for($i = 0; $i < count($felder); $i++){
				//wenn das Feld nicht ausgefüllt ist
				if ($felder[$i] == ""){
					//fügt das Feld zur Liste der nicht ausgefüllten Felder hinzu
					$nicht_ausgefuellte_felder[$z] = $meldungswort[$i];
					$z++;
					
					//schaltet das Feld in den Rückgabeobjekt auf fehlerhaft
					$return->set_feldstatus($feldnamen[$i], true);
				}
				//wenn das Feld richtig ausgefüllt ist
				else{
					//schaltet das Feld in den Rückgabeobjekt auf nicht fehlerhaft
					$return->set_feldstatus($feldnamen[$i], false);
				}
			}
			
			//wenn nicht jedes Feld ausgefüllt ist, wird eine Fehlermeldung generiert
			if ( count($nicht_ausgefuellte_felder) > 0 ){
				if ( count($nicht_ausgefuellte_felder) == 1 ){
					$fehlermeldung = 'Bitte geben Sie '.$nicht_ausgefuellte_felder[0].' an.';
				}else{
					for ($j = 0; $j < count($nicht_ausgefuellte_felder); $j++){
						if ($j == 0){
							$fehlermeldung = 'Bitte geben Sie '.$nicht_ausgefuellte_felder[$j];
						}else if ( $j < (count($nicht_ausgefuellte_felder)-1)){
							$fehlermeldung .= ', '.$nicht_ausgefuellte_felder[$j];
						}else{
							$fehlermeldung .= ' und '.$nicht_ausgefuellte_felder[$j].' an.';
						}
					}
				}
			}
			//wenn alle Felder ausgefüllt sind, wird überprüft, ob die Eingaben gültig sind
			else{
				//überprüft, ob die PLZ gültig ist
				if ( strlen($plz) != 5 ||  is_numeric($plz) == false ){
					$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
					$fehlermeldung .= "Die Postleitzahl ist ung&uuml;ltig. Bitte geben Sie eine g&uuml;ltige Postleitzahl ein.";
					$return->set_feldstatus('plz', true);
				}
				
				//überprüft, ob die Passwörter übereinstimmen
				if ( $passwort != $wpasswort ){
					$fehlermeldung .= $fehlermeldung == '' ? '' : ' ';
					$fehlermeldung += "Die Passw&ouml;rter stimmen nicht überein.";
					$return->set_feldstatus('wpasswort', true);
					$return->set_feldstatus('passwort', true);
				}
				
				//überprüft, die Email-Adresse
				if (filter_var($email, FILTER_VALIDATE_EMAIL) == false){
					$fehlermeldung .= $fehlermeldung == '' ? '' : ' ';
					$fehlermeldung .= "Die Email-Adresse ist ung&uuml;ltig.";
					$return->set_feldstatus('email', true);
				}
			}
			
			//Übergibt an das Rückgabeobjekt die Fehlermeldung
			$return->set_fehlermeldung($fehlermeldung);
			
			return $return;
		}
	};
?>