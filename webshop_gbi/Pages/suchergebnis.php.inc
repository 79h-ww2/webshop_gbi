<?php
?>
<h2>
	Suchergebnisse zum Suchwort &quot;<?php if (isset($_GET['feld_suche_normal'])) echo htmlspecialchars($_GET['feld_suche_normal'],ENT_QUOTES,'UTF-8') ?>&quot;
</h2>

<?php
	include_once './Classes/bewertung.php.inc';
	include_once './Classes/artikel.php.inc';
	include_once './Classes/suche.php.inc';
	
	//führt die Suche durch
	if ( isset($_GET['feld_suche_normal'])){
		$suche = new Suche();
		$seite = isset($_GET['seite']) ? $_GET['seite'] : 1;
		$suche->nomale_suche_mit_ergebnisauflistung($_GET['feld_suche_normal'], $seite);
	}
	//kein Suchwort angegeben
	else{
		echo "<h2>Kein Suchwort eingegeben.</h2>";
	}
?>