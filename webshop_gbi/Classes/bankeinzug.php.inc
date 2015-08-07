<?php
	include_once 'Classes/EingabeCheckGrundlegend.php.inc';

	class Bankeinzug extends EingabeCheckGrundlegend{
		
		//Attribute
		private $iban;
		private $bic;
		private $kontoinhaber;
		
		/**
		 * Konstruktor
		 * @param string $iban Die IBAN-Nummer
		 * @param string $bic Die BIC-Nummer
		 * @param string $kontoinhaber Der Kontoinhaber
		 */
		function __construct($iban, $bic, $kontoinhaber){
			$this->iban = $iban;
			$this->bic = $bic;
			$this->kontoinhaber = $kontoinhaber;
		}
		
		/**
		 * gibt die IBAN-Nummer aus
		 * @return string
		 */
		public function get_iban(){
			return $this->iban;
		}
		
		/**
		 * Übergibt die IBAN-Nummer
		 * @param string $iban Die IBAN-Nummer
		 */
		public function  set_iban($iban){
			$this->iban = $iban;
		}
		
		/**
		 * Gibt die BIC-Nummer aus
		 * @return string
		 */
		public function  get_bic(){
			return $this->bic;
		}
		
		/**
		 * Übergibt die BIC-Nummer
		 * @param string $bic
		 */
		public function set_bic ($bic){
			$this->bic = $bic;
		}
		
		/**
		 * Gibt den Kontoinhaber aus
		 * @return string
		 */
		public function get_kontoinhaber(){
			return $this->kontoinhaber;
		}
		
		/**
		 * Übergibt den Kontoinhaber
		 * @param string $kontoinhaber Der Kontoinhaber
		 */
		public function set_kontoinhaber($kontoinhaber){
			$this->kontoinhaber = $kontoinhaber;
		}
		
		/**
		 * überprüft die eingegeben Daten
		 * @return Ueberpruefresult
		 */
		public function daten_pruefen(){
			//Array mit allen Feldern, die ausgefüllt sein müssen
			$felder = array($this->kontoinhaber, $this->iban, $this->bic);
			$feldnamen = array('inhaber', 'iban', 'bic');
				
			//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
			$meldungswort = array('den Kontoinhaber', 'die IBAN-Nummer', 'den BIC-Code');
			
			//Variable für die Fehlermeldung
			$fehlermeldung = "";
				
			//überprüft, ob alle Inputfelder ausgefüllt sind und erstellt wenn nicht eine Fehlermeldung
			$return = $this->erstelle_meldung_nicht_alle_felder_ausgefuellt($feldnamen, $meldungswort, $felder);
			$fehlermeldung = $return->get_fehlermeldung();
			
			//wenn alle Felder ausgefüllt sind, wird überprüft, ob die Eingaben gültig sind
			if ($fehlermeldung == "") {
				//überprüft, die IBAN-Nummer
				if ($this->ueberpruefe_iban_pruefsumme() == false){
					//wenn die IBAN-Nummer ungültig ist
					$fehlermeldung .="Die IBAN-Nummer ist ungültig.";
					$return->set_feldstatus('iban', true);
				}
				
				//Wenn der BIC-Code nicht die gültige Länge besitzt
				if (!(strlen($this->bic) == 8 || strlen($this->bic) == 11)){
					$fehlermeldung .= "Der BIC-Code hat nicht die gültige Länge.";
					$return->set_feldstatus("bic", true);
				}
			}
			
			$return->set_fehlermeldung($fehlermeldung);
			
			return  $return;
		}
		
		/**
		 * Überprüft, die eingegebene IBAN
		 * @return mixed|boolean
		 */
		public function ueberpruefe_iban_pruefsumme(){
			

			$iban = $this->iban;
			$iban = str_replace( ' ', '', $iban );
			$iban1 = substr( $iban,4 )
			. strval( ord( $iban{0} )-55 )
			. strval( ord( $iban{1} )-55 )
			. substr( $iban, 2, 2 );
				
			$rest=0;
			for ( $pos=0; $pos<strlen($iban1); $pos+=7 ) {
				$part = strval($rest) . substr($iban1,$pos,7);
				$rest = intval($part) % 97;
			}
			$pz = sprintf("%02d", 98-$rest);
				
			if ( substr($iban,2,2)=='00')
				return substr_replace( $iban, $pz, 2, 2 );
			else
				return ($rest==1) ? true : false;
			
			//################################### Mein Versuch: Problem IBAN ist aus den Datenbereich von Long
			/*$fehler = false;
			
			$buchstabenliste = array("A" => "10", "B" =>"11", "C" => "12", "D" => "13", "E" => "14", "F" => "15", "G" => "16", "H" => "17", "I" => "18", "J" => "19", "K" => "20", "L" => "21", "M" => "22", "N" => "23", "O" => "24", "P" => "25", "Q" => "26", "R" => "27", "S" => "28", "T" => "29", "U" => "30", "V" => "31", "W" => "32", "X" => "33", "Y" => "34", "Z" => "35");
			
			//Leerzeichen aus der IBAN entfernen
			$iban = str_replace(" ", "", $this->iban);
			
			//Ländercode aus dem String herausfiltern
			$laendercode = substr($iban, 0,2);
			
			//Wenn der Ländercode aus Buchstaben besteht, der Rest der IBAN Zahlenwerte sind und die IBAN nicht länger als 34 Zeichen besitzt 
			if (preg_match("/^[a-zA-Z]+$/", $laendercode) && is_numeric(substr($iban,2)) && strlen($iban) < 35) {
				
				//Ländercode wird als Ziffern umgewandelt
				$laendercode = strtoupper($laendercode);
				$laendercode_ziffern = $buchstabenliste[substr($laendercode,0,1)];
				$laendercode_ziffern .= $buchstabenliste[substr($laendercode,1,1)];
				
				//IBAN wird so umgestellt, dass der Modulo berechnet werden kann
				$iban_mod_form = substr($iban,4).$laendercode_ziffern."00";
				
				
				//Berechnet den Modulo
				$mod = $iban_mod_form % 97;
								
				//berechnet die Prüfsumme aus dem Modulo
				$pruefsumme = 98- $mod;
				
				
				//Vergleicht die Prüfsumme mit der Prüfsumme der IBAN-Nummer
				if (substr($iban,2,2) != $pruefsumme) $fehler = true;
	
			}
			//Fehler, wenn der Länder-Code nicht aus Buchstaben besteht oder die Syntax der IBAN nicht eingehalten wurde
			else{
				$fehler = true;
			}
			
			if ($fehler){
				die("falsch");
			}else{
				die("richtig");
			}
			
			return $fehler;*/
		}
	} 
?>