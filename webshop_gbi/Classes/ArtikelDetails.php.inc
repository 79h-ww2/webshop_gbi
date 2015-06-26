<?php
class ArtikelDetails extends  Artikelauflistung{
	
	public function beschreibungAnzeigen($pid){
		$query = $this->anfangszeilenSQLQuery(); //Vordefinierten Kopf abspeichern
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
	
		$pid=$db->db_real_escape_string($pid); //Sonderzeichen aus $bauart entfernen
	
		//Anfrage ergänzen
		$query = "select 
					Bezeichnung, Beschreibung, `Verfuegbare Menge` as Menge
				from
					produkte
				where pid = '$pid' ";
		$result = $db->db_query($query);
		
		$werte = "";
		
		while ($db_werte = $db->db_fetch_object($result)){
			$werte = $db_werte;
		}
		
		$db ->db_close();
		
		return $werte;
		
	}
		
}
?>