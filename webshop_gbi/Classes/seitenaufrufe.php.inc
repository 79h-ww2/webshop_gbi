<?php
class seitenaufrufe {
	 
	function __construct(){
		if (!isset($_SESSION["Seitenaufrufe"])){
				
			$_SESSION["Seitenaufrufe"] = array();
	 }
	}
	
	public function ArtikelSeiteSchonAufgerufen ($artikelnummer) {
		
		$arraySeitenaufrufe=$_SESSION["Seitenaufrufe"];
		
		$gefunden = false;
		
		for ($i=0; $i<count($arraySeitenaufrufe); $i++) {
			if ($arraySeitenaufrufe[$i] == $artikelnummer) {
				$gefunden = true;
			}
		}
		
		return $gefunden;
		
	}
	
	public function BesuchezaehlerErhoehen ($artikelnummer) {
		$arraySeitenaufrufe=$_SESSION["Seitenaufrufe"];
		$arraySeitenaufrufe[count($arraySeitenaufrufe)]=$artikelnummer;
		$_SESSION["Seitenaufrufe"] = $arraySeitenaufrufe;
		
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
		
		$artikelnummer=$db->db_real_escape_string($artikelnummer); //Sonderzeichen aus $bauart entfernen
		
		$query="update produkte set `Menge Besuche` = if(`Menge Besuche`is null,1, `Menge Besuche`+1) where PId = '$artikelnummer' ";
		
		//Ausführen der Abfrage
		$result = $db->db_query($query);
	}
}
?>