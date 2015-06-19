<?php
?>

<?php
	include_once './Classes/bewertung.php.inc';
	include_once './Classes/artikel.php.inc';
	include_once './Classes/suche.php.inc';
	
	//führt die Suche durch
	if ( isset($_GET['feld_suche_normal'])){
?>
		<h2>
			Suchergebnisse zum Suchwort &quot;<?php if (isset($_GET['feld_suche_normal'])) echo htmlspecialchars($_GET['feld_suche_normal'],ENT_QUOTES,'UTF-8') ?>&quot;
		</h2>
<?php
		
		$suche = new Suche();
		$seite = isset($_GET['seite']) ? $_GET['seite'] : 1;
		$suche->nomale_suche_mit_ergebnisauflistung($_GET['feld_suche_normal'], $seite);
	}
	elseif (isset($_GET['marke']) && isset($_GET['produktbezeichnung']) &&  isset($_GET['preis_von']) && isset($_GET['preis_bis']) && isset($_GET['kategorie']) && isset($_GET['bauart']) && isset($_GET['bauvariante']) && isset($_GET['artikelnr'])){
?>
		<h2>
			Suchergebnisse zur erweiterten Suche
		</h2>
<?php
		
		$suche = new Suche();
		$seite = isset($_GET['seite']) ? $_GET['seite'] : 1;
		$suche->erweiterte_suche_mit_ergebnisauflistung($_GET['produktbezeichnung'], $_GET['preis_von'], $_GET['preis_bis'], $_GET['kategorie'], $_GET['bauart'], $_GET['bauvariante'], $_GET['artikelnr'], $_GET['marke'], $seite);
	}
	//kein Suchwort angegeben
	else{
		echo "<h2>Kein Suchwort eingegeben.</h2>";
	}
?>