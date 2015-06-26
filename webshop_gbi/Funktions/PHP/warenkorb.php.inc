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
?>