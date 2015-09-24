<!-- Vorher schauen ob angemeldet: wenn nicht zum zum Loginfenster, wenn angemeldet schauen ob bereits Bewertung abgegeben wurde -->
<script src="http://code.jquery.com/jquery-1.11.2.min.js"></script>

<script type="text/javascript"
	src="./Funktions/JS/vorcheck_std_funktionen.js"></script>
<script type="text/javascript" src="./Funktions/JS/bewertung.js"></script>
<?php
include_once 'Classes/Kunde.php.inc';
include_once 'Classes/Kommentar.php.inc';
include_once 'Classes/ArtikelDetails.php.inc';
?>
<div class="startseite">
 <?php
	// wenn der Kunde noch nicht angemeldet ist, wird auf die Login-Seite weitergeleitet
	if (! (isset ( $_SESSION ['angemeldet'] ))) {
		?>
               <div class="topContentArtBewerten">
		<h4>Bevor Sie eine Bewertung abgeben können, müssen Sie sich anmelden!</h4>
	</div>
 <?php
		include 'Pages/Login.php.inc';
		
	}  // wenn er angemeldet ist bekommt der Kunde ein Popup zur Verwaltung seines Profils angezeigt
else {
	$profil = new Kunden ();
	$kommentare = new Kommentar ();
	// Kundennr bestimmen
	$kid = $profil->get_kid_from_email ( $_SESSION ['angemeldet'] );
	
	$eingabe_ungueltig_bewertung = isset ( $eingabe_ungueltig_bewertung ) ? $eingabe_ungueltig_bewertung : false;
		
		include_once './Classes/artikel.php.inc';
		?>

	<h2>Rezension</h2>
	<div class="artBewerten">
	
	<?php
	//Setzt die Action-Url zusammen
	$url = ( count($_GET) > 0 ) ?  "./?" : "./";
		
	$get_feldnamen = array_keys($_GET);
	for ( $i = 0; $i < count($_GET); $i++)
	{
		$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
		$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
		
		if ($feldname != "aktion" && $wert != "abmelden"){ //übernimmt nur die Get-Parameter, wenn sie nicht zum gleichzeitigen Abmelden führen
			if ( $i > 0) $url .= "&";
			$url .= $feldname."=".$wert;
		}
	}
	?>

		<form method="post" action="./?page=produkt&pid=<?php echo $_GET['pid']?>"
			onsubmit="return vorcheckEingabe_bewertung();" id="rezension"
			name="form_bewertung">
			<div class="sterne">
				<input id="sternbewertung" type="hidden" name="bewertung"
					value="<?php if ($eingabe_ungueltig_bewertung) { echo htmlspecialchars($_POST['bewertung'],ENT_QUOTES,'UTF-8');}else{ echo htmlspecialchars($kommentare->get_bewertung($kid, $_GET['pid']),ENT_QUOTES,'UTF-8'); } ?>">
				<ul class="sternliste">
					<li id="stern1" class="stern1"><a href="#"></a></li>
					<li id="stern2" class="stern2"><a href="#"></a></li>
					<li id="stern3" class="stern3"><a href="#"></a></li>
					<li id="stern4" class="stern4"><a href="#"></a></li>
					<li id="stern5" class="stern5"><a href="#"></a></li>

				</ul>
			</div>
			<div class="textfelder">

				<input class="uberschrift" type="text" name="ueberschrift" placeholder="Überschrift oder Zusammenfassung ihrer Rezension (erforderlich)" value="<?php if ($eingabe_ungueltig_bewertung) { echo htmlspecialchars($_POST['ueberschrift'],ENT_QUOTES,'UTF-8');}else{ echo htmlspecialchars($kommentare->get_ueberschrift($kid, $_GET['pid']),ENT_QUOTES,'UTF-8'); } ?>" />

				<textarea class="rezension" name="rezension" placeholder="Schreiben Sie hier ihre Rezension (erforderlich)"><?php if ($eingabe_ungueltig_bewertung) { echo htmlspecialchars($_POST['rezension'],ENT_QUOTES,'UTF-8');}else{ echo htmlspecialchars($kommentare->get_rezension($kid, $_GET['pid']),ENT_QUOTES,'UTF-8'); } ?></textarea>
			</div>
			
			<input type="hidden" name="pid" value="<?php echo $_GET['pid']?>"/>
			<input type="hidden" name="type" value="kommentar" />
			<input class="sendebutton" type="submit" name="action" value="Senden" />
			<p class="fehlermeldung_bewertung" id="fehlermeldung_bewertung">
        <?php
		// zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
		if ($eingabe_ungueltig_bewertung) {
			echo htmlspecialchars ( $eingabe_check_result_bewertung->get_fehlermeldung(), ENT_QUOTES, 'UTF-8' );
		}
		?>
                				            </p>
		</form>
	</div>
    <?php
		}
	?>
	</div>