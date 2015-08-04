<?php
$result_ueberpruefung = "";
if (isset($_POST['type']) && isset($_POST['menge']) && isset($_POST['pid']) && $_POST['type'] == 'neuerArtikelimWarenkorb'){
	
	$warenkorb1 = new warenkorb();
	
	//überprüft, ob die angegebene Menge, die in den Warenkorb gepackt werden soll gültig ist
	$result_ueberpruefung = $warenkorb1->ueberpruefe_eingegebene_menge_warenkorb($_POST['menge'], $_POST['pid'], false);

	$mengen_fehler = true; //Variable, die festhält, ob die Mengenangabe gültig war
	
	//wenn die Eingabe gültig ist
	if ( $result_ueberpruefung->get_fehlermeldung() == ""){
		
		$mengen_fehler = false; //speichert in der Variabel, das die Eingabe gültig war
		
		//den Artikel zum Warenkorb hinzufügen
		$warenkorb1->artikel_in_den_warenkorb_legen($_POST['pid'],$_POST['menge']);
	}
}

//Sicherheitsfrage, wenn mehrere Artikel aus dem Warenkorb gelöscht werden sollen
elseif (isset($_POST['type']) && $_POST['type'] == 'markierung_loeschen_warenkorb'){
	//entfernt aus dem über Post übermittelten Werten alle Werte, die keine Artikelnummer sind
	$werte = $_POST;
	if (isset($werte['type'])) unset($werte['type']);
	if (isset($werte['submit'])) unset($werte['submit']);
	
	$warenkorb1 = new warenkorb();
	//Zeigte eine Sicherheitsfrage an, ob die markierten Produkte wirklich aus dem Warenkorb entfernt werden sollen
	$warenkorb1->sicherheitsnachfrage_mehrere_artikel_aus_warenkorb_entfernen($werte);
}

//Bestellmenge eines Artikels ändern
elseif (isset($_POST['type']) && $_POST['type'] == 'warenkorb-artikel-mengenaewnderung' && isset($_POST['idBox']) && isset($_POST['menge'])){
	$pid = $_POST['idBox'];
	$menge = $_POST['menge'];
	
	$warenkorb1 = new warenkorb();
	
	//überprüft, ob die angegebene Menge, die in den Warenkorb gepackt werden soll gültig ist
	$result_ueberpruefung = $warenkorb1->ueberpruefe_eingegebene_menge_warenkorb($menge, $pid, true);
	

	//wenn die Eingabe gültig ist
	if ( $result_ueberpruefung->get_fehlermeldung() == ""){
		//Bestellmenge im Warenkorb ändern
		$warenkorb1->aendere_bestellmenge_artikel_im_warenkorb($pid, $menge);
	}
	//wenn die Eingabe ungültig ist
	else{
		$link = (isset($_GET['page']) && $_GET['page'] == "warenkorb") ? "./?page=warenkorb" : "./?page=bestellung&schritt=2";
		
		//es wird das Popup erneut geöffnet und die Fehlermeldung angezeigt		
		$warenkorb1->zeige_fenster_bestellmenge_aendern_atrikel($pid, $result_ueberpruefung->get_fehlermeldung(), $link);
	}
}

//Entfernt einen Artikel aus dem Warenkorb
elseif (isset($_GET["aktion"]) && isset($_GET["aktionparam"]) && $_GET["aktion"]== "artikel-warenkorb-entfernen"){
	
	//Extrahiert die übermittelten Parameter für die Löschfunktion
	$parameter = explode(".", $_GET["aktionparam"]);
	
	//Instanz des Warenkorbs bilden
	$warenkorb1 = new warenkorb();
	
	//Zeigt die Sicherheitsfrage an
	if (count($parameter) == 2 && $parameter[0] == "sicherheitsfrage"){
		$warenkorb1->sicherheitsnachfrage_ein_artikel_auswarenkorb_entfernen($parameter[1]);
	}
	//Löscht den Artikel aus dem Warenkorb, wenn der Löschvorgang bestätigt wurde
	elseif (count($parameter) == 2 && $parameter[0] == "bestaetigt"){
		$warenkorb1->entferne_artikel_aus_warenkorb($parameter[1]);
	}
	//Löscht mehrere markierte Artikel aus dem Warenkorb
	elseif (count($parameter) > 1 && $parameter[0] == "bestaetigt_mehrere_pids"){
		$arr_pids = $parameter;
		unset($arr_pids[0]);
		$warenkorb1->mehrere_artikel_aus_warenkorb_entfernen($arr_pids);
	}
}

//Zeigt eine Popup-Fenster an, wo der Benutzer die Bestellmenge ändern kann
elseif (isset($_GET["aktion"]) && isset($_GET["aktionparam"]) && $_GET["aktion"]== "bestellmenge_warenkorbartikel_aendern"){
	//Instanz des Warenkorbs bilden
	$warenkorb1 = new warenkorb();
	
	//Extrahiert die übermittelten Parameter für die Löschfunktion
	$parameter = explode(".", $_GET["aktionparam"]);
	
	//wenn die gültige Menge an Parametern übertragen wurde
	if (count($parameter) == 1){
		$link = (isset($_GET['page']) && $_GET['page'] == "warenkorb") ? "./?page=warenkorb" : "./?page=bestellung&schritt=2";
		
		//Popup öffnen, wo der Benutzer die neue Menge eingeben kann
		$warenkorb1->zeige_fenster_bestellmenge_aendern_atrikel($parameter[0], "", $link);
	}
}
?>