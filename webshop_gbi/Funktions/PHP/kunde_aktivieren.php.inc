<?php
	//Kunde wird durch den Aktivierungslink aktiviert
	include_once './Classes/Kunde.php.inc';
	$kunde = new Kunden();
	$kunde->aktiviere_kunde_durch_aktivierungs_code($_GET['account-activate']);
?>