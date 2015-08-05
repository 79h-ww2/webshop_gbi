<?php
	include_once 'Classes/bankeinzug.php.inc';
	
	/**
	 * In dieser Klasse werden die Einstellungen einer Bestellung gespeichert
	 */
	class Bestellungenslisteneintrag{
		private $zahlungsart;
		private $versandart;
		private $bankeinzug_daten;
		
		/**
		 * Konstruktor
		 */
		function __construct(){
			$this->zahlungsart = "";
			$this->versandart = "";
			$this->bankeinzug_daten = new Bankeinzug("", "", "");
		}
		
		/**
		 * Übergibt die Versandart
		 * @param unknown $versandart Die Versandart, die übergeben werden soll
		 */
		public function set_versandart($versandart){
			$this->versandart=$versandart;
		}
		
		/**
		 * gibt die gespeicherte Versandart aus
		 * @return Ambigous <string, string>
		 */
		public function get_versandart(){
			return $this->versandart;
		}
		
		
		/**
		 * Übergibt an die Klasse die Zahlungsart
		 * @param string $zahlungsart Die Zahlungsart
		 */
		public function set_zahlungsart($zahlungsart){
			$this->zahlungsart = $zahlungsart;
		}
		
		/**
		 * gibt die gespeicherte Zahlungsart aus
		 * @return Ambigous <string, string>
		 */
		public function get_zahlungsart(){
			return $this->zahlungsart;
		}
		
		/**
		 * Gibt die Bankeinzugsdaten aus
		 */
		public function get_bankeinzug_daten(){
			return $this->bankeinzug_daten;
		}
		
		/**
		 * Setzt die Bankeinzugsdaten
		 * @param unknown $bankeinzugs_daten Die Bankeinzugsdaten
		 */
		public function  set_bankeinzug_daten($bankeinzugs_daten){
			$this->bankeinzug_daten = $bankeinzugs_daten;
		}
	}
?>