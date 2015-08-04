<?php
$warenkorb1 = new warenkorb();

//wenn der Kunde noch nicht angemeldet ist, wird auf die Login-Seite weitergeleitet
if (!(isset($_SESSION['angemeldet']))){
	?>
		<h4>Bevor Sie mit der Bestellung fortfahren können, müssen Sie sich angemeldet haben.</h4>
<?php
		include 'Pages/Login.php.inc';
	}
	
	//wenn der Warenkorb leer ist
	elseif ($warenkorb1->menge_im_warenkorb() == 0){
?>
		<article class="middleContent content_einruecken" >
			<h2>Bestellvorgang</h2>
			<h3>Der Bestellvorgang kann nicht fortgesetzt werden, da der Warenkorb leer ist. Bitte füllen Sie den Warenkorb.</h3>
		</article>
<?php
	}
	//wenn der Kunde angemeldet ist und Waren im Warenkorb hat
	//Die Seiten für den Bestellvorgang werden angezeigt
	else{
		include_once 'Classes/bestellungen.php.inc';
		
		//lädt die aktuell zwischengespeicherte Bestellung
		$bestellungen = new Bestellungen();
		$aktuelle_bestellung = $bestellungen->get_zwischengespeicherte_bestellungseinstellungen();
		
		
		//zeigt die erste Seite des Bestellvorgangs an
		if (!isset($_GET['schritt'])){
			include_once 'Pages/bestellvorgang_schritt1.php.inc';
		}else{
			//zeigt die nächsten Seiten des Bestellvorgangs an
			switch ($_GET['schritt']){
				
				//erste Seite
				case '1':
					include_once 'Pages/bestellvorgang_schritt1.php.inc';
				break;
				
				//zweite Seite
				case '2':
					include_once 'Pages/bestellvorgang_schritt2.php.inc';
				break;
			}
		}
	}
?>