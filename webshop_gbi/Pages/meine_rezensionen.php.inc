
    <?php
				include_once 'Classes/artikel.php.inc';
				include_once 'Classes/navigation.php.inc';
				include_once 'Classes/ArtikelDetails.php.inc';
				include_once 'Classes/Kommentar.php.inc';
				include_once 'Classes/Kunde.php.inc';
				?>
<form method="post"
	action="./?page=produkt&pid=<?php echo $_GET['pid']?>"
	id="produkt_rezensionen" name="form_produkt_rezensionen">
	    <?php
	    	$kommentare = new Kommentar ();
	    	$kunde = new Kunden();
	    	$kid = $kunde->get_kid_from_email($_SESSION['angemeldet']);
			$alle_kommentare = $kommentare->getKommentareByKId ($kid);
		?>
        <h2>
		    Meine Rezensionen
		</h2>
		
		<table class="rezensionen_tabelle">
			<thead>
			    <tr>
			    <th class="produkt_rezensionen_trennstrich rezension_eintrag_bezeichnung"> Bezeichnung </th>
			      <th class="produkt_rezensionen_trennstrich rezension_eintrag_ueberschrift"> Überschrift </th>
			      <th class="produkt_rezensionen_trennstrich rezension_eintrag_rezension"> Rezension </th>
			      <th class="produkt_rezensionen_trennstrich rezension_eintrag_bewertung"> Bewertung </th>
			    </tr>
			</thead>
			<tbody>
			<?php
			for($i = 0; $i < count ( $alle_kommentare ); $i ++) {
				$rezension = $alle_kommentare [$i];
			?>
			<tr class="rezension_eintrag_reihe">
			<td class="rezension_eintrag_bezeichnung"><?php echo $rezension->Bezeichnung; ?>
				<td class="rezension_eintrag_ueberschrift"><?php echo $rezension->Ueberschrift; ?>
				<td class="rezension_eintrag_rezension"><?php echo $rezension->Text; ?>
				<td class="rezension_eintrag_bewertung"><?php echo $rezension->bewertung; ?>
			</tr>
			<?php
			}
			?>
			</tbody>
		</table>
        
    </form>