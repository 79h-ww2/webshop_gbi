<?php
	include_once './Classes/bewertung.php.inc';
	include_once './Classes/artikel.php.inc';
	include_once './Classes/suche.php.inc';
	
	//überprüft, ob alle nötigen Felder übertragen wurden
	if (isset($_POST['marke']) && isset($_POST['produktbezeichnung']) &&  isset($_POST['preis_von']) && isset($_POST['preis_bis']) && isset($_POST['kategorie']) && isset($_POST['bauart']) && isset($_POST['bauvariante']) && isset($_POST['artikelnr']))
	
	//wenn alle Felder übertragen wurden wird überprüft, ob die Eingabe gültig ist
	$suche_vorcheck = new Suche();
	$suche_vorcheck_fehler = $suche_vorcheck->erweiterte_suche_eingabe_pruefen($_POST['produktbezeichnung'], $_POST['preis_von'], $_POST['preis_bis'], $_POST['kategorie'], $_POST['bauart'], $_POST['bauvariante'], $_POST['artikelnr'], $_POST['marke']);
	

	if ($suche_vorcheck_fehler->get_fehlermeldung() == ""){
		//wenn der Vorcheck erfolgreich war, wird zur Suchergebnisanzeige weitergeleitet
		header("location:./?page=such_erg&produktbezeichnung=".$_POST['produktbezeichnung']."&preis_von=".$_POST['preis_von']."&preis_bis=".$_POST['preis_bis']."&kategorie=".$_POST['kategorie']."&bauart=".$_POST['bauart']."&bauvariante=".$_POST['bauvariante']."&artikelnr=".$_POST['artikelnr']."&marke=".$_POST['marke']);
	};
?>