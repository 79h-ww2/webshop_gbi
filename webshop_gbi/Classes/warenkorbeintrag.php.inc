<?php 

class warenkorbeintrag{
	private $artikelnummer;
	private $menge;
	
	function __construct($menge, $artikelnummer){
		$this->artikelnummer = $artikelnummer;
		$this->menge = $menge;
		}
		public function get_artikelnummer(){
			return $this->artikelnummer;
		}
		public function get_menge(){
			return $this->menge;
		}
		public function set_menge($menge){
			 $this->menge = $menge;
					}
		public function get_artikelnamen(){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			$PId = $db->db_real_escape_string($this->artikelnummer);
			//Die Datenbankabfrage
			$query = "select Bezeichnung from produkte where PId ='$PId' ";
		
			//Ausführen der Abfrage
			$result = $db->db_query($query);
		
			$bezeichnung =""; 
			while($werte = $db->db_fetch_object($result)){
				$bezeichnung = $werte->Bezeichnung;
							}
		
			//schließt die Datenbankverbindung
			$db->db_close();
		
			return  $bezeichnung;
		}
		public function get_artikelbild(){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			$PId = $db->db_real_escape_string($this->artikelnummer);
			//Die Datenbankabfrage
			$query = "select Pfad from produktbilder where PID ='$PId' and Art ='Liste'";
		
			//Ausführen der Abfrage
			$result = $db->db_query($query);
		
			$pfad ="";
			while($werte = $db->db_fetch_object($result)){
				$pfad = $werte->Pfad;
			}
		
			//schließt die Datenbankverbindung
			$db->db_close();
		
			return  $pfad;
		}
		
		/**
		 * Gibt den Einzelpreis des Artikels aus
		 * @return float Der Einzelpreis
		 */
		public function get_einzelpreis_artikel(){
			
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			$PId = $db->db_real_escape_string($this->artikelnummer);
			//Die Datenbankabfrage
			$query = "select Preis from produkte where PId ='$PId' ";
			
			//Ausführen der Abfrage
			$result = $db->db_query($query);
			
			$preis =0;
			while($werte = $db->db_fetch_object($result)){
				$preis = $werte->Preis;
			}
			
			//schließt die Datenbankverbindung
			$db->db_close();
			
			return $preis;
		}
		
		/**
		 * Gibt den Gesamtpreis aus, der sich nach der Angabe der Menge ergibt 
		 * @return float der Gesamtpreis
		 */
		public function get_gesamtpreis_artikel(){
			return $this->menge * $this->get_einzelpreis_artikel();
		}
}

?>