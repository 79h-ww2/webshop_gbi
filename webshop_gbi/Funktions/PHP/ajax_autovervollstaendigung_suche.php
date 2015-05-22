<?php
	//überprüft, ob Werte übermittelt wurden, wonach gesucht werden soll
	if (isset($_GET['modus']) && isset($_GET['suchwort']) && $_GET['suchwort'] != "" && $_GET['modus'] != ""){
		
		//Suchobjekt instanzieren
		include_once '../../Classes/datenbank.php.inc';
		include_once '../../Classes/suche.php.inc';
		$suche = new Suche();
		
		//es handelt sich um eine Normale Suche
		if ($_GET['modus'] == 'normal'){
			//fragt bei der Datenbank nach der Autovervollständigung an und gibt das Ergebnis aus
			echo $suche->normale_suche_autovervollstaendigung($_GET['suchwort']);
		}
	}
?>