<?php
$warenkorb1 = new warenkorb();
?>
<article class="middleContent" >
	<h1>Warenkorb</h1>
	<?php
		//Meldung, die angibt, wie viele Artikel sich im Warenkorb befinden.
		$meldung_ware_im_warenkorb = ($warenkorb1->menge_im_warenkorb() > 0) ? "Im Warenkorb befinden sich ".$warenkorb1->menge_im_warenkorb()." Artikel:" : "Der Warenkorb ist leer.";
		echo "<h3>$meldung_ware_im_warenkorb</h3>";
		
		//listet den Inhalt des Warenkorbs auf
		if ($warenkorb1->menge_im_warenkorb() > 0){
			$Artikel = $warenkorb1->artikel_im_warenkorb_anzeigen();
	?>
		<form class="auflistung_warenkorb" method="post" action="" name="form_warenkorb_auflistung" id="form_warenkorb_auflistung" >
			<div class="aktuelleArtikelimWarenkorb" >
				<div class="ArtikelmarkiercheckboxWarenkorb UeberschriftWarenkorb">
					<!--  zeigt eine Checkbox an, womit jeder Artikel markiert werden kann, wenn JavaScript aktiviert ist -->
					<script type="text/javascript">document.write('<input type="checkbox" name="check_all_warenkorb"  title="Alle Artikel markieren" onclick="WarenkorbAlleArtikelMarkieren();" />');</script>
				</div>
				<div class="ArtikelbildWarenkorb UeberschriftWarenkorb">Bild</div>
				<div class="ArtikelnameWarenkorb UeberschriftWarenkorb">Name</div>
				<div class="ArtikelmengeWarenkorb UeberschriftWarenkorb">Menge</div>
				<div class="ArtikelLoeschenWarenkorb UeberschriftWarenkorb"></div>
			</div>
			<script type="text/javascript" src="Funktions/JS/vorcheck_warenkorb.js" ></script>
			<?php
			
			//erstellt den Adressenanfang für den Löschen und Berarbeitungslink
			$adresse_links = "./?";
			$get_feldnamen = array_keys($_GET);
			$z = 0;
			for ( $i = 0; $i < count($_GET); $i++)
			{
				$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
				$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
			
				//übernimmt die Parameter von der Adressenleiste, die nicht als Feldname "aktion" und "aktionparam" heißen
				if ( $feldname != "aktion" && $feldname != "aktionparam" ){
					if ( $z > 0) $adresse_no_script .=  "&";
					$adresse_links .= $feldname."=".$wert;
					$z++;
				}
			}
			if ($z > 0) $adresse_links.= "&";	
			
			//Listet die Produkte des Warenkorbs auf
			$Artikel = $warenkorb1->artikel_im_warenkorb_anzeigen();
			for ($i = 0; $i < count($Artikel) && $i<4; $i++){
				$AktuellerArtikel = $Artikel[$i];
				?> 
				<div class="aktuelleArtikelimWarenkorb" >
					<div class="ArtikelmarkiercheckboxWarenkorb" >
						<input type="checkbox" name="check_warenkorb_artikel" value="<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>" title="Den Artikel &quot;<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8');?>&quot; markieren"  />
					</div>
					<div class="ArtikelbildWarenkorb "> 
						<a class="ArtikelnameWarenkorbhyper" href="./?page=produkt&pid=<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>"><img class="Artikelbild" alt="Artikelbild" title="<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8' );?>" src="<?php echo $AktuellerArtikel->get_artikelbild();?>" ></a>
					</div>
					<div class="ArtikelnameWarenkorb "> <a class="ArtikelnameWarenkorbhyper" href="./?page=produkt&pid=<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>"><?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8');?> </a> </div> 
					<div class="ArtikelmengeWarenkorb ">
						<?php echo htmlspecialchars ( $AktuellerArtikel->get_menge(), ENT_QUOTES, 'UTF-8' );?>
						<a href="#" title="Menge &auml;ndern" class="link_menge_aendern" ></a>
					</div>
					<div class="ArtikelLoeschenWarenkorb">
						<a href="<?php echo $adresse_links."aktion=artikel-warenkorb-entfernen&aktionparam=sicherheitsfrage.".htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>" title="Artikel aus dem Warenkorb entfernen" class="loeschen_link" >
						</a>
					</div>
				</div>
		<?php
			}
		?>
		</form>
	<?php
		}
	?>
</article>