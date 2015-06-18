<?php 
$zeilen = "";
$data = "";
$gesamtsumme = $gesamtbetrag = 0;
$datei = fopen ("produkte.csv", "r");
$daten = fgetcsv ($datei, 1000, ";");

while ($data = fgetcsv ($datei, 1000, ";")) {
	
	// Artikel (Anzahl) bearbeiten
	if (isset ($_GET["edit"][$data[0]])) {
		$artAnzahl = ($_GET["anz"][$data[0]]);
		$_SESSION[$data[0]] = $artAnzahl;
	}
	
	// Artikel löschen
	if (isset ($_GET["loeschen-$data[0]"])) {
		unset($_SESSION[$data[0]]);
	}
	
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
		<td>	
			<form action='$_SERVER[PHP_SELF]' method='get'>
			<input name='id' value='$data[0]' type='hidden'>
			<input name='anz[$data[0]]' type='text' value='$artAnzahl' class='count' pattern='^[0-9]{1,3}$'>
			<input name='edit[$data[0]]' type='submit' value='Ändern'>
			<input name='loeschen-$data[0]' type='submit' value='Artikel löschen'>
			</form>
		</td>
		<td>$artPreis €</td>
		<td>$artZwischen €</td>
	</tr>";
}

fclose ($datei);
?>