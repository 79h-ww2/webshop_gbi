<?php
	//Angaben zur Verbindung mit der Datenbank
	$benutzername = 'root';
	$passwort = '';
	$datenbank = 'webshop';
	$server = '127.0.0.1';
	
	//Festlegung der Webshop-Emailadresse
	$webshop_email_adresse = "webshop@fahrrad-gbi.de";
	$webshop_email_name = "Webshop Fahrrad GBI";
	
	//Konto-Daten der GBI für die Bestätiguns-Email (wenn Vorkasse von Kunden gewählt)
	$bankdaten_gbi = array ("inhaber" => "Global Bike Inc.", "iban" => "DE08700901xxxxDemo", "bic" => "1234567890B");
	
	//Benötigte Plugins:
	//php5-mcrypt, php5-mysql
