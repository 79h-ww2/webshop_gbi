<?php
	include_once './Classes/Ueberpruefresult.php.inc';
	include_once './Classes/EingabeCheckGrundlegend.php.inc';
	
	class Kommentar extends EingabeCheckGrundlegend{
				
		/**
		 * erstellt neuen Kommentar
		 * @param string $kid KId
		 * @param string $text Text
		 * @param string $ueberschrift Ueberschrift
		 * @param string $pid PId
		 * @param string $geloescht geloescht
		 * @param string $bewertung bewertung
		 */
		public function kommentar_speichern($kid, $text, $ueberschrift, $pid, $bewertung){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			
			//Query, um den Kunden in der Datenbank anzulegen
			$query = "
				insert into kommentare(
					KId,
					Text,
					Ueberschrift,
					PId,
					geloescht,
					bewertung
				)values(
					'$kid',
					'$text',
					'$ueberschrift',
					'$pid',
					'nein',
					'$bewertung'
				);
			";
						
			//Kunde zur Datenbank hinzufügen
			$result = $db->db_query($query);
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			//gibt beim Fehler den Wert false zurück bei erfolgreicher Durchführung die ID des neuen Kunden
			return (!$result) ? false : true;
		}
		
		public function ueberpruefeEingabeBew($bewertung, $ueberschrift, $rezension)
		{
			$felder = array($bewertung, $ueberschrift, $rezension);
			$feldnamen = array('bewertung', 'ueberschrift', 'rezension');
			
			$meldungswort = array('ihre Sternbewertung', 'die &Uuml;berschrift', 'ihre Rezension');
			
			//Variable, wo die Fehlermeldung zwischengespeichert wird
			$fehlermeldung = "";
			
			//überprüft, ob alle Inputfelder ausgefüllt sind und erstellt wenn nicht eine Fehlermeldung
			$return = $this->erstelle_meldung_nicht_alle_felder_ausgefuellt($feldnamen, $meldungswort, $felder);
			$fehlermeldung = $return->get_fehlermeldung();
			
			//Übergibt die Fehlermeldung an das Rückgabeobjekt
			$return->set_fehlermeldung($fehlermeldung);
			
			return $return;
		}
		
		public function getKommentareByPId($pid) {
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$pid = $db->db_real_escape_string($pid);
			
			$query = "select Text, Ueberschrift, bewertung from kommentare where PId ='$pid'";
			$result = $db->db_query($query);
			
			$werte = array();
			
			$i = 0;
			while ($zeile = $db->db_fetch_object($result)){
				$werte[$i] = $zeile;
					$i++;
			}
			
			$db ->db_close();
			
			return $werte;
		}
		
		public function getKommentareByKId($kid) {
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
				
			$kid = $db->db_real_escape_string($kid);
				
			$query = "select Bezeichnung, Text, Ueberschrift, bewertung from kommentare join produkte on kommentare.PId = produkte.PId where kommentare.KId ='$kid'";
			$result = $db->db_query($query);
				
			$werte = array();
				
			$i = 0;
			while ($zeile = $db->db_fetch_object($result)){
				$werte[$i] = $zeile;
				$i++;
			}
				
			$db ->db_close();
				
			return $werte;
		}
		
		public function get_ueberschrift($kid, $pid)
		{
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
				
			$kid = $db->db_real_escape_string($kid);
			
			$query = "select Ueberschrift from kommentare where KId ='$kid' and PId = '$pid'";
			$result = $db->db_query($query);
			
			$w = "";
			while ( $wert = $db->db_fetch_array($result)){
				$w = $wert[0];
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			return $w;
		}
		
		public function get_rezension($kid, $pid)
		{
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
		
			$kid = $db->db_real_escape_string($kid);
				
			$query = "select Text from kommentare where KId ='$kid' and PId = '$pid'";
			$result = $db->db_query($query);
				
			$w = "";
			while ( $wert = $db->db_fetch_array($result)){
				$w = $wert[0];
			}
				
			//Datenbankverbindung schließen
			$db->db_close();
				
			return $w;
		}
		
		public function get_bewertung($kid, $pid)
		{
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
		
			$kid = $db->db_real_escape_string($kid);
		
			$query = "select bewertung from kommentare where KId ='$kid' and PId = '$pid'";
			$result = $db->db_query($query);
		
			$w = "";
			while ( $wert = $db->db_fetch_array($result)){
				$w = $wert[0];
			}
		
			//Datenbankverbindung schließen
			$db->db_close();
		
			return $w;
		}
		
		public function get_kommentar_from_kid($kid)
		{
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$kid = $db->db_real_escape_string($kid);
			
			$query = "select Text, Ueberschrift, bewertung, Bezeichnung from kommentare join produkte on kommentare.PId = prdukte.PId where KId ='$kid'";
			$result = $db->db_query($query);
			
			//die Rückgabewerte entgegennehmen
			$werte = array();
			$j = 0;
				
			while($zeile = $db->db_fetch_object($result)){
				$werte[$j] = $zeile;
				$j++;
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			//return $w;
			
			//Ergebnis auf der Webseite ausgeben
			$this->erstelle_auflistung_aus_datenbank_reslut_array($werte);
			
		}
		public function erstelle_auflistung_aus_datenbank_reslut_array($array_query_result_db){
				
			//wenn keine Bewertungen gefunden wurde, wird eine Meldung ausgegeben
			if ( count($array_query_result_db) == 0) {
				echo '<br/>Keine Bewertungen gefunden.';
			}
			//wenn Bewertungen gefunden wurden
			else{
				//Kopfzeile der Auflistung erstellen
				$this->schreibe_kopf_auslistung();
		
				//Produkte auflisten
				for($i = 0; $i < count($array_query_result_db); $i++ ){
						
					//Produkt aus dem Array auslesen
					$kommentar = $array_query_result_db[$i];
						
					//Sterne in einen Array zwischenspeichern
					$arr_sterne = array();
					$arr_sterne[0] = $kommentar->sterne1;
					$arr_sterne[1] = $kommentar->sterne2;
					$arr_sterne[2] = $kommentar->sterne3;
					$arr_sterne[3] = $kommentar->sterne4;
					$arr_sterne[4] = $kommentar->sterne5;
						
					//Produkt zur Liste hinzufügen
					$this->bewertung_zur_liste_hinzufuegen($kommentar->Text, $kommentar->Ueberschrift, $kommentar->bewertung, $kommentar->Bezeichnung);
				}
		
				$this->schreibe_fuss_auflistung();
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
		public function bewertung_zur_liste_hinzufuegen($text, $ueberschrift, $bewertung, $bezeichnung){
			?>
					<div class="listeneintrag_auflistung_produkte" title="<?php echo htmlspecialchars($bezeichnung,ENT_QUOTES,'UTF-8') ?>" >
						<div class="listeneintrag_auflistung_produkte_content" >
			
							<div class="listeneintrag_auflistung_produkte_beschriftung"  >
									<div>
										<a class="listeneintrag_auflistung_produkte_beschriftungstext" href="./?page=produkt&pid=<?php echo htmlspecialchars($pid,ENT_QUOTES,'UTF-8') ?>" >
											<?php echo htmlspecialchars($bezeichnung,ENT_QUOTES,'UTF-8') ?>
										</a>
									</div>
									
									</div>
									<div class="clear_right" >
									</div>
							</div>
						</div>
					</div>
		<?php
					
				}
	};
?>