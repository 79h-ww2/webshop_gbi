<?php
	class EingabeCheckGrundlegend{
		
		/**
		 * überprüft, ob alle Inputfelder des übergebenden Arrays ausgefüllt sind
		 * @param unknown $arr_feldnamen Array: Name der Inputfelder
		 * @param unknown $arr_meldungswoerter Array: Meldungswörter für die Fehlermeldung
		 * @param unknown $arr_werte_felder Array: Inhalt der Inputfelder
		 * @return string
		 */
		public function erstelle_meldung_nicht_alle_felder_ausgefuellt($arr_feldnamen, $arr_meldungswoerter, $arr_werte_felder){
			
			//Objekt, über das der Funktionsrückgabewert übergeben werden soll
			$return = new Ueberpruefresult();
				
			//Array mit allen Feldern, die ausgefüllt sein müssen
			$felder = $arr_werte_felder;
			$feldnamen = $arr_feldnamen;
			
			//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
			$meldungswort = $arr_meldungswoerter;
			
			//Variable, wo die Fehlermeldung zwischengespeichert wird
			$fehlermeldung = "";
			
			//Array, wo alle nicht ausgefüllten Felder gespeichert werden sollen
			$nicht_ausgefuellte_felder = array();
			
			//überprüft jedes Feld
			$z = 0;
			for($i = 0; $i < count($felder); $i++){
				//wenn das Feld nicht ausgefüllt ist
				if ($felder[$i] == ""){
					//fügt das Feld zur Liste der nicht ausgefüllten Felder hinzu
					$nicht_ausgefuellte_felder[$z] = $meldungswort[$i];
					$z++;
			
					//schaltet das Feld in den Rückgabeobjekt auf fehlerhaft
					$return->set_feldstatus($feldnamen[$i], true);
				}
				//wenn das Feld richtig ausgefüllt ist
				else{
					//schaltet das Feld in den Rückgabeobjekt auf nicht fehlerhaft
					$return->set_feldstatus($feldnamen[$i], false);
				}
			}
			
			//wenn nicht jedes Feld ausgefüllt ist, wird eine Fehlermeldung generiert
			if ( count($nicht_ausgefuellte_felder) > 0 ){
				if ( count($nicht_ausgefuellte_felder) == 1 ){
					$fehlermeldung = 'Bitte geben Sie '.$nicht_ausgefuellte_felder[0].' an.';
				}else{
					for ($j = 0; $j < count($nicht_ausgefuellte_felder); $j++){
						if ($j == 0){
							$fehlermeldung = 'Bitte geben Sie '.$nicht_ausgefuellte_felder[$j];
						}else if ( $j < (count($nicht_ausgefuellte_felder)-1)){
							$fehlermeldung .= ', '.$nicht_ausgefuellte_felder[$j];
						}else{
							$fehlermeldung .= ' und '.$nicht_ausgefuellte_felder[$j].' an.';
						}
					}
				}
			}
			
			//Übergibt an das Rückgabeobjekt die Fehlermeldung
			$return->set_fehlermeldung($fehlermeldung);
			
			return $return;
		}
	}
?>