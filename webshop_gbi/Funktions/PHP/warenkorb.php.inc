<?php
$result_ueberpruefung = "";
if (isset($_POST['menge']) && isset($_POST['pid'])){
	
	$warenkorb1 = new warenkorb();
	
	//überprüft, ob die angegebene Menge, die in den Warenkorb gepackt werden soll gültig ist
	$result_ueberpruefung = $warenkorb1->ueberpruefe_eingegebene_menge_warenkorb($_POST['menge'], $_POST['pid']);

	$mengen_fehler = true; //Variable, die festhält, ob die Mengenangabe gültig war
	
	//wenn die Eingabe gültig ist
	if ( $result_ueberpruefung->get_fehlermeldung() == ""){
		
		$mengen_fehler = false; //speichert in der Variabel, das die Eingabe gültig war
		
		//den Artikel zum Warenkorb hinzufügen
		$warenkorb1->artikel_in_den_warenkorb_legen($_POST['pid'],$_POST['menge']);
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
}	
?>