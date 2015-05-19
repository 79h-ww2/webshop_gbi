<?php
	include_once './Classes/Ueberpruefresult.php.inc';
	include_once './Classes/Email.php.inc';
	include_once './Classes/EingabeCheckGrundlegend.php.inc';

	class Kunden extends EingabeCheckGrundlegend{
		
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
		public function ueberpruefeEingabeReg ($vorname, $name, $strasse, $plz, $hausnr, $ort, $email, $passwort, $wpasswort){
			
			//Objekt, über das der Funktionsrückgabewert übergeben werden soll
			//$return = new Ueberpruefresult();
						
			//Array mit allen Feldern, die ausgefüllt sein müssen
			$felder = array($vorname, $name, $strasse, $hausnr, $plz, $ort, $email, $passwort, $wpasswort);
			$feldnamen = array('vorname', 'name', 'strasse', 'hausnr', 'plz', 'ort', 'email', 'passwort', 'wpasswort');
			
			//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
			$meldungswort = array('ihren Vornamen', 'ihren Namen', 'ihre Straße', 'ihre Hausnummer', 'ihr Postleitzahl', 'ihr Ort', 'ihre Email-Adresse', 'ein Passwort', 'die Passwort-Wiederholung');
			
			//Variable, wo die Fehlermeldung zwischengespeichert wird
			$fehlermeldung = "";
			
			//überprüft, ob alle Inputfelder ausgefüllt sind und erstellt wenn nicht eine Fehlermeldung
			$return = $this->erstelle_meldung_nicht_alle_felder_ausgefuellt($feldnamen, $meldungswort, $felder);
			$fehlermeldung = $return->get_fehlermeldung();
			
			//wenn alle Felder ausgefüllt sind, wird überprüft, ob die Eingaben gültig sind
			if ($fehlermeldung == "") {
				//überprüft, ob die PLZ gültig ist
				if ( strlen($plz) != 5 ||  is_numeric($plz) == false ){
					$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
					$fehlermeldung .= "Die Postleitzahl ist ungültig. Bitte geben Sie eine gültige Postleitzahl ein.";
					$return->set_feldstatus('plz', true);
				}
				
				//überprüft, ob die Passwörter übereinstimmen
				if ( $passwort != $wpasswort ){
					$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
					$fehlermeldung += "Die Passwörter stimmen nicht überein.";
					$return->set_feldstatus('wpasswort', true);
					$return->set_feldstatus('passwort', true);
				}
				
				//überprüft, die Email-Adresse
				if (filter_var($email, FILTER_VALIDATE_EMAIL) == false){
					$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
					$fehlermeldung .= "Die Email-Adresse ist ungültig.";
					$return->set_feldstatus('email', true);
				}
				//überprüft, ob die Email-Adresse nicht schon im System gespeichert ist
				elseif ($this->email_in_db_vorhanden($email)){
					$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
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
					Geschlecht,
					aktiviert
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
					'$geschlecht',
					'nein'
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
				$adresse_server = $_SERVER["SERVER_NAME"];
					
				//Pfad zur Webseite bestimmen
				$pfad_zur_webseite = $_SERVER["PHP_SELF"];
				
				//bestimmt an Hand des Ports, ob die Webseite über http oder https betrieben wird
				$protokoll = ($_SERVER["SERVER_PORT"] == 80) ? "http" : "https";
				
				//Kundennummer verschlüsseln
				$encrypted = base64_encode($KId."---".$kunde->Name."---".time());
					
				//Aktivierungslink zusammenstellen
				$aktivierungslink = $protokoll."://".$adresse_server.$pfad_zur_webseite."?account-activate=".urldecode($encrypted);

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
		
		/**
		 * aktiviert den neu registrierten Kunden
		 * @param string $aktivierungscode der Aktivierungscode
		 * @return boolean gibt, aus, ob die Aktivierung erfolgreich war
		 */
		public function aktiviere_kunde_durch_aktivierungs_code ($aktivierungscode){
			
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			//Entschlüsselt den Deaktivierungscode
			$code_elemente_unverschluesselt = explode("---", base64_decode($aktivierungscode));
			
			
			//Sonderzeichen entfernen
			$KId = $db->db_real_escape_string($code_elemente_unverschluesselt[0]);
			$Name = $db->db_real_escape_string($code_elemente_unverschluesselt[1]);
			
			//DB-Abfrage erstellen
			$query = "
				update
					kunde
				set 
					aktiviert='ja'
				where
						KId = '$KId'
					and
						Name = '$Name'
					and
						(aktiviert is null or aktiviert = 'nein')
				;
			";
			
			//Die DB-Abfrage ausführen
			$result = $db->db_query($query);
						
			//Datenbankverbindung schließen
			$db->db_close();
			
			//den Kunden anmelden
			$_SESSION['angemeldet'] = $this->get_email_from_kid($KId); 
			
			return (!$result) ? false : true;
		}
		
		/**
		 * bestimmt die Email-Adresse des Kunden
		 * @param String $kid Kundennr
		 * @return String Email-Adresse
		 */
		public function get_email_from_kid($kid){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$kid = $db->db_real_escape_string($kid);
			
			$query = "select Email from kunde where KId ='$kid'";
			$result = $db->db_query($query);
			
			$email = "";
			while ( $wert = $db->db_fetch_array($result)){
				$email = $wert[0];
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			return $email;
		}
		
		/**
		 * Überprüft die eingegebenen Daten, die in das Anmeldeformular eingegeben wurden
		 * @param unknown $email Eingabe: Email-Adresse
		 * @param unknown $passwort Eingabe: Passwort
		 * @return Ambigous <string, Ueberpruefresult>
		 */
		public function ueberpruefeEingabeAnmeldung ($email, $passwort){
			//Array mit allen Feldern, die ausgefüllt sein müssen
			$felder = array($email, $passwort);
			$feldnamen = array('anmedlung_email', 'anmedlung_passwort');
				
			//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
			$meldungswort = array('ihre Email-Adresse', 'ein Passwort');
			
			$fehlermeldung = "";
			
			//überprüft, ob alle Inputfelder ausgefüllt sind und erstellt wenn nicht eine Fehlermeldung
			$return = $this->erstelle_meldung_nicht_alle_felder_ausgefuellt($feldnamen, $meldungswort, $felder);
			$fehlermeldung = $return->get_fehlermeldung();
			
			//überprüft, ob die Email-Adresse gültig ist
			if ($fehlermeldung == "" && filter_var($email, FILTER_VALIDATE_EMAIL) == false){
				$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
				$fehlermeldung .= "Die Email-Adresse ist ungültig.";
				$return->set_feldstatus('anmedlung_email', true);
			}
			$return->set_fehlermeldung($fehlermeldung);
			
			//überprüft, ob die Login-Daten richtig sind (solange vorher nicht schon ein Fehler aufgetreten ist)
			
			if ($fehlermeldung == ""){
				//Verbindung zur Datenbank aufbauen
				$db = datenbank_verbindung_aufbauen();
				if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
				
				$email = $db->db_real_escape_string($email);
				$passwort_hash = md5($passwort);
				
				$query = "
					select 
						count(*) 
					from 
						kunde 
					where 
							Email = '$email'
						and
							Passwort = '$passwort_hash'
						and
							aktiviert = 'ja'
					;";
				
				$result = $db->db_query($query);
				
				$wert = 0;
				while ($werte = $db->db_fetch_array($result) ){
					$wert = $werte[0];
				}
				
				//Datenbankverbindung schließen
				$db->db_close();
				
				//wenn kein Eintrag zu den Login-Daten in der Datenbank gefunden wurde wird eine Fehlermeldung erstellt
				if ($wert < 1){
					$return->set_feldstatus('anmedlung_email', true);
					$return->set_feldstatus('anmedlung_passwort', true);
					$return->set_fehlermeldung("Die Anmeldung ist fehlgeschlagen. Bitte überprüfen Sie nochmal ihre Anmeldedaten.");
				}
			}
			
			return $return; 
		}
	};
?>