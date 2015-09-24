<?php
	if ( file_exists ( './Classes/bewertung.php.inc' )) include_once './Classes/bewertung.php.inc';

	class Artikelauflistung{

		/**
		 * Erstellt eine Artikelauflistung aus den Übergebenen Array, welches Werte einer Datenbankabfrage enthält
		 * Array-Feldbezeichnungen: bezeichnung, exemplare, kategorie, preis, preis_alt, sterne1, sterne2, sterne3, sterne4, sterne5, bild, PId
		 * @param String[] $array_query_result_db Array mit den Abfrageergebniss
		 */
		public function erstelle_auflistung_aus_datenbank_reslut_array($array_query_result_db, $seitennr, $seitenInsgesammt ){
			
			//wenn kein Produkt gefunden wurde, wird eine Meldung ausgegeben
			if ( count($array_query_result_db) == 0) {
				echo '<br/>Kein Ergebnis gefunden.';
			}
			//wenn Produkte gefunden wurden
			else{
				//Kopfzeile der Auflistung erstellen
				$this->schreibe_kopf_auslistung();
				
				//Produkte auflisten
				for($i = 0; $i < count($array_query_result_db); $i++ ){
					
					//Produkt aus dem Array auslesen
					$produkt = $array_query_result_db[$i];
					
					//Sterne in einen Array zwischenspeichern
					$arr_sterne = array();
					$arr_sterne[0] = $produkt->sterne1;
					$arr_sterne[1] = $produkt->sterne2;
					$arr_sterne[2] = $produkt->sterne3;
					$arr_sterne[3] = $produkt->sterne4;
					$arr_sterne[4] = $produkt->sterne5;
					
					//Produkt zur Liste hinzufügen
					$this->produkt_zur_liste_hinzufuegen($produkt->bezeichnung, $produkt->exemplare, $produkt->kategorie, $produkt->preis, $produkt->preis_alt, $arr_sterne, $produkt->bild, $produkt->PId );
				}
				
				$this->schreibe_fuss_auflistung();
				
				$this->seitennummerwahl_hinzufuegen($seitennr, $seitenInsgesammt);
			}
			
		}
		
		/**
		 * schreibt die Kopfzeile der Auflistung
		 */
		public function schreibe_kopf_auslistung(){
			echo '<div class="auflistung_produkte" >';
		}
		
		
		/**
		 * erstellt die Fußangaben für die Auflistung
		 */
		public function  schreibe_fuss_auflistung(){
			echo '</div>';
		}
		
		/**
		 * fügt eine Produkt zur Produktliste hinzu
		 * @param unknown $bezeichnung Produktbezeichnung
		 * @param unknown $verfuegbare_examplare verfügbare Examplare
		 * @param unknown $kategorie Kategorie des Produkts
		 * @param unknown $preis Preis des Produkts
		 * @param unknown $preis_alt alter Preis des Produkts
		 * @param unknown $arr_sterne Bewertung des Produkts
		 * @param unknown $bild Pfad zum Produktbild
		 * @param unknown $pid Produkt-ID
		 */
		public function produkt_zur_liste_hinzufuegen($bezeichnung, $verfuegbare_examplare, $kategorie, $preis, $preis_alt, $arr_sterne, $bild, $pid){
?>
			<div class="listeneintrag_auflistung_produkte" title="<?php echo htmlspecialchars($bezeichnung,ENT_QUOTES,'UTF-8') ?>" >
				<div class="listeneintrag_auflistung_produkte_content" >
					<div class="listeneintrag_auflistung_produkte_bild" >
						<a class="listeneintrag_auflistung_produkte_beschriftungstext" href="./?page=produkt&pid=<?php echo htmlspecialchars($pid,ENT_QUOTES,'UTF-8') ?>" >
							<img src="<?php echo $bild; ?>" />
						</a>
					</div>
					<div class="listeneintrag_auflistung_produkte_beschriftung"  >
							<div>
								<a class="listeneintrag_auflistung_produkte_beschriftungstext" href="./?page=produkt&pid=<?php echo htmlspecialchars($pid,ENT_QUOTES,'UTF-8') ?>" >
									<?php echo htmlspecialchars($bezeichnung,ENT_QUOTES,'UTF-8') ?>
								</a>
							</div>
							<div class="listeneintrag_bewertung" >														
								<?php
								
									//fügt die Bewertungssterne zum Eintrag hinzu
									$sterne = new Bewertung($arr_sterne);
									$sterne->zeige_sterne();
								
									//Popup mit der detailierten Auswertung der Bewertung wird eingefügt
									include './Pages/popupBewertungProduktauflistung.php.inc'; 
								?>
							</div>
							<?php 
								if ($verfuegbare_examplare > 0){
									echo '<div class="menge_exemplare_gruen" >'.htmlspecialchars($verfuegbare_examplare,ENT_QUOTES,'UTF-8').' Exemplare verfügbar</div>';
								}
								else{
									echo '<div class="menge_exemplare_rot" >Ausverkauft</div>';
								}
							?>
							<div class="listeneintrag_auflistung_kategorie" >
								Kategorie: <?php echo htmlspecialchars($kategorie,ENT_QUOTES,'UTF-8') ?>
							</div>
							<div class="listeneintrag_auflistung_preis">
								<?php if ($preis != "" ) echo htmlspecialchars($preis,ENT_QUOTES,'UTF-8')."&euro;"; ?>
								<span class="listeneintrag_auflistung_preis_alt" >
									<?php if ($preis_alt != "" ) echo htmlspecialchars($preis_alt,ENT_QUOTES,'UTF-8')."&euro;"; ?>
								</span>
							</div>
							<div class="clear_right" >
							</div>
					</div>
				</div>
			</div>
<?php
			
		}
		
		/**
		 * erstellt die Seitennummerwahlnavigationsleiste
		 * @param unknown $aktuelleSeite Aktuell aufgerufene Seite
		 * @param unknown $SeitenInsgesamt Seiten insgesammt
		 */
		public function seitennummerwahl_hinzufuegen($aktuelleSeite, $SeitenInsgesamt){
			
			//die Adresse für den Link zusammenstellen
			$adresse = "./";
			$get_feldnamen = array_keys($_GET);
			$k = 0;
			for ( $i = 0; $i < count($_GET); $i++)
			{
				if ( $get_feldnamen[$i] != 'seite'){
					$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
					$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
					$adresse .= ($k == 0) ? "?".$feldname."=".$wert : "&".$feldname."=".$wert;
					$k++;
				}
			}
			
			
			//baut die Nummererierten Links auf
			$nummerierung = "";
			$von_als_link = ' von '.$this->baue_seiten_link_seiten_nummer($SeitenInsgesamt, $adresse);
			$span_von = ' von <span>'.htmlspecialchars($SeitenInsgesamt,ENT_QUOTES,'UTF-8').'</span>';
			$span_aktuell = '<span  id="akutelleSeite" >'.htmlspecialchars ($aktuelleSeite,ENT_QUOTES,'ISO8859-1').'</span>';
			
			//Variablen, die festlegen, welches Weiter- und Zurücksymbole angezeigt werden soll, ob ausgeblendet oder nicht
			$id_zuruecklink = "";
			$id_weiterlink = "";
			
			if ( $aktuelleSeite <  $SeitenInsgesamt){
				$nummerierung = $span_aktuell;
				$nummerierung .= ', '.$this->baue_seiten_link_seiten_nummer($aktuelleSeite+1, $adresse);
				if ( ($aktuelleSeite + 1) <  $SeitenInsgesamt ){
					$nummerierung .= ', '.$this->baue_seiten_link_seiten_nummer($aktuelleSeite+2, $adresse);
				}
				if ( ($aktuelleSeite + 2) <  $SeitenInsgesamt ){
					$nummerierung .= ', ...';
				}
				$nummerierung .= $von_als_link;
				
				if ( $aktuelleSeite == 1){
					$id_zuruecklink ="seite_zurueck_grau";
				}else{
					$id_zuruecklink ="seite_zurueck";
				}
				$id_weiterlink = "seite_weiter";
				
			}elseif ($aktuelleSeite == 1){
				$nummerierung = $span_aktuell.$span_von;
				$id_zuruecklink ="seite_zurueck_grau";
				$id_weiterlink = "seite_weiter_grau";
			}else{
				if ( ($aktuelleSeite - 2) >  1 ) $nummerierung .= '..., ';
				if ( ($aktuelleSeite - 1) >  1 ) $nummerierung .= $this->baue_seiten_link_seiten_nummer($aktuelleSeite-2, $adresse).", ";
				$nummerierung .= $this->baue_seiten_link_seiten_nummer($aktuelleSeite-1, $adresse);
				$nummerierung .= ', '.$span_aktuell.$span_von;
				$id_zuruecklink ="seite_zurueck";
				$id_weiterlink = "seite_weiter_grau";
			}
			
			//erstellt den Zurücklink
			$link_zurueck = "";
			if ( $id_zuruecklink ==  'seite_zurueck_grau'){ //Deaktivierter Zurücklink
				$link_zurueck = '
					<span title="Seite zur&uuml;ck"  class="seite_vor_zurueck_link" id="seite_zurueck_grau" >
						Seite zur&uuml;ck
					</span>
				';
			}else{ //aktivierter Zurücklink
				$link_zurueck = '
					<a title="Seite zur&uuml;ck"  class="seite_vor_zurueck_link" id="seite_zurueck"  href="'.$adresse.'&seite='.($aktuelleSeite-1).'">
						Seite zur&uuml;ck
					</a>
				';
			}
			
			//erstelle Weiter-Link
			$link_weiter = "";
			if ( $id_weiterlink ==  'seite_weiter_grau'){ //Deaktivierter Weiterlink
				$link_weiter = '
					<span title="N&auml;chste Seite"  class="seite_vor_zurueck_link" id="seite_weiter_grau" >
						N&auml;chste Seite
					</span>
				';
			}else{ //aktivierter Weiterlink
				$link_weiter = '
					<a title="N&auml;chste Seite"  class="seite_vor_zurueck_link" id="seite_weiter"  href="'.$adresse.'&seite='.($aktuelleSeite+1).'">
						N&auml;chste Seite
					</a>
				';
			}
			
			
			//erstellt den HTML-Code für die Navigation der Seitenzahlen
			echo'
		 		<div class="box_seitennavigation_ergebnis_seiten" >
					'.$link_zurueck.'
					<span class="seiten_nummern" >
						'.$nummerierung.'
					</span>
					'.$link_weiter.'
				</div>
	 		';
		}
		
		/**
		 * erstellt einen Link für die Seitenwahlleiste am unteren Rand
		 * @param unknown $seitennr Seitennummer des Links
		 * @param unknown $adresse Adresse worauf der Link zeigen soll
		 * @return string Die erstellte Adresse
		 */
		public function baue_seiten_link_seiten_nummer($seitennr, $adresse){
			return '<a href="'.$adresse.'&seite='.htmlspecialchars ($seitennr ,ENT_QUOTES,'ISO8859-1').'" title="Seite '.htmlspecialchars ($seitennr ,ENT_QUOTES,'ISO8859-1').'" >'.htmlspecialchars ($seitennr ,ENT_QUOTES,'ISO8859-1').'</a>';
		}
		
		
		/**
		 * gibt die Anfangszeilen für den SQL-Query zurück, der die Felder für die Auflistung definiert
		 * @return string ersten Zeilen des Query's
		 */
		protected function anfangszeilenSQLQuery(){
			
			//ließt die für die Auflistung benötigten Felder aus und bestimmt wie oft das Produkt welche Sterne bekommen hat durch zählen, wie oft welche Bewertungsziffer für das Produkt angegeben wurde
			$query = "
						select
							distinct p.Bezeichnung bezeichnung,
							b.Bezeichnung kategorie,
							`Verfuegbare Menge` exemplare,
							Preis preis,
							preis_alt,
							sterne1,
							sterne2,
							sterne3,
							sterne4,
							sterne5,
							p.PId,
							pb.Pfad bild
						from
							produkte p
								left join bauart b on (b.BId = p.bauart)
								left join produktkategorie pk on (pk.PTId = p.produktkategorie)
								left join ( select count(*) sterne1, PId from kommentare where bewertung = '1' and geloescht = 'nein' group by PId ) s1 using (PId)
								left join ( select count(*) sterne2, PId from kommentare where bewertung = '2' and geloescht = 'nein' group by PId ) s2 using (PId)
								left join ( select count(*) sterne3, PId from kommentare where bewertung = '3' and geloescht = 'nein' group by PId ) s3 using (PId)
								left join ( select count(*) sterne4, PId from kommentare where bewertung = '4' and geloescht = 'nein' group by PId ) s4 using (PId)
								left join ( select count(*) sterne5, PId from kommentare where bewertung = '5' and geloescht = 'nein' group by PId ) s5 using (PId)
								left join produktbilder pb using (PId)
						where
							(pb.Art = 'Liste' or pb.Art is null)
							and p.geloescht = 'nein'
				";
			
			return $query;
		}
		
	}

?>
