<?php 
include_once './Classes/artikel.php.inc';
include_once 'Classes/navigation.php.inc';
if (isset($_GET["PTId"])) {
	if ($_GET["PTId"] == 1 && isset($_GET ["bauart"])) {
		$seite = isset($_GET['seite']) ? $_GET['seite'] : 1;
		$navi  = new Navigation();
		$navi->FahrradbauartAuflisten($_GET ["bauart"], $seite);
	}
	else {
			$seite = isset($_GET['seite']) ? $_GET['seite'] : 1;
			$navi  = new Navigation();
			$navi->WeitereProdukteAuflisten($_GET ["PTId"], $seite);
	}
}
?>