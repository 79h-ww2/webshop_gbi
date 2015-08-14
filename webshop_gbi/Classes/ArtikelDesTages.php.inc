<?php

class ArtikelDesTages extends ArtikelDetails {
	
	public function ArtikelDesTagesPIdSuchen(){
		
		$query = $this->anfangszeilenSQLQuery(); //Vordefinierten Kopf abspeichern
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
		
		
		//Anfrage ergänzen
		$query = "select PId
		from
		produkte
		where `Artikel des Tages` = 'ja' ";
		$result = $db->db_query($query);
		
		$werte = "";
		
		while ($db_werte = $db->db_fetch_object($result)){
		$werte = $db_werte->PId;
		}
		
		$db ->db_close();
		
		return $werte;
	}
}



?>