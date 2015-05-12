<?php
	include_once './Classes/Ueberpruefresult.php.inc';
	include_once './Classes/Email.php.inc';

	class Kunden{
		
		/**
		 * überprüft, die Benutzereingabe des Registrierungsfensters 
		 * @param string $vorname Vorname
		 * @param string $name Name
		 * @param string $strasse Strasse
		 * @param string $plz Postleitzahl
		 * @param string $hausnr Hausnummer
		 * @param string $ort Ort
		 * @param string $email Email-Adresse
		 * @param string $passwort Passwort
		 * @param string $wpasswort Wiederholdung des Passworts
		 * @return Ambigous <boolean, Eingabe gültig>
		 */
		public function ueberpruefeEingabe ($vorname, $name, $strasse, $plz, $hausnr, $ort, $email, $passwort, $wpasswort){
			
			//Objekt, über das der Funktionsrückgabewert übergeben werden soll
			$return = new Ueberpruefresult();
						
			//Array mit allen Feldern, die ausgefüllt sein müssen
			$felder = array($vorname, $name, $strasse, $hausnr, $plz, $ort, $email, $passwort, $wpasswort);
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
				//überprüft, ob die Email-Adresse nicht schon im System gespeichert ist
				elseif ($this->email_in_db_vorhanden($email)){
					$fehlermeldung .= $fehlermeldung == '' ? '' : ' ';
					$fehlermeldung .= "Die Email-Adresse wird schon von einer anderen Person verwendet.";
					$return->set_feldstatus('email', true);
				}
			}
			
			//Übergibt an das Rückgabeobjekt die Fehlermeldung
			$return->set_fehlermeldung($fehlermeldung);
			
			return $return;
		}
		
		/**
		 * überprüft, ob die Email-Adresse schon in der Datenbank existiert
		 * @param unknown $email Email-Adresse
		 * @return boolean Rückgabewert, ob die Email-Adresse existiert
		 */
		public function email_in_db_vorhanden ($email){
			
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			//Sonderzeichen entfernen, womit der Datenbankserver gehackt werden könnte
			$email_real_escape_string = $db->db_real_escape_string($email);
			
			//erstellen der Datenbank-Query
			$query = "select count(*) from kunde where Email = '$email_real_escape_string'";
			
			//die Query ausführen
			$result = $db->db_query($query);
			
			//Rückgabewert auslesen
			$gefundeneMenge = "";
			while ($werte = $db->db_fetch_array($result)){
				$gefundeneMenge = $werte[0];
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
						
			//gibt zurück, ob die Email-Adresse schon im System vorhanden ist
			return ($gefundeneMenge > 0);
		}
		
		/**
		 * erstellt den neuen Kunden
		 * @param string $vorname Vorname
		 * @param string $name Name
		 * @param string $strasse Straße
		 * @param string $hausnr Hausnummer
		 * @param string $plz Postleitzahl
		 * @param string $ort Wohnort
		 * @param string $email Email-Adresse
		 * @param string $passwort Passwort
		 * @return Ambigous <number, Kunden-ID>
		 */
		public function kunde_registrieren($vorname, $name, $strasse, $hausnr, $plz, $ort, $email, $passwort, $geschlecht){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			//Sonderzeichen entfernen
			$vorname = $db->db_real_escape_string($vorname);
			$name = $db->db_real_escape_string($name);
			$strasse = $db->db_real_escape_string($strasse);
			$hausnr = $db->db_real_escape_string($hausnr);
			$plz = $db->db_real_escape_string($plz);
			$ort = $db->db_real_escape_string($ort);
			$email= $db->db_real_escape_string($email);
			$passwort = md5($passwort);
			$id = $this->generiere_neu_kundennr();
			$geschlecht = $db->db_real_escape_string($geschlecht);
			
			//Query, um den Kunden in der Datenbank anzulegen
			$query = "
				insert into kunde(
					KId,
					Vorname,
					PLZ,
					Ort,
					Email,
					Strasse,
					Name,
					Stand,
					Passwort,
					geloescht,
					Geschlecht
				)values(
					'$id',
					'$vorname',
					'$plz',
					'$ort',
					'$email',
					'$strasse',
					'$name',
					now(),
					'$passwort',
					'nein',
					'$geschlecht'
				);
			";
			
			//Kunde zur Datenbank hinzufügen
			$result = $db->db_query($query);
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			//gibt beim Fehler den Wert false zurück bei erfolgreicher Durchführung die ID des neuen Kunden
			return (!$result) ? false : $id;
		}
		
		/**
		 * generiert eine neue Kundennummer
		 * @return Ambigous <number, neue Kundennummer>
		 */
		public function generiere_neu_kundennr(){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			//bestimmt die letzte Kundennr., die vergeben wurde
			$query = "
					select 
						KId
					from
						kunde
					order by KId desc
					limit 0,1; 
			";
			
			//die Datenbank-Abfrage ausführen
			$result = $db->db_query($query);
			
			$letzte_id = 0;
			while ($wert = $db->db_fetch_object($result)){
				$letzte_id = $wert->KId;
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			//gibt das die letzte Kundennummer mit 1 addiert aus
			$letzte_id++;
			return $letzte_id; 
		}
		
		/**
		 * sendet bei Neuanmeldung am System eine Aktivierung-Email an den Kunden
		 * @param integer $KId Kundennummer
		 * @return boolean Email wurde erfolgreich versendet?
		 */
		public function sende_aktivierungsemail_registrierung($KId){
			
			$erfolgreich = false;
			
			$mail = instanziere_email_objekt();
			
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			
			//Sonderzeichen entfernen
			$KId = $db->db_real_escape_string($KId);
			
			
			//bestimmt den Kundennamen
			$query = "
					select
						Name, Geschlecht, Email
					from
						kunde
					where
						KId = '$KId'
					;
			";
			
			//die Datenbank-Abfrage ausführen
			$result = $db->db_query($query);

			//Abfrage-Result entgegennehmen
			$kunde = "";
			while ($werte = $db->db_fetch_object($result)){
				$kunde = $werte;
			}
			
			//wenn der Kunde gefunden wurde
			if ($kunde != ""){
				//Serveradresse bestimmen
				$adresse_server = $_SERVER["SERVER_ADDR"];
					
				//Pfad zur Webseite bestimmen
				$pfad_zur_webseite = $_SERVER["PHP_SELF"];
				
				//bestimmt an Hand des Ports, ob die Webseite über http oder https betrieben wird
				$protokoll = ($_SERVER["SERVER_PORT"] == 80) ? "http" : "https";
				
				//Kundennummer verschlüsseln
				$encrypted = base64_encode($KId."---".$kunde->Name);
					
				//Aktivierungslink zusammenstellen
				$aktivierungslink = $protokoll."://".$pfad_zur_webseite."?account-activate=".urldecode($encrypted);

				//Anredesatz erstellen
				$anrede = ($kunde->Geschlecht == "weiblich") ? "Sehr geehrte Frau " : "Sehr geehrter Herr ";
				
				//Email-Nachricht verfassen
				$nachricht  = $anrede.$kunde->Name.",\r\n";
				$nachricht .= "vielen Dank für Ihre Registrierung beim Webshop der Global Bike Inc.\r\n";
				$nachricht .= "Bitte aktivieren Sie ihr Benutzerkonto durch folgenden Link:".$aktivierungslink." .\r\n \r\n";
				$nachricht .= "Mit freundlichen Grüßen\r\n";
				$nachricht .= "Ihr Webshop Team der Global Bike Inc.\r\n";
				
				//die Email versenden
				$erfolgreich =  $mail->senden($kunde->Email, "Bestätigungsemail: Abmeldung am Webshop der Global Bike Inc.", $nachricht);
			}
						
			//Datenbankverbindung schließen
			$db->db_close();
			
			return $erfolgreich;
		}
	};
?>