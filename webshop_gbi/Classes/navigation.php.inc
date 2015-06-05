<?php
class Navigation extends  Artikelauflistung{
	
	/**
	 * erstellt eine Array mit den möglichen Kategorien
	 * @return multitype:String Kategorien, ID der Kategorie
	 */
	public function erstelle_array_kategorien(){
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
		
		//Die Datenbankabfrage
		$query = "select PTId, Bezeichnung from produktkategorie";
		
		//Ausführen der Abfrage
		$result = $db->db_query($query);
		
		$kategorien = array();
		$i = 0;
		while($werte = $db->db_fetch_object($result)){
			$kategorien[$i] = $werte;
			$i++;
		}
		
		//schließt die Datenbankverbindung
		$db->db_close();
		
		return  $kategorien;
	}
	
	/**
	 * erstellt eine Array mit den möglichen Kategorien
	 * @return multitype:String Kategorien, ID der Kategorie
	 */
	public function erstelle_array_bauart(){
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
	
		//Die Datenbankabfrage
		$query = "select BId, Bezeichnung from bauart";
	
		//Ausführen der Abfrage
		$result = $db->db_query($query);
	
		$bauarten = array();
		$i = 0;
		while($werte = $db->db_fetch_object($result)){
			$bauarten[$i] = $werte;
			$i++;
		}
	
		//schließt die Datenbankverbindung
		$db->db_close();
	
		return  $bauarten;
	}
}
?>