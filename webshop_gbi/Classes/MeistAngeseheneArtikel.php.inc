<?php
class MeistAngeseheneArtikel {
	 
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
	
	
	public function MeistAngeseheneArtikelAnzeigen () {
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
	
		//Anfrage ergänzen
		$query = "select 
					 Bezeichnung, Pfad, produkte.PId as PId
				from
					produkte
					left join produktbilder ON (produkte.PId = produktbilder.PId)
				where produktbilder.Art ='Liste' AND (`Artikel des Tages`!= 'ja' OR `Artikel des Tages` is NULL)
				order by `Menge Besuche` DESC
				limit 0,4";
		
		$result = $db->db_query($query);
		
		$werte = array();
		
		$i= 0;
		
		while ($db_werte = $db->db_fetch_object($result)){
			$werte[$i] = $db_werte;
			$i ++;
		}
		
		$db ->db_close();
		
		return $werte;
	}
}
?>