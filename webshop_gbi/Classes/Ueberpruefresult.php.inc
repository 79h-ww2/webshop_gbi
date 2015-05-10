<?php 
	/**
	 * Klasse zur Übertragung des Funktionsresults
	 */
	class Ueberpruefresult{
		private $feld_status;
		private $fehlermeldung;
	
		/**
		 * Konstruktor
		 */
		function __construct(){
			$feld_status = array();
			$fehlermeldung = "";
		}
		
		/**
		 * übernimmt den Feldstatus, also ob das Feld richtig oder fehlerhaft gefüllt wurde
		 * @param String $feld der Feldname
		 * @param Boolean $status der Feldstatus, also ob Feld richtig gefüllt ist
		 */
		public function set_feldstatus($feld, $fehler){
			$this->feld_status[$feld] = $fehler;
		}
		
		/**
		 * übernimmt die Fehlermeldung
		 * @param String $text der Fehlermeldungstext
		 */
		public function set_fehlermeldung($text){
			$this->fehlermeldung = $text;
		}
		

		/**
		 * gibt die Fehlermeldung aus
		 * @returns String Fehlermeldungstext
		 */
		public function get_fehlermeldung(){
			return $this->fehlermeldung;
		}
		
		/**
		 * gibt den Feldstatus aus, also ob das Feld richtig ausgefüllt wurde
		 * @param String $feld Feldname
		 * @returns Boolean gibt aus, ob das Feldfehlerhaft ist
		 */
		public function get_feldstatus($feld){
			return $this->feld_status[$feld];
		}
	};
?>