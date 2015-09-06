<?php

//Anredesatz erstellen
$anrede = ($kunde->Geschlecht == "weiblich") ? "Sehr geehrte Frau " : "Sehr geehrter Herr ";
				
//Email-Nachricht verfassen
$nachricht  = $anrede.$kunde->Name.",\r\n";
$nachricht .= "vielen Dank fuer Ihre Registrierung beim Webshop der Global Bike Inc.\r\n";
$nachricht .= "Bitte aktivieren Sie ihr Benutzerkonto durch folgenden Link:".$aktivierungslink." .\r\n \r\n";
$nachricht .= "Mit freundlichen Gruessen\r\n";
$nachricht .= "Ihr Webshop Team der Global Bike Inc.\r\n";
	 
?>