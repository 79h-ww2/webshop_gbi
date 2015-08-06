<?php
	include_once 'Classes/bankeinzug.php.inc';
	
	/**
	 * In dieser Klasse werden die Einstellungen einer Bestellung gespeichert
	 */
	class Bestellungenslisteneintrag{
		private $zahlungsart;
		private $versandart;
		private $bankeinzug_daten;
		private $lieferadresse_art;
		private $liefer_vorname;
		private $liefer_name;
		private $liefer_geschlecht;
		private $liefer_strasse;
		private $liefer_hausnr;
		private $liefer_plz;
		private $liefer_ort;
		
		private $durchgefuehrte_schritte;
				
		/**
		 * Konstruktor
		 */
		function __construct(){
			$this->zahlungsart = "";
			$this->versandart = "";
			$this->bankeinzug_daten = new Bankeinzug("", "", "");
			$this->durchgefuehrte_schritte = 0;
		}
		
		/**
		 * Gibt an, bis welchen Schritt das Formular schon ausgefüllt ist
		 * @param int $schritt
		 */
		public function set_durchgefuehrte_schritte($schritt){
			$this->durchgefuehrte_schritte = $schritt;
		}
		
		/**
		 * gibt aus, bis welchen Schritt das Formular schon ausgefüllt ist
		 * @return Ambigous <number, int>
		 */
		public function  get_durchgefuehrte_schritte(){
			return $this->durchgefuehrte_schritte;
		}
		
		/**
		 * Übergibt den Vornamen der Person, an den das Paket geliefert werden soll
		 * @param unknown $vorname
		 */
		public function set_liefer_vorname($vorname){
			$this->liefer_vorname = $vorname;
		}
		
		/**
		 * Gibt den Vornamen der Person aus, an den das Paket gesendet werden soll
		 * @return unknown
		 */
		public function get_liefer_vorname(){
			return $this->liefer_vorname;
		}
		
		/**
		 * Übergibt den VNamen der Person, an den das Paket geliefert werden soll
		 * @param unknown $name
		 */
		public function set_liefer_name($name){
			$this->liefer_name = $name;
		}
		
		/**
		 * Gibt den Nnamen der Person aus, an den das Paket gesendet werden soll
		 * @return unknown
		 */
		public function get_liefer_name(){
			return $this->liefer_name;
		}
		
		/**
		 * Übergibt das Geschlecht der Person, an die das Paket gesendet werden soll
		 * @param unknown $geschlecht
		 */
		public function set_liefer_geschlecht($geschlecht){
			$this->liefer_geschlecht = $geschlecht;
		}
		
		/**
		 * Gibt das Geschlecht der Person aus, an die das Paket gesendet werden soll
		 */
		public function get_liefer_geschlecht(){
			return $this->liefer_geschlecht;
		}
		
		/**
		 * Übergibt die Straße, wo die Person wohnt, an die das Paket gesendet werden soll
		 * @param unknown $strasse
		 */
		public function set_liefer_strasse($strasse){
			$this->liefer_strasse = $strasse;
		}
		
		/**
		 * Gibt die Straße aus, wo die Person wohnt, an die das Paket gesendet werden soll
		 */
		public function get_liefer_strasse(){
			return $this->liefer_strasse;
		}
		
		/**
		 * Übergibt die Hausnr, der Person, an die das Paket gesendet werden soll
		 * @param unknown $hausnr
		 */
		public function set_liefer_hausnr($hausnr){
			$this->liefer_hausnr = $hausnr;
		}
		
		/**
		 * Gibt die Hausnr aus, der Person, an die das Paket gesendet werden soll
		 */
		public function get_liefer_hausnr(){
			return $this->liefer_hausnr;
		}
		
		/**
		 * Übergibt die Postleitzahl des Wohnortes der Person, an die das Paket gesendet werden soll
		 * @param unknown $plz
		 */
		public function set_liefer_plz($plz){
			$this->liefer_plz = $plz;
		}
		
		/**
		 * Gibt die Postleitzahl des Wohnortes der Person aus, an die das Paket gesendet werden soll
		 * @param unknown $plz
		 */
		public function get_liefer_plz(){
			return $this->liefer_plz;
		}
		
		/**
		 * Übergibt den Wohnort der Person, an den das Paket gesendet werden soll
		 * @param unknown $ort
		 */
		public function set_liefer_ort($ort){
			$this->liefer_ort = $ort;
		}
		
		/**
		 * Gibt den Wohnort der Person aus, an den das Paket gesendet werden soll
		 * @param unknown $ort
		 */
		public function get_liefer_ort(){
			return $this->liefer_ort;
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
		
		
		/**
		 * Gibt an, ob die registrierte oder eine andere Adresse als Lieferadresse verwendet werden soll
		 * @param string $art 
		 */
		public function set_lieferadresse_art($art){
			$this->lieferadresse_art = $art;
		}
		
		/**
		 * Gibt aus, ob die registrierte oder eine andere Adresse als Lieferadresse verwendet werden soll
		 * @return string
		 */
		public function get_leiferadresse_art(){
			return $this->lieferadresse_art;
		}
	}
?>