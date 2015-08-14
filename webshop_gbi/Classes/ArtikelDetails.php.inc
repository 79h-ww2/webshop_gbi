<?php
include_once 'Classes/bewertung.php.inc';
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
	
	
	
	public function EigenschaftenAnzeigen($pid){
		$query = $this->anfangszeilenSQLQuery(); //Vordefinierten Kopf abspeichern
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
	
		$pid=$db->db_real_escape_string($pid); //Sonderzeichen aus $pid entfernen
	
		//Anfrage ergänzen
		$query = "select
		Eigenschaften
		from
		produkte
		where pid = '$pid'";
		$result = $db->db_query($query);
	
		$werte = array();
	
		$i= 0;
	
		while ($db_werte = $db->db_fetch_array($result)){
			$eigenschaften = $db_werte[0];
			$werte = explode (";",$eigenschaften);
		}
	
		$db ->db_close();
	
		return $werte;
	
	}
	
	/**
	 * zeigt die Bewertung des Artikels an
	 * @param unknown $pid Die Artikelnummer
	 */
	public function bewertungZeigen($pid){
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
		
		$pid = $db->db_real_escape_string($pid);
		$query = "
				select 
					sterne1, sterne2, sterne3, sterne4,sterne5
				from 
					produkte p
						left join ( select count(*) sterne1, PId from kommentare where bewertung = '1' and geloescht = 'nein' group by PId ) s1 using (PId)
						left join ( select count(*) sterne2, PId from kommentare where bewertung = '2' and geloescht = 'nein' group by PId ) s2 using (PId)
						left join ( select count(*) sterne3, PId from kommentare where bewertung = '3' and geloescht = 'nein' group by PId ) s3 using (PId)
						left join ( select count(*) sterne4, PId from kommentare where bewertung = '4' and geloescht = 'nein' group by PId ) s4 using (PId)
						left join ( select count(*) sterne5, PId from kommentare where bewertung = '5' and geloescht = 'nein' group by PId ) s5 using (PId)
				where
					p.PId = '$pid'";
		
		$result = $db->db_query($query);
		
		$arr_sterne = array();
		
		while ($werte = $db->db_fetch_array($result)){
			$arr_sterne = $werte;
		} 
				
		//Datenbankverbindung schließen
		$db->db_close();

		$bewertung1 = new Bewertung($arr_sterne);
		$bewertung1->zeige_sterne();
		
		//Popup mit der detailierten Auswertung der Bewertung wird eingefügt
		include './Pages/popupBewertungProduktauflistung.php.inc';
	}
}
?>