<?php 
include_once 'Classes/Ueberpruefresult.php.inc';
include_once "Classes/warenkorbeintrag.php.inc";
include_once "Classes/EingabeCheckGrundlegend.php.inc";
include_once 'Classes/artikel.php.inc';
include_once 'Classes/ArtikelDetails.php.inc';
include_once 'Classes/meldungsfenster.php.inc';
		
class warenkorb extends EingabeCheckGrundlegend{ 
     
 function __construct(){ 
 	if (!isset($_SESSION["Warenkorb"])){
 	 
 		$_SESSION["Warenkorb"] = array();
	 } 
  	}
  	
  	/*  Menge im Warenkorb, falls 2 mal der gleiche Artikel hinzugefügt, wird ingsgesamt nur 1 Artikel
  	 * mit der gewünschte Menge angezeigt
  	 */
 	public function artikel_in_den_warenkorb_legen ($artikelnummer, $menge){
		if ( $this->objekt_schon_im_warenkorb($artikelnummer) != -1){
			$w = $_SESSION["Warenkorb"];
			$y = $w[$this->objekt_schon_im_warenkorb($artikelnummer)];
			$x = $y->get_menge();
			$x+= $menge;
			$_SESSION["Warenkorb"][$this->objekt_schon_im_warenkorb($artikelnummer)]->set_menge($x);
		}
			else {
 		$index=count($_SESSION["Warenkorb"]);
 		$eintrag = new warenkorbeintrag($menge, $artikelnummer);
 		$_SESSION["Warenkorb"][$index] = $eintrag;
			}
 	 	}
 	
 	public function menge_im_warenkorb(){
 		
 		$menge = 0;
 		for( $i = 0; $i < count($_SESSION["Warenkorb"]); $i++){
 			$w = $_SESSION["Warenkorb"];
 			$y = $w[$i];
 			$menge += $y->get_menge();
 		}
 		return $menge;		
 	 }
 	 
 	 public function artikel_im_warenkorb_anzeigen(){
 	 	$w = $_SESSION["Warenkorb"];
 	 	return $w;
 	 	  	 		
 	  }
 	  
 	/**
 	 * Überprüft, ob die eingegebene Menge, die in den Warenkorb gepackt werden soll gültig ist
 	 * Übernommen von Benedikt, um den Zeitplan einhalten zu können
 	 * @param unknown $menge Menge, die in den Warenkorb gepackt werden soll
 	 * @param unknown $pid Artikel- bzw. Produkt-ID
 	 * @param boolean $update Gibt an, ob es sich um eine Änderung der Menge handelt, wenn der Artikel schon im Warenkorb ist
 	 * @return Ambigous <string, Ueberpruefresult> Rückgabewert der Überprüfung, mit Fehlermeldung und Array der falschen Felder
 	 */ 
 	public function ueberpruefe_eingegebene_menge_warenkorb($menge, $pid, $update){
 		
 		//Array mit allen Feldern, die ausgefüllt sein müssen
 		$felder = array($menge);
 		$feldnamen = array('menge');
 		
 		//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
 		$meldungswort = array('die Menge der Artikel an, die in den Warenkorb gepackt werden soll');
 		
 		//Variable für die Fehlermeldung
 		$fehlermeldung = "";
 		
 		//überprüft, ob alle Inputfelder ausgefüllt sind und erstellt wenn nicht eine Fehlermeldung
 		$return = $this->erstelle_meldung_nicht_alle_felder_ausgefuellt($feldnamen, $meldungswort, $felder);
 		$fehlermeldung = $return->get_fehlermeldung();
 		
 		//wenn alle Felder ausgefüllt sind, wird überprüft, ob die Eingaben gültig sind
 		if ($fehlermeldung == "") {
 			
 			$return->set_feldstatus('menge', true); //markiert das Mengenfeld standardmäßig als falsch
 			
 			//überprüft, ob der Wert im Mengen-Inputfeld eine gültige Zahl ist
 			if (is_numeric($menge) == false){
 				$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
 				$fehlermeldung .= "Die Mege muss ein Zahlwert sein.";
 			}
 			//Fehlermedung, wenn die Zahl nicht positive ist
 			elseif ($menge < 1){
 				$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
 				$fehlermeldung .= "Die Menge muss eine positive Zahl sein, die größer als 0 ist.";
 			}
 			//Erlaubt nur ganze Zahlen
 			elseif (ceil($menge) != $menge ){
 				$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
 				$fehlermeldung .= "Es muss eine ganze Zahl eingegeben werden.";
 			}
 			//Fehlermeldung, wenn versucht wird mehr Artikel, als vorhanden in den Warenkorb zu packen
 			else{
 				$aktuellerArtikel = new ArtikelDetails();
 				$artikel_info = $aktuellerArtikel->beschreibungAnzeigen($pid);
 				$vorhandene_menge = $artikel_info->Menge;
 				
 				$menge_schon_in_korb = 0;
 				if ( $this->objekt_schon_im_warenkorb($pid) != -1 ) {
 					$warenkorb = $_SESSION["Warenkorb"][$this->objekt_schon_im_warenkorb($pid)];
 					$menge_schon_in_korb = $warenkorb->get_menge();
 				}
 				
 				
 				if ($vorhandene_menge < $menge || $vorhandene_menge < ($menge + $menge_schon_in_korb) && !$update){
 					$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
 					$fehlermeldung .= "Es können nicht mehr Exemplare bestellt werden, als auf Lager sind.";
 					
 					if ($menge_schon_in_korb > 0 && !$update) $fehlermeldung .= " Es sind schon $menge_schon_in_korb Objekte im Warenkorb.";
 				}
 				//wenn kein Fehler aufgetreten ist
 				else{
 					$return->set_feldstatus('menge', false); //Fehlermarkierung beim Mengenfeld wird aufgehoben
 				}
 			}
 		}
 		
 		//Übergibt an das Rückgabeobjekt die Fehlermeldung
 		$return->set_fehlermeldung($fehlermeldung);
 			
 		return $return;
 	}
 	
 	/**
 	 * überprüft, ob das Objekt schon existiert
 	 * wenn das Objekt schon existiert wird der Index im Warenkorb angegeben
 	 * @param unknown $artikelnummer Artikelnummer
 	 * @return number Index im Warenkorb
 	 */
 	public function objekt_schon_im_warenkorb($artikelnummer){
 		$artikelschonvorhanden = -1;
 		for( $i = 0; $i < count($_SESSION["Warenkorb"]); $i++){
 			$w = $_SESSION["Warenkorb"];
 			$y = $w[$i];
 			if ($y->get_artikelnummer() == $artikelnummer) $artikelschonvorhanden = $i;
 		}
 		
 		return $artikelschonvorhanden;
 	}
 	
 	/**
 	 * Zeigt eine Sicherheitsnachfrage an, wo der Benutzer bestätigen muss, wenn wirklich der Artikel aus dem Warenkorb gelöscht werden soll
 	 * @param number $pid Artikelnummer des Artikels
 	 */
 	public function sicherheitsnachfrage_ein_artikel_auswarenkorb_entfernen($pid){
 		
 		//bestimmt, welchen Index der Artikel im Warenkorb hat
 		$warenkorbIndex = $this->objekt_schon_im_warenkorb($pid);
 		
 		//bestimmt, den Artikelnamen
 		$w = $_SESSION["Warenkorb"];
 		$y = $w[$warenkorbIndex];
 		$artikelname = $y->get_artikelnamen();
 		
 		//zeigt die Sicherheitsfrage an
 		$msg = new Meldungsfenster();
 		$msg->erstelleHTMLQuelltextConfirmBox_mit_Meldung("artikel_loeschen", "Gewählten Artikel löschen", "Wollen Sie den Artikel \"$artikelname\" wirklich aus dem Warenkorb entfernen?" , "question", "artikel-warenkorb-entfernen","bestaetigt.".$pid,  "artikel-warenkorb-entfernen", "verneint", "ja", "nein", true);
 	}
 	
 	
 	/**
 	 * Zeigt eine Sicherheitsnachfrage an, wo der Benutzer bestätigen muss, dass wirklich die markierten Artikel gelöscht werden sollen
 	 * @param number $arr_pids Array mit den Atrikelnummern, die aus dem Warenkorb entfernt werden sollen
 	 */
 	public function sicherheitsnachfrage_mehrere_artikel_aus_warenkorb_entfernen($arr_pids){
 		
 		//erstellt eine Array mit den Indexen, wo sich der Artikel im Warenkorb befindet
 		$warenkorbIndexe = array();
 		
 		$summe_produkte = count($arr_pids);
 			 			
 		//zeigt die Sicherheitsfrage an
 		$msg = new Meldungsfenster();
 		if ($summe_produkte > 0){
 			//erstellt einen Zeichenkette, wo die zum Entfernen markierten Artikel mit Punkt getrennt hintereinander geschrieben werden
 			$pids_str_loeschen = implode(".", $arr_pids);
	 		
	 		$loeschmeldung = ($summe_produkte == 1) ? "Wollen Sie wirklich das gewählte Produkt aus dem Warenkorb entfernen?" : "Wollen Sie wirklich die $summe_produkte markierten Produkte aus dem Warenkorb entfernen.";
	 		$msg->erstelleHTMLQuelltextConfirmBox_mit_Meldung("artikel_loeschen", "Gewählte Artikel löschen", $loeschmeldung , "question", "artikel-warenkorb-entfernen","bestaetigt_mehrere_pids.".$pids_str_loeschen,  "artikel-warenkorb-entfernen", "verneint", "ja", "nein", true);
 		}
 		//Infomirt den Benutzer, dass kein Produkt markiert wurde
 		else{
 			$msg->erstelleHTMLQuelltextInfoBox_mit_Meldung("warenkorb_nichts_markiert", "Kein Artikel markiert", "Bitte markieren Sie einen Artikel, der gelöscht werden soll.", 'info', '', true);
 		}
 	}
 	

 	/**
 	 * Entfernt den Artikel mit der übergebenen Artikelnummer aus dem Projekt
 	 * @param nummer $pid Die übergebene Artikelnummer
 	 */
 	public function entferne_artikel_aus_warenkorb($pid){
 		//bestimmt, welchen Index der Artikel im Warenkorb hat
 		$warenkorbIndex = $this->objekt_schon_im_warenkorb($pid);
 		
 		//eine Zählvariable für ein neues Array, wo der Artikel nicht mehr enthalten ist
 		$z = 0;
 		
 		//das neue Array wird erstellt
 		$warenkorb_neu = array();
 		
 		//der alte Warenkorb
 		$warenkorb_alt = $_SESSION["Warenkorb"];
 		
 		//füllt den neuen Warenkorb mit den Produkten des alten und lässt das entfernte Produkt weg
 		for ( $i = 0; $i < count($warenkorb_alt); $i++){
 			if ($i != $warenkorbIndex){
 				$warenkorb_neu[$z] = $warenkorb_alt[$i];
 				$z++;
 			}
 		}
 		
 		//speichert den neuen Warenkorb in der SESSION-Variable
 		$_SESSION["Warenkorb"] = $warenkorb_neu;
 	}
 	
 	/**
 	 * Entfernt mehrere Artikel aus dem Warenkorb
 	 * @param number $arr_pids Array mit den Artikelnumern, die aus dem Warenkorb entfernt werden sollen
 	 */
 	public function mehrere_artikel_aus_warenkorb_entfernen($arr_pids){
 		foreach ($arr_pids as $pid){
 			$this->entferne_artikel_aus_warenkorb($pid);
 		}
 	}
 	
 	/**
 	 * Zeigt ein Popup-Fenster an, wo der Benutzer die Bestellmenge ändern kann
 	 * @param unknown $pid
 	 */
 	public function zeige_fenster_bestellmenge_aendern_atrikel($pid, $fehler){
 		
 		//JavaScripts für den Vorcheck werden hinzugefügt
 		echo
 		'
 			<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
    		</script>
    		<script type="text/javascript" src="Funktions/JS/vorcheck_warenkorb.js">
    		</script>
 		';
 		
 		//bestimmt die Menge, wie viele Objekte des Artikels sich auf Lager befindet
 		$aktuellerArtikel = new ArtikelDetails();
 		$artikel_info = $aktuellerArtikel->beschreibungAnzeigen($pid);
 		$vorhandene_menge = $artikel_info->Menge;
 		
 		//Unsichtbares Div, welches die auf Lager vorhandene Menge enthält (um schon bestehende JS-Script-Vorcheckmethode nutzen zu können)
 		echo '<span style="display:none" id="exemplare_auf_lager" >'.htmlspecialchars($vorhandene_menge,ENT_QUOTES,'UTF-8').'</span>';
 		
 		//Bestimmt die Bestellmenge, die in Moment im Warenkorb vorzufinden ist
 		$warenkorbIndex = $this->objekt_schon_im_warenkorb($pid);
 		$w = $_SESSION["Warenkorb"];
 		$y = $w[$warenkorbIndex];
 		$menge_aktuell = $y->get_menge();
 		
 		
 		//Zeigt das Popup-Fenster an, wo der Benutzer die neue Bestellmenge eingeben kann
 		$action_link = "./?page=warenkorb";
 		$msg = new Meldungsfenster();
 		$wort_exemplar = ($vorhandene_menge != 1) ? "Exemplare" : "Exemplar";
 		
 		$msg->erstelleHTMLQuelltextTextinputbox($pid, "Bestellmenge ändern", "Tippen Sie in dieses Fenster die neue Bestellmenge ein. $vorhandene_menge $wort_exemplar des Artikels sind auf Lager vorhanden.", "Menge", "menge", "OK", "Abbrechen", $action_link, "post", true, "eintrag_in_warenkorb_vorcheck();", "fehlermeldung_warenkorb", $fehler, $menge_aktuell, "from_warenkorb", "60px", "warenkorb-artikel-mengenaewnderung" );
 	}
 	
 	/**
 	 * Gibt den Gesamtpreis der Artikel im Warenkorb aus
 	 * @return float Der Gesamtpreis
 	 */
 	public function get_gesamtpreis_artikel_im_warenkorb(){
 		
 		$preis_summe = 0;
 		//addiert die Gesamtpreise der Artikel
 		foreach ($_SESSION["Warenkorb"] as $artikel){
 			$preis_summe += $artikel->get_gesamtpreis_artikel();
 		}
 		
 		return $preis_summe;
 	}
 	
 	/**
 	 * Ändert die Bestellmenge eines Artikels im Warenkorb
 	 * @param unknown $pid Artikelnummer
 	 * @param unknown $menge Bestellmenge
 	 */
 	public function aendere_bestellmenge_artikel_im_warenkorb($pid, $menge){
 		//bestimmt den Index des Artikels im Warenkorb
 		$warenkorbIndex = $this->objekt_schon_im_warenkorb($pid);
 		
 		//ändert die Menge im Warenkorb
 		$w = $_SESSION["Warenkorb"];
 		$y = $w[$warenkorbIndex];
 		$y->set_menge($menge);
 		
 		//speichert die geänderte Menge in der SESSION-Variable
 		$w[$warenkorbIndex] = $y;
 		$_SESSION["Warenkorb"] = $w;
 	}
}
?>