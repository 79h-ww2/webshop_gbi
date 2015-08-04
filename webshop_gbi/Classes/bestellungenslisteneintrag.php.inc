<?php
	/**
	 * In dieser Klasse werden die Einstellungen einer Bestellung gespeichert
	 */
	class Bestellungenslisteneintrag{
		private $zahlungsart;
		private $versandart;
		
		/**
		 * Konstruktor
		 */
		function __construct(){
			$this->zahlungsart = "";
			$this->versandart = "";
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
	}
?>