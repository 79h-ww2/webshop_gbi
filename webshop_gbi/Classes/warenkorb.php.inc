<?php 
include_once 'Classes/Ueberpruefresult.php.inc';
include_once "Classes/warenkorbeintrag.php.inc";
include_once "Classes/EingabeCheckGrundlegend.php.inc";
include_once 'Classes/artikel.php.inc';
include_once 'Classes/ArtikelDetails.php.inc';
		
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
		$artikelschonvorhanden = -1;
		for( $i = 0; $i < count($_SESSION["Warenkorb"]); $i++){
 			$w = $_SESSION["Warenkorb"];
 			$y = $w[$i];
 			if ($y->get_artikelnummer() == $artikelnummer) $artikelschonvorhanden = $i;
		}
		if ($artikelschonvorhanden!= -1){
			$w = $_SESSION["Warenkorb"];
			$y = $w[$artikelschonvorhanden];
			$x = $y->get_menge();
			$x+= $menge;
			$_SESSION["Warenkorb"][$artikelschonvorhanden]->set_menge($x);
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
 	 * @return Ambigous <string, Ueberpruefresult> Rückgabewert der Überprüfung, mit Fehlermeldung und Array der falschen Felder
 	 */ 
 	public function ueberpruefe_eingegebene_menge_warenkorb($menge, $pid){
 		
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
 			//Fehlermdelung, wenn versucht wird mehr Artikel, als vorhanden in den Warenkorb zu packen
 			else{
 				$aktuellerArtikel = new ArtikelDetails();
 				$artikel_info = $aktuellerArtikel->beschreibungAnzeigen($pid);
 				$vorhandene_menge = $artikel_info->Menge;
 				
 				if ($vorhandene_menge < $menge){
 					$fehlermeldung .= ($fehlermeldung == '') ? '' : ' ';
 					$fehlermeldung .= "Es können nicht mehr Exemplare bestellt werden, als auf Lager sind.";
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

}
?>