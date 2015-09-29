<?php
include_once './Classes/Kommentar.php.inc';
include_once 'Classes/Kunde.php.inc';

$eingabe_ungueltig_bewertung = false;

// erlaubt nur das Ändern, wenn der Kunde angemeldet ist
if (isset ( $_SESSION ['angemeldet'] )) {
	
	$erfolgreich = false;
	
	if (isset ( $_POST ['rezension'] ) && isset ( $_POST ['ueberschrift'] ) && isset ( $_POST ['pid'] ) && isset ( $_POST ['bewertung'] )) {
		$kommentar = new Kommentar ();
		
		$eingabe_check_result_bewertung = $kommentar->ueberpruefeEingabeBew($_POST ['rezension'], $_POST ['ueberschrift'], $_POST ['bewertung']);
		
		if (! $eingabe_ungueltig_bewertung) {
			$kunde1 = new Kunden();
			$kid = $kunde1->get_kid_from_email ( $_SESSION ['angemeldet'] );
			
			// Kommentar wird zur Datenbank hinzugefügt
			$erfolgreich = $kommentar->kommentar_speichern ( $kid, $_POST ['rezension'], $_POST ['ueberschrift'], $_POST ['pid'], $_POST ['bewertung'] );	
		}
	}
	// Informationbox, die den Kunden informiert, ob die Änderung erfolgtreich ausgeführt wurde
	if ($erfolgreich) {
		$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung ( 'rezension', 'Verfassen einer Rezension', 'Ihre Rezension wurde erfolgreich hochgeladen.', 'info', '', true );
	} else {
		$msgbox->erstelleHTMLQuelltextInfoBox_mit_Meldung ( 'rezension', 'Verfassen einer Rezension', 'Beim Hochladen der Rezension ist ein Fehler aufgetreten.', 'error', '', true );
	}
}
?>