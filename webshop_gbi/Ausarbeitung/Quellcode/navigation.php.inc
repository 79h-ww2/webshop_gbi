<?php
// ...
//	Erzeugt das Drop-Down-Menü der Navigation
public function FahrradbauartAuflisten($bauart ,$seitenzahl){
 
  //Verbindung zur Datenbank aufbauen
 $db = datenbank_verbindung_aufbauen();
 if ( !($db->db_connect()) ) 
	die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");

 //Sonderzeichen aus $bauart entfernen
 $bauart=$db->db_real_escape_string($bauart);

 //Vordefinierten Abfrage-Kopf laden
 $query = $this->anfangszeilenSQLQuery();

 //Abfrage ergänzen
 $query.= 
  " AND b.BId ='$bauart' ORDER BY p.Bezeichnung asc limit $seite_sql, 10";

 $result = $db->db_query($query); //Abfrage ausführen
 $werte = array(); 
 $i = 0;
 
 //Nimmt die Rückgabewerte der Abfrage entgegen und
 //legt diese in einen Array ab
 while ($temp = $db->db_fetch_object($result)) {
  $werte[$i] = $temp;
  $i++;
 }
 //...
 //Artikel werden aufgelistet
 $this->erstelle_auflistung_aus_datenbank_reslut_array($werte, ($seitenzahl), $gesammtseitenzahlen);
 $db->db_close(); //Verbindung zur Datenbank schließen
}
?>
