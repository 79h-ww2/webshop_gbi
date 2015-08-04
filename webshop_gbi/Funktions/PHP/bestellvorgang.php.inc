<?php
	include_once 'Classes/bestellungen.php.inc';
	
	//lädt die aktuell zwischengespeicherte Bestellung
	$bestellungen = new Bestellungen();
	$aktuelle_bestellung = $bestellungen->get_zwischengespeicherte_bestellungseinstellungen();

	//Die Versandart wird zwischengespeichert
	if ($_POST['type'] == 'bestellvorgang_versandart' && isset($_POST['versandart']) && $_POST['versandart'] != ""){		
		$aktuelle_bestellung->set_versandart($_POST['versandart']);
		$bestellungen->set_zwischengespeicherte_bestellungseinstellungen($aktuelle_bestellung);
	}
?>