<?php
	$url = file_exists('config.php.inc') ? 'config.php.inc' : '../../config.php.inc';
	include_once ( $url );

	function datenbank_verbindung_aufbauen()
	{
		global $zugriffsmodul;
		global $benutzername;
		global $passwort;
		global $server;
		global $datenbank;

		$con = new Datenbank ($zugriffsmodul, $server, $benutzername, $passwort, $datenbank);

		return $con;
	}

	class Datenbank
	{

		//Variable für die aufgebaute Datenbanksitzung
		private $db_session;
		private $zugriffsmodul;
		private $benutzername;
		private $passwort;
		private $server;
		private $datenbank;
		private $query_result;

		function __construct ($zugriffsmodul, $server, $benutzername, $passwort, $datenbank )
		{
			$this->db_session = "";
			$this->zugriffsmodul = $zugriffsmodul;
			$this->benutzername = $benutzername;
			$this->passwort = $passwort;
			$this->server = $server;
			$this->datenbank = $datenbank;
		}

		//Verbindung zur Datenbank aufbauen	
		public function db_connect()
		{
			//für folgende Variablen soll auf die globalen Variablen zugegriffen werden

			$con = "";
			$con = new mysqli( $this->server, $this->benutzername, $this->passwort, $this->datenbank );
			
			$con->set_charset("utf8");

			$this->db_session = $con;

			return $con;
		}

		//Schließt die Verbindung
		public function db_close()
		{
			$this->db_session->close();
		}

		//Passt einen String so an, das von ihn keine Gefahr für die Datenbank ausgeht. ( Mehrdeutige Zeichen, wie z.B. das ' werden \' ersetzt )
		public function db_real_escape_string ($string)
		{

			$new_value = "";

			$new_value = $this->db_session->real_escape_string ( $string );

			return $new_value;
		}

		//Datenbankanweisung ausführen
		public function db_query( $anweisung )
		{
			$this->query_result = $this->db_session->query ( $anweisung );

			return $this->query_result;
		}

		//erstellt aus den Rückgabewerten ein Objekt 
		public function db_fetch_object($result)
		{
			$result = $result->fetch_object();

			return $result;
		}

		//erstellt aus den Rückgabewerten ein Array 
		public function db_fetch_array($result)
		{
			$result =  $result->fetch_array();

			return $result;
		}


		//gibt die Anzahl der Rückgabewerte auf
		public function db_num_rows($result)
		{
			$result = $result->num_rows;

			return $result;
		}


		//gibt die Anzahl der Felder aus
		public function db_num_fields ($result)
		{
			$result = $result->field_count;

			return $result;
		}

		//gibt den Speicher des Results wieder frei
		public function db_free_result ($result)
		{
			$result->free();
		}
	}
?>
