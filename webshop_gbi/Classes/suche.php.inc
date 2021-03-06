<?php
	class Suche extends Artikelauflistung{
		
		/**
		 * Konstruktor
		 */
		function __construct(){
			
		}
		
		/**
		 * Sucht auf der Datenbank nach den Suchbegriff
		 * @param string $suchwort der Suchbegriff
		 * @return multitype:string eine Array mit den Suchergebnissen
		 */
		private function normale_suche_db_abfrage($suchwort){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			//Sonderzeichen aus den Suchbegriff entfernen
			$suchwort = $db->db_real_escape_string($suchwort);
			
			//Suchwort in einzelne wörter aufteilen
			$arr_suchwoerter = explode(" ", $suchwort);
			
			//Generierung der Suchabfrage
			$query = "
					select 
						p.Bezeichnung,
						b.Bezeichnung
					from
						produkte p 
							left join bauart b on (b.BId = p.bauart)
					where
						p.geloescht = 'nein'
						and 	
			";
			
			$teilbedingung = "";
			
			for ($i = 0; $i < count($arr_suchwoerter); $i++){
				
				if ($i > 0) $teilbedingung .=" and ";
				
				$teilbedingung .= "
					(
								b.Bezeichnung like '%".$arr_suchwoerter[$i]."%'
							or 
								p.Bezeichnung like '%".$arr_suchwoerter[$i]."%'
					)
				";
			}
			
			$query .= $teilbedingung." order by p.Beschreibung asc;";
			
			
			//die Suchabfrage durchführen
			$result = $db->db_query($query);
			
			//die Rückgabewerte entgegennehmen
			$werte = array();
			$j = 0;
			
			while($zeile = $db->db_fetch_array($result)){
				$werte[$j] = "";
				$werte[$j] .= $zeile[1];
				$werte[$j] .= ($werte[$j] == "") ? $zeile[0] : " ".$zeile[0];
				$j++;
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			//gibt das Array mit den Datenbankrückgabewerten aus
			
			return $werte;
		}
		
		
		/**
		 * sucht für die Autovervollständigung in der Datenbank nach möglichen Produkten und gibt sie für die Autovervollständigung passend aus
		 * @param string $suchwort der Suchbegriff
		 * @return string
		 */
		public function normale_suche_autovervollstaendigung ($suchwort){
			
			//erstellt ein Array mit den Suchergebnissen
			$array_suchergebnis = $this->normale_suche_db_abfrage($suchwort);
			
			$ausgabe = "";
			
			//Schreibt die Suchergebnisse in DIVs
			for ($i = 0; $i < count($array_suchergebnis); $i++){
				$ausgabe .= "
						<div class=\"zeile_suchergebnis_autovervollstaendigung_normale_suche\" onclick=\"
								document.getElementById('feld_suche_normal').value='".htmlspecialchars($array_suchergebnis[$i],ENT_QUOTES,'UTF-8')."';
								document.getElementById('form_suche_normal_autovervollstaendigung_box').style.display='';
								//document.forms['form_suche_normal'].submit();
						\" >
							".htmlspecialchars($array_suchergebnis[$i],ENT_QUOTES,'UTF-8')."
						</div>
				";
			}
			
			return $ausgabe;
		}
		
		
		/**
		 * sucht für die Autovervollständigung in der Datenbank nach möglichen Produkten und gibt sie für die Autovervollständigung passend aus
		 * @param string $suchwort der Suchbegriff
		 * @return string
		 */
		public function erweiterte_suche_autovervollstaendigung ($suchwort){
				
			//erstellt ein Array mit den Suchergebnissen
			$array_suchergebnis = $this->normale_suche_db_abfrage($suchwort);
				
			$ausgabe = "";
				
			//Schreibt die Suchergebnisse in DIVs
			for ($i = 0; $i < count($array_suchergebnis); $i++){
				$ausgabe .= "
						<div class=\"zeile_suchergebnis_autovervollstaendigung_normale_suche\" onclick=\"
								document.getElementById('suche_erweitert_produktbezeichnung').value='".htmlspecialchars($array_suchergebnis[$i],ENT_QUOTES,'UTF-8')."';
								document.getElementById('form_erweiterte_suche_autovervollstaendigung_box').style.display='';
						\" >
							".htmlspecialchars($array_suchergebnis[$i],ENT_QUOTES,'UTF-8')."
						</div>
				";
			}
				
			return $ausgabe;
		}
		
		/**
		 * führt die normale Suche durch und gibt das Suchergebnis aus
		 * @param unknown $suchwort das Suchwort
		 * @param unknown $seite die Seite, die angezeigt werden soll
		 */
		public function nomale_suche_mit_ergebnisauflistung ( $suchwort, $seite ){
			
			$werte = array();
			$seite -= 1;
			$seite_sql = $seite*10;
			$menge_seiten = 0;
			
			//wenn ein Suchwort eingegeben wurde
			if ( $suchwort != ""){
				//Verbindung zur Datenbank aufbauen
				$db = datenbank_verbindung_aufbauen();
				if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
					
				//Sonderzeichen aus den Suchbegriff entfernen
				$suchwort = $db->db_real_escape_string($suchwort);
					
				//Suchwort in einzelne wörter aufteilen
				$arr_suchwoerter = explode(" ", $suchwort);
				
					
				//Generierung der Suchabfrage
				
				$query = $this->anfangszeilenSQLQuery(); //ruft die Projektion des Sql-Query über eine Methode ab, somit muss die nicht bei jeden Suchselecvt neugeschrieben werden
				$teilbedingung = "";
				$teilbedingung_ = "";
				if ( count($arr_suchwoerter) > 0) $teilbedingung_ .= " and ";
					
					
				for ($i = 0; $i < count($arr_suchwoerter); $i++){
				
					if ($i > 0) $teilbedingung .=" and ";
				
					$teilbedingung .= "
						(
									b.Bezeichnung like '%".$arr_suchwoerter[$i]."%'
								or
									pk.Bezeichnung like '%".$arr_suchwoerter[$i]."%'
								or
									p.Bezeichnung like '%".$arr_suchwoerter[$i]."%'
						)
					";
				}
					
				$query .= $teilbedingung_.$teilbedingung." order by p.Beschreibung asc";
		
				$query_mit_seitennr = $query." limit $seite_sql, 10;";
								
				//die Suchabfrage durchführen
				$result = $db->db_query($query_mit_seitennr);
					
				//die Rückgabewerte entgegennehmen
				$werte = array();
				$j = 0;
					
				while($zeile = $db->db_fetch_object($result)){
					$werte[$j] = $zeile;
					$j++;
				}
				
				//Bestimmen, wie viele Seiten zum Suchbegriff gefunden werden
				$query = "
						select
							count(distinct p.Bezeichnung)
						from
							produkte p
								left join bauart b on (b.BId = p.bauart)
								left join produktkategorie pk on (pk.PTId = p.produktkategorie)
						where		
				".$teilbedingung;
				
				
				$result = $db->db_query($query);
				while ($werte_ = $db->db_fetch_array($result)){
					$menge_seiten = $werte_[0];
				}
		
				$menge_seiten = ceil($menge_seiten/10); //Bestimmt wie viele Seiten benötigt werden, wenn jede Seite nur 10 Einträge enthält
				
				//Datenbankverbindung schließen
				$db->db_close();
			}
			
			//Ergebnis auf der Webseite ausgeben
			$this->erstelle_auflistung_aus_datenbank_reslut_array($werte, ($seite +1), $menge_seiten);
				
		}
		
		/**
		 * Überprüft, ob die Eingabe bei der erweiterten Suche gültig ist 
		 * @param unknown $produktbezeichnung Wert des "Produktbeschreibungs"-Felds
		 * @param unknown $preis_von Wert des "Preis von"-Felds
		 * @param unknown $preis_bis Wert des "Preis bis"-Felds
		 * @param unknown $kategorie Wert des "Kategorie"-Dropdownmenü
		 * @param unknown $bauart Wert des "Bauart"-Dropdownmenü
		 * @param unknown $bauvariante Wert des "Bauvariante"-Dropdownmenü
		 * @param unknown $artikelnr Wert des "Atrikelnr"-Felds
		 * @param unknown $marke Wert des "Marke"-Felds
		 * @return Ueberpruefresult Prüferprüfungsrückgabe
		 */
		public function erweiterte_suche_eingabe_pruefen($produktbezeichnung,$preis_von, $preis_bis, $kategorie, $bauart, $bauvariante, $artikelnr, $marke){
			$meldung = "";
			
			//Objekt, über das der Funktionsrückgabewert übergeben werden soll
			$return = new Ueberpruefresult();
			
			//überprüft, ob mindestens ein Textfeld ausgefüllt sind
			if ($produktbezeichnung == "" && $preis_von == "" && $preis_bis == "" && $kategorie == "alle" && $bauart == "alle"  && $bauvariante == "alle" && $artikelnr == ""  && $marke =="" ){
				$meldung = "Bitte füllen Sie mindestens ein Feld aus.";
				$return->set_fehlermeldung($meldung);
			}
			//wenn eine bei der Preisspanne nur eine Textfeld ausgefüllt ist
			elseif ( $preis_von == "" && $preis_bis != "" || $preis_von != "" && $preis_bis == "" ){
				//gibt eine Fehlermeldung, aus das beide Felder ausgefüllt sein müssen
				
				$return->set_fehlermeldung("Bitte füllen Sie beide Textfelder bei der Preisspanne aus.");
				
				//überprüft, welche der Textfelder nicht ausgefüllt ist
				if ($preis_bis != ""){
					$return->set_feldstatus('preis_bis', true);
					$return->set_feldstatus('preis_von', false);
				}
				else{
					$return->set_feldstatus('preis_bis', false);
					$return->set_feldstatus('preis_von', true);
				}
			}
			//überprüft, ob es sich bei beiden Preisen um Zahlen handelt
			elseif ( $preis_von != "" && $preis_bis != "" ){
				
				$return->set_feldstatus('preis_bis', false);
				$return->set_feldstatus('preis_von', false);
				
				$sind_zahlen = true; //Variablen, die speichert, ob beide Textfelder zahlen enthalten
				
				//Deutsche Gleitkommazahl in Englisch Gleitpunktzahl umwandeln
				$p_von = str_replace(",", ".", $preis_von);
				$p_bis = str_replace(",", ".", $preis_bis);
				
				//wenn "Preis von" keine Zahl ist
				if ( is_numeric($p_von) == false  ){
					
					//Fehlermeldung festlegen
					$return->set_fehlermeldung("Bitte geben Sie bei der Preisspanne Zahlenwerte an.
					Die Zahlen müssen folgendermaßen formatiert sein: 1200,99 .");

					//Speichern, dass das Textfeld fehlerhaft ausgefüllt wurde
					$return->set_feldstatus('preis_von', true);
					$sind_zahlen = false;
				}
				
				//wenn "Preis bis" keine Zahl ist
				if ( is_numeric($p_bis) == false  ){

					//Fehlermeldung festlegen
					$return->set_fehlermeldung("Bitte geben Sie bei der Preisspanne Zahlenwerte an.
					Die Zahlen müssen folgendermaßen formatiert sein: 1200,99 .");
				
					//Speichern, dass das Textfeld fehlerhaft ausgefüllt wurde
					$return->set_feldstatus('preis_bis', true);
					$sind_zahlen = false;
				}
				
				//wenn beides Zahlen sind, wird überprüft, ob die "Preis_von" auch kleiner als die "Preis_bis" ist
				if ( $sind_zahlen && $preis_von > $preis_bis){
					//wenn nicht wird eine Fehlermeldung erstellt und die Textfelder als Fehlerhaft markiert
					$return->set_feldstatus('preis_bis', true);
					$return->set_feldstatus('preis_von', true);
					
					//Fehlermeldung festlegen
					$return->set_fehlermeldung('Der Mindestpreis muss kleiner als der Maximalpreis sein.' );
				}
			}
			
			//gibt das Prüfergebnis aus
			return $return;
			
		}
		
		/**
		 * führt die erweiterte Suche aus und gibt das Ergebnis aus
		 * @param unknown $produktbezeichnung Wert des "Produktbeschreibungs"-Felds
		 * @param unknown $preis_von Wert des "Preis von"-Felds
		 * @param unknown $preis_bis Wert des "Preis bis"-Felds
		 * @param unknown $kategorie Wert des "Kategorie"-Dropdownmenü
		 * @param unknown $bauart Wert des "Bauart"-Dropdownmenü
		 * @param unknown $bauvariante Wert des "Bauvariante"-Dropdownmenü
		 * @param unknown $artikelnr Wert des "Atrikelnr"-Felds
		 * @param unknown $marke Wert des "Marke"-Felds
		 * @param unknown $seite Die Seite, die angezeigt werden soll
		 */
		public function erweiterte_suche_mit_ergebnisauflistung ($produktbezeichnung,$preis_von, $preis_bis, $kategorie, $bauart, $bauvariante, $artikelnr, $marke, $seite){
			$seite -= 1;
			$seite_sql = $seite*10;
			
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			//Sonderzeichen entfernen
			$produktbezeichnung = $db->db_real_escape_string($produktbezeichnung);
			$preis_bis = $db->db_real_escape_string($preis_bis);
			$preis_von = $db->db_real_escape_string($preis_von);
			$kategorie = $db->db_real_escape_string($kategorie);
			$bauart = $db->db_real_escape_string($bauart);
			$bauvariante = $db->db_real_escape_string($bauvariante);
			$artikelnr = $db->db_real_escape_string($artikelnr);
			$marke = $db->db_real_escape_string($marke);
				
			//Suchwort in einzelne wörter aufteilen
			$arr_produktbezeichnung = explode(" ", $produktbezeichnung);
			
				
			//Generierung der Suchabfrage
			$query = $this->anfangszeilenSQLQuery()." and ";
			
			$teilbedingung = "";
			$teilbedingung_ = "";

			//sucht nach der Produktbezeichnung
			$ein_paar_bedingungen_schon_vorhanden = false;
			for ($i = 0; $i < count($arr_produktbezeichnung); $i++){
			
				if ($ein_paar_bedingungen_schon_vorhanden) $teilbedingung .=" and "; //Wenn schon Bedingungen im Where-Teil stehen wird wird der nächsten Bedingung ein "and" geschrieben
			
				$teilbedingung .= "
					(
								b.Bezeichnung like '%".$arr_produktbezeichnung[$i]."%'
							or
								pk.Bezeichnung like '%".$arr_produktbezeichnung[$i]."%'
							or
								p.Bezeichnung like '%".$arr_produktbezeichnung[$i]."%'
					)
				";
				$ein_paar_bedingungen_schon_vorhanden = true;
			}
			
			//wenn eine Preisspanne angegeben wurde, wird nach dieser gesucht
			if ( $preis_bis != "" && $preis_von != ""){
				if ($ein_paar_bedingungen_schon_vorhanden) $teilbedingung .=" and "; //Wenn schon Bedingungen im Where-Teil stehen wird wird der nächsten Bedingung ein "and" geschrieben
				
				$teilbedingung .= "Preis between '$preis_von' and '$preis_bis'";
				
				$ein_paar_bedingungen_schon_vorhanden = true;
			}
			
			//wenn eine Kategorie angegeben wurde, wird nach dieser gesucht
			if ($kategorie != "alle"){
				if ($ein_paar_bedingungen_schon_vorhanden) $teilbedingung .=" and "; //Wenn schon Bedingungen im Where-Teil stehen wird wird der nächsten Bedingung ein "and" geschrieben
				$teilbedingung .= "pk.Bezeichnung = '$kategorie'";
			}
			
			//wenn eine Bauart angegeben wurde, wird nach dieser gesucht
			if ($bauart != "alle"){
				if ($ein_paar_bedingungen_schon_vorhanden) $teilbedingung .=" and "; //Wenn schon Bedingungen im Where-Teil stehen wird wird der nächsten Bedingung ein "and" geschrieben
				$teilbedingung .= "b.Bezeichnung = '$bauart'";
			}
			
			//wenn eine Bauvariante angegeben wurde, wird nach dieser gesucht
			if ($bauvariante != "alle"){
				if ($ein_paar_bedingungen_schon_vorhanden) $teilbedingung .=" and "; //Wenn schon Bedingungen im Where-Teil stehen wird wird der nächsten Bedingung ein "and" geschrieben
				$teilbedingung .= "p.bauvariante = '$bauvariante'";
			}
			
			//wenn eine Bauvariante angegeben wurde, wird nach dieser gesucht
			if ($artikelnr != ""){
				if ($ein_paar_bedingungen_schon_vorhanden) $teilbedingung .=" and "; //Wenn schon Bedingungen im Where-Teil stehen wird wird der nächsten Bedingung ein "and" geschrieben
				$teilbedingung .= "p.PId = '$artikelnr'";
			}
			
			//wenn eine Bauvariante angegeben wurde, wird nach dieser gesucht
			if ($marke != ""){
				if ($ein_paar_bedingungen_schon_vorhanden) $teilbedingung .=" and "; //Wenn schon Bedingungen im Where-Teil stehen wird wird der nächsten Bedingung ein "and" geschrieben
				$teilbedingung .= "p.marke = '$marke'";
			}
				
			$query .= $teilbedingung_.$teilbedingung." order by p.Beschreibung asc";
			
			$query_mit_seitennr = $query." limit $seite_sql, 10;";
			
			//die Suchabfrage durchführen
			$result = $db->db_query($query_mit_seitennr);
			
				
			//die Rückgabewerte entgegennehmen
			$werte = array();
			$j = 0;
				
			while($zeile = $db->db_fetch_object($result)){
				$werte[$j] = $zeile;
				$j++;
			}
			
			
			//Bestimmen, wie viele Seiten zum Suchbegriff gefunden werden
			$query = "
						select
							count(distinct p.Bezeichnung)
						from
							produkte p
								left join bauart b on (b.BId = p.bauart)
								left join produktkategorie pk on (pk.PTId = p.produktkategorie)
						where
				".$teilbedingung;

			$result = $db->db_query($query);
			while ($werte_ = $db->db_fetch_array($result)){
				$menge_seiten = $werte_[0];
			}
			
			$menge_seiten = ceil($menge_seiten/10); //Bestimmt wie viele Seiten benötigt werden, wenn jede Seite nur 10 Einträge enthält
						
			
			//Datenbankverbindung schließen
			$db->db_close();

			//Ergebnis auf der Webseite ausgeben
			$this->erstelle_auflistung_aus_datenbank_reslut_array($werte, ($seite +1), $menge_seiten);
		}
	}
?>