<?php
	class Suche{
		
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
						distinct p.Bezeichnung,
						b.Bezeichnung
					from
						produkte p 
							inner join bauart b on (b.BId = p.bauart)
							inner join produktkategorie pk on (pk.PTId = p.produktkategorie)
					where
						
			";
			
			$teilbedingung = "";
			
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
								document.getElementById('form_suche_normal_autovervollstaendigung_box').style.display='';\" >
							".htmlspecialchars($array_suchergebnis[$i],ENT_QUOTES,'UTF-8')."
						</div>
				";
			}
			
			return $ausgabe;
		}
	}
?>