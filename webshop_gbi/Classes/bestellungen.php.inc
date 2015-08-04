<?php 
	include_once "Classes/EingabeCheckGrundlegend.php.inc";
	include_once 'Classes/bestellungenslisteneintrag.php.inc';
	
	/**
	 * Diese Klasse dient dazu die Bestellungen zu verwalten
	 */
	class Bestellungen extends EingabeCheckGrundlegend{
		
		/**
		 * Konstruktor
		 */
		function __construct(){
			
			//erstellt eine Server-SESSION-Variable, um vorübergehend die Bestellungseinstellungen zu speichern
			if (!isset($_SESSION["bestellungenslisteneintrag"])){
				$_SESSION["bestellungenslisteneintrag"] = new Bestellungenslisteneintrag();
			}
		}
		
		/**
		 * Gibt die zwischengespeicherten Bestellungseinstellungen aus 
		 * @return Bestellungenslisteneintrag
		 */
		public function get_zwischengespeicherte_bestellungseinstellungen(){
			return $_SESSION["bestellungenslisteneintrag"];
		}
		
		/**
		 * Übergibt die Bestellungseinstellungen, die zwischengespeichert werden sollen
		 * @param Bestellungenslisteneintrag $bestellungseinstellungen Die Bestellungseinstellungen
		 */
		public function set_zwischengespeicherte_bestellungseinstellungen($bestellungseinstellungen){
			$_SESSION["bestellungenslisteneintrag"] = $bestellungseinstellungen;
		}
	}
?>