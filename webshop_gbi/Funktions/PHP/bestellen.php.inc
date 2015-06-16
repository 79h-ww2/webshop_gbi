<?php 
$zeilen = "";
$data = "";
$gesamtsumme = $gesamtbetrag = 0;
$datei = fopen ("produkte.csv", "r");
$daten = fgetcsv ($datei, 1000, ";");

while ($data = fgetcsv ($datei, 1000, ";")) {
	
	if (!isset ($_SESSION[$data[0]])) {
		$artNr = $data[0];
		continue;
	}
	
	$artNr 				= $data[0];
	$artBezeichnung		= $data[1];
	$artPreis				= str_replace(",", ".", $data[2]);
	$artAnzahl			= $_SESSION[$data[0]];
	$artZwischensumme	= number_format ($artAnzahl * $artPreis, 2,",", "");
	$artZwischen			= number_format ($artAnzahl * str_replace(",", ".", $artPreis), 2, ",", ".");	
	$gesamtsumme		= str_replace(",", ".", $gesamtsumme) + str_replace(",", ".", $artZwischensumme);
	
	// Artikel zeilenweise ausgeben
	$zeilen.="
		<tr>
			<td>$artNr</td>
			<td>$artBezeichnung</td>
			<td>$artPreis €</td>
			<td>$artAnzahl Stück</td>
			<td>$artZwischen €</td>
		</tr>";
}

fclose ($datei);
?>

<table class="shoppingCart final">
	<tr>
		<th>Artikelnummer</th>
		<th>Bezeichnung</th>
		<th>Einzelpreis</th>
		<th>Anzahl</th>
		<th>Warensumme</th>
	</tr>
<?php echo $zeilen; ?>
	<tr>
		<td class="gesamt" colspan="4">Gesamtsumme:</td>
		<td class="summe" ><?php echo number_format ($gesamtsumme ,2 ,"," ,".")." €"; ?></td>
	</tr>
	<tr class="lastItem">
		<td colspan="5">
			<a class="linkArrowLeft linkBackward" href="warenkorb.php" title="Möchten Sie ihren Warenkorb bearbeiten?">Zurück zum Warenkorb <span>(Schritt 2)</span></a>
			<br>
			<a class="linkArrowLeft linkBackward" href="index.php" title="Nutzen Sie diese Gelegenheit weitere starke Artikel zum einmaligen Sonderpreis zu erhalten!">Weitere Artikel einkaufen <span>(Schritt 1)</span></a>
		</td>
	</tr>
</table>

<!-- Formular (Kundendaten) -->
<?php
$sep = ";";
$webmaster = $_POST["email"];

if (isset ($_POST["formular"])) {
	include_once ("formular.html");
}

// Überprüfung der Eingabefelder
elseif (isset ($_POST["absenden"]) && (empty ($_POST["title"]) || (empty ($_POST["name"]) || (empty ($_POST["firstname"]) || 
(empty ($_POST["street"]) || (empty ($_POST["number"]) || (empty ($_POST["zip"]) || (empty ($_POST["city"]) || 
(empty ($_POST["country"]) || (empty ($_POST["email"]) || empty ($_POST["paymentMethod"]))))))))))) { 
	
	// Fehlermeldung
	echo "<div class='hint alert'>
		Bitte füllen Sie alle Felder aus!
	</div>";
	include_once ("formular.html");
}

	// Meldung/Anzeige nach Versand: Ausgabe der Formulareingaben
	if (isset($_POST["absenden"])) {
		echo "<div class='sentData'>\n\t\t";
		echo "Anrede: <span>".$_POST["title"]."</span><br>\n\t\t";
		echo "Vorname: <span>".ucfirst($_POST["firstname"])."</span><br>\n\t\t";
		echo "Name: <span>".ucfirst($_POST["name"])."</span><br>\n\t\t";
		echo "Straße: <span>".ucfirst($_POST["street"])." ".($_POST["number"])."</span><br>\n\t\t";
		echo "Wohnort: <span>".($_POST["zip"])." ".ucfirst($_POST["city"])."</span><br>\n\t\t";
		echo "E-Mail: <span>".$_POST["email"]."</span><br>\n\t\t";
		echo "Zahlweise: <span>".$_POST["paymentMethod"]."\n\t
		</div>";
	}
	
	else 
	{
	include_once ("formular.html");
}
?>