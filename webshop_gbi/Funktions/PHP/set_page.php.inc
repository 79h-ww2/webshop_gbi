<?php
if (isset ( $_GET ['page'] ) && $_GET ['page'] != "") {
	
	switch ($_GET ['page']) {
		case 'reg' :
			include "./Pages/registrierung.php.inc";
			break;
		case 'such_erg' :
			include "./Pages/suchergebnis.php.inc";
			break;
		case 'suche_erweitert' :
			include "./Pages/erweiterte_suche.php.inc";
			break;
		case 'impressum' :
			include './Pages/impressum.php.inc';
			break;
		case 'agb' :
			include './Pages/AGB.php.inc';
			break;
		case 'datenschutz' :
			include './Pages/datenschutz.php.inc';
			break;
		case 'uebersicht' :
			include './Pages/uebersicht.php.inc';
			break;
		case 'produkt' :
			include_once 'Pages/ArtikelDetailansicht.php.inc';
			break;
		
		case 'profilbearbeiten' :
			// profil kann nur bearbeitet werden, wenn der Kunde angemelet ist
			if (isset ( $_SESSION ['angemeldet'] )) {
				include './Pages/profilbearbeiten.php.inc';
			} else {
				echo "Sie müssen angemeldet sein, um Ihr Profil ändern zu können.";
			}
			break;
		case 'artBewerten' :
			include_once './Pages/ArtikelBewerten.php.inc';
			break;
		case 'login' :
			include_once './Pages/Login.php.inc';
			break;
		case 'warenkorb' :
			include_once './Pages/warenkorb.php.inc';
			break;
		case 'bestellung':
			include_once './Pages/bestellvorgang.php.inc';
			break;
		case 'bestellungen':
			include_once './Pages/bestellungen.php.inc';
		break;
		case 'fahrrad_katg':
			include_once './Pages/uebersicht_fahrradkategorien.php.inc';
			break;
		case 'konto_uebersicht':
			include_once './Pages/uebersicht_konto.php.inc';
			break;
		case 'rezensionen':
			include_once './Pages/meine_rezensionen.php.inc';
			break;
		case 'produkt_rezensionen_uebersicht':
			include_once './Pages/produkt_rezensionen.php.inc';
			break;
		default :
			echo "<br/><h2>Gewünschte Seite wurde nicht gefunden.</h2>";
	}
} else {
	// Startseite zeigen
	include "./Pages/startseite.php.inc";
}
?>
