<?php
class ArtikelDetails extends  Artikelauflistung{
	
	public function beschreibungAnzeigen($pid){
		$query = $this->anfangszeilenSQLQuery(); //Vordefinierten Kopf abspeichern
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
	
		$pid=$db->db_real_escape_string($pid); //Sonderzeichen aus $pid entfernen
	
		//Anfrage ergänzen
		$query = "select 
					 Beschreibung, `Verfuegbare Menge` as Menge, Preis, bauart.Bezeichnung as bauart, produkte.Bezeichnung as Bezeichnung
				from
					produkte
					left join bauart ON (produkte.bauart = bauart.BId)
				where pid = '$pid' ";
		$result = $db->db_query($query);
		
		$werte = "";
		
		while ($db_werte = $db->db_fetch_object($result)){
			$werte = $db_werte;
		}
		
		$db ->db_close();
		
		return $werte;
		
	}
	
	
	public function produktbildAnzeigen($pid){
		$query = $this->anfangszeilenSQLQuery(); //Vordefinierten Kopf abspeichern
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
	
		$pid=$db->db_real_escape_string($pid); //Sonderzeichen aus $pid entfernen
	
		//Anfrage ergänzen
		$query = "select
		Pfad
		from
		produktbilder
		where pid = '$pid' AND geloescht = 'nein' ANd Art = 'Produktbild'  ";
		$result = $db->db_query($query);
	
		$wert = "";
	
		while ($db_wert = $db->db_fetch_object($result)){
		$wert = $db_wert->Pfad;
	}
	
		$db ->db_close();
	
		return $wert;
	
	}
	
	
	public function DetailbilderAnzeigen($pid){
		$query = $this->anfangszeilenSQLQuery(); //Vordefinierten Kopf abspeichern
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
	
		$pid=$db->db_real_escape_string($pid); //Sonderzeichen aus $pid entfernen
	
		//Anfrage ergänzen
		$query = "select
		Pfad
		from
		produktbilder
		where pid = '$pid' AND geloescht = 'nein' ANd Art = 'Detail'  ";
		$result = $db->db_query($query);
	
		$werte = array();
		
		$i= 0;
	
		while ($db_werte = $db->db_fetch_object($result)){
			$werte[$i] = $db_werte->Pfad;
			$i ++;
		}
	
		$db ->db_close();
	
		return $werte;
	
	}
		
}
?>