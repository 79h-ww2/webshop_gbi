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
}

?>