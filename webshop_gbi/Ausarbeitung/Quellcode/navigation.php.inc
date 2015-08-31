<?php
//	Der Quellcode zeigt nur einen kleinen Ausschnitt aus der kompletten Klasse Navigation.
//	Der nachfolgende Quellcode wurde von Herrn Schnuerer geeriert.

// ...
// ...
// ...

//	Erzeugt das Drop-Down-Menü der Navigation
	public function FahrradbauartAuflisten($bauart ,$seitenzahl){
		$query = $this->anfangszeilenSQLQuery(); //Vordefinierten Kopf abspeichern
		//Verbindung zur Datenbank aufbauen
		$db = datenbank_verbindung_aufbauen();
		if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
		
		$bauart=$db->db_real_escape_string($bauart); //Sonderzeichen aus $bauart entfernen
		
		//Anfrage ergänzen
		$seite_sql = ($seitenzahl-1)*10;
		$query.= " AND b.BId ='$bauart' ORDER BY p.Bezeichnung asc limit $seite_sql, 10";
		
		$result = $db->db_query($query); //Abfrage ausführen
		
		$werte = array(); 
		$i = 0;
		
		//wird benötig um einzelne Elemente auf der Seite mit Namen anzusprechen
		while ($temp = $db->db_fetch_object($result)) {
			$werte[$i] = $temp;
			$i++;
		}
				
		$query= "select
					count(distinct p.Bezeichnung)
				from
					produkte p
					left join bauart b on (b.BId = p.bauart)
					left join produktkategorie pk on (pk.PTId = p.produktkategorie)
				where
					b.BId ='$bauart'";
		$result= $db->db_query($query);
		
		$gesammtseitenzahlen = 0;
		
		while ($temp = $db->db_fetch_array($result)) {
			$gesammtseitenzahlen = $temp[0];
		}
		$gesammtseitenzahlen = ceil($gesammtseitenzahlen/10); //Bestimmt wie viele Seiten benötigt werden, wenn jede Seite nur 10 Einträge enthält
		
		$this->erstelle_auflistung_aus_datenbank_reslut_array($werte, ($seitenzahl), $gesammtseitenzahlen);
		
		$db->db_close();
		
	}
}
?>