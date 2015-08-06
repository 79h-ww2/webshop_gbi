<?php 
	include_once "Classes/EingabeCheckGrundlegend.php.inc";
	include_once 'Classes/bestellungenslisteneintrag.php.inc';
	include_once 'Classes/Kunde.php.inc';
	include_once 'Classes/datenbank.php.inc';
	include_once 'Classes/warenkorb.php.inc';
	include_once 'Classes/warenkorbeintrag.php.inc';
	
	/**
	 * Diese Klasse dient dazu die Bestellungen zu verwalten
	 */
	class Bestellungen extends EingabeCheckGrundlegend{
		
		/**
		 * Konstruktor
		 */
		function __construct(){
			
			//erstellt eine Server-SESSION-Variable, um vorübergehend die Bestellungseinstellungen zu speichern
			if (!isset($_SESSION["bestellungenslisteneintrag"])){
				$_SESSION["bestellungenslisteneintrag"] = new Bestellungenslisteneintrag();
			}
		}
		
		/**
		 * Gibt die zwischengespeicherten Bestellungseinstellungen aus 
		 * @return Bestellungenslisteneintrag
		 */
		public function get_zwischengespeicherte_bestellungseinstellungen(){
			return $_SESSION["bestellungenslisteneintrag"];
		}
		
		/**
		 * Übergibt die Bestellungseinstellungen, die zwischengespeichert werden sollen
		 * @param Bestellungenslisteneintrag $bestellungseinstellungen Die Bestellungseinstellungen
		 */
		public function set_zwischengespeicherte_bestellungseinstellungen($bestellungseinstellungen){
			$_SESSION["bestellungenslisteneintrag"] = $bestellungseinstellungen;
		}
		
		/**
		 * Die Bestellung wird abgesendet
		 * @return boolean Gibt an, ob die Bestellung erfolgreich in der Datenbank gespeichert wurde
		 */
		public function zwischengespeicherter_bestellungslisteneintrag_bestellen(){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$kunde1 = new Kunden();
			
			//Sonderzeichen entfernen
			$kid = $db->db_real_escape_string($kunde1->get_kid_from_email($_SESSION['angemeldet']));
			$zahlungsart = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_zahlungsart());
			$versandart = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_versandart());
			$iban = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_iban());
			$bic = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_bic());
			$kinhaber = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_kontoinhaber());
			$lgeschlecht = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_geschlecht());
			$lvorname = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_vorname());
			$lname = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_name());
			$lstrasse = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_strasse());
			$lhausnummer = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_hausnr());
			$lplz = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_plz());
			$lort = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_ort());
			
			$query = "
					insert into bestellung
					(
						KId,
						Status,
						Datum,
						Zahlungsart,
						stand,
						versandart,
						geloescht,
						bankeinzug_iban,
						bankeinzug_bic,
						bankeinzug_kontoinhaber,
						lieferadresse_geschlecht,
						lieferadresse_vorname,
						lieferadresse_name,
						lieferadresse_strasse,
						lieferadresse_hausnummer,
						lieferadresse_plz,
						lieferadresse_ort
					)
					values
					(
						'$kid',
						'Auftrag erhalten',
						now(),
						'$zahlungsart',
						now(),
						'$versandart',
						'nein',
						'$iban',
						'$bic',
						'$kinhaber',
						'$lgeschlecht',
						'$lvorname',
						'$lname',
						'$lstrasse',
						'$lhausnummer',
						'$lplz',
						'$lort'
					);
			";
			
			$result = $db->db_query($query);
						
			//Datenbankverbindung schließen
			$db->db_close();
			
			$erfolgreich = ( !$result ) ? false : true;
			
			//Wenn die Bestellung erfolgreich erstellt wurde, wird die Bestellungsnummer ermittelt und der Warenkorb zur Bestellung hinzugefügt
			if ($erfolgreich){
				//Bestellungsnummer ermitteln
				$bestId = $this->bestimme_bestellunger_letzte_bestellung_kunde($kid);
				
				//Warenkorbprodukte zur Bestellung hinzufügen
				$erfolgreich = $this->warenkorb_produkte_in_bestellung_einfuegen($bestId);
			}
			
			return $erfolgreich;
		}
		
		/**
		 * Gibt die letzte Bestellungsnummer eines Kundens aus
		 * @param integer $kundennr Die Kundennummer des Kundens
		 * @return Ambigous <string, int> Die Bestellnummer
		 */
		public function bestimme_bestellunger_letzte_bestellung_kunde($kundennr){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$kundennr = $db->db_real_escape_string($kundennr);
			
			$query = "select BestId from bestellung where KId='$kundennr' order by BestId desc limit 0,1;";
			
			$result = $db->db_query($query);
			
			$bid = "";
			while($werte = $db->db_fetch_array($result)){
				$bid = $werte[0];
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			return $bid;
		}
		
		
		/**
		 * Fügt die Produkt aus dem Warenkorb zur Bestellung hinzu
		 * @param unknown $bestellnummer Nummer der Bestellung
		 * @return boolean
		 */
		public function warenkorb_produkte_in_bestellung_einfuegen($bestellnummer){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$bestellnummer = $db->db_real_escape_string($bestellnummer);
			
			$warenkorb1 = new warenkorb();
			$Artikel = $warenkorb1->artikel_im_warenkorb_anzeigen();
			
			$query = "insert into bestellprodukte (BestId, PId, Menge) values ";
			
			//fügt jeden Eintrag im Warenkorb zum Insert-Befehl hinzu
			for ($i = 0; $i < count($Artikel); $i++){
				if ( $i > 0) $query.",";
				$eintrag = $Artikel[$i];
				$menge = $db->db_real_escape_string($eintrag->get_menge());
				$artikelnummer = $db->db_real_escape_string($eintrag->get_artikelnummer());
				$query.="('$bestellnummer', '$artikelnummer', '$menge')";
			}
			
			$result = false;
			
			//wenn Artikel im Warenkorb vorhanden sind, wird der Insert-Befehl ausgeführt
			if (count($Artikel) > 0){
				$result = $db->db_query($query);
			}
			
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			return (!$result) ? false : true;
		}
	}
?>