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
					Beschreibung
				from
					produkte
				where pid = '$pid' ";
		$result = $db->db_query($query);
		
		$beschreibung = "";
		
		while ($db_werte = $db->db_fetch_object($result)){
			$beschreibung = $db_werte->Beschreibung;
		}
		
		$db ->db_close();
		
		return $beschreibung;
		
	}
		
}
?>