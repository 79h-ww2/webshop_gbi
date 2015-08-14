<?php
	$url = file_exists('config.php.inc') ? 'config.php.inc' : '../config.php.inc';
	include_once ( $url );

	/**
	 * Funktion, welches ein Objekt der Email-Klasse instanziert
	 * @return Email
	 */
	function instanziere_email_objekt(){
		global $webshop_email_adresse;
		global $webshop_email_name;
		
		$email = new Email($webshop_email_adresse, $webshop_email_name);
		return $email;
	}
	
	/**
	 * Klasse, zum einfachen Schreiben von Emails
	 */
	class Email{
		
		//Datenfeld für die Absender-Adresse
		private $absender_adresse;
		
		//Datenfeld für den Absender-Namen
		private $absender_name;
		
		/**
		 * Konstruktor
		 * @param string $absender_adresse
		 * @param string $absender_name
		 */
		function __construct ($absender_adresse, $absender_name){
			$this->absender_adresse = $absender_adresse;
			$this->absender_name = $absender_name;
		}
		
		
		/**
		 * Versendet eine Email
		 * @param string $empfaenger_adresse Der Empfänger der Email
		 * @param string $betreff Der Betreff der Email
		 * @param string $nachricht Die Nachricht, die mit der Email übertragen werden soll
		 * @return boolean
		 */
		public function senden ($empfaenger_adresse, $betreff, $nachricht){
			
			//Email-Header wird erstellt
			$header = "From: ".$this->absender_name." <".$this->absender_adresse.">\r\n";
			$header .= "Content-type: text/plain; charset=utf-8";
			
			//versendet die Email
			$erfolgreich = mail($empfaenger_adresse,$betreff,$nachricht,$header);
			return $erfolgreich;
		}
		
		/**
		 * Versendet eine HTML-Email
		 * @param unknown $empfaenger_adresse Der Empfänger der Email
		 * @param unknown $betreff Der Betreff der Email
		 * @param unknown $html_code DeEmail-Nachricht ürbertragen werden soll
		 * @return boolean
		 */
		public function html_email_senden($empfaenger_adresse, $betreff, $html_code){
			
			//Email-Header wird erstellt
			$header = "From: ".$this->absender_name." <".$this->absender_adresse.">\r\n";
			$header  .= 'MIME-Version: 1.0' . "\r\n";
			$header .= 'Content-type: text/html; charset=utf-8' . "\r\n";
			
			//versendet die Email
			$erfolgreich = mail($empfaenger_adresse,$betreff,$html_code,$header);
			return $erfolgreich;
		}
	}
?>