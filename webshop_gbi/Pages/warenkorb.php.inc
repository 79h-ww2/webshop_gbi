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
		<form  method="post" action="" name="form_warenkorb_auflistung" id="form_warenkorb_auflistung" >
			<div class="auflistung_warenkorb" >
				<div class="aktuelleArtikelimWarenkorb" >
					<div class="ArtikelmarkiercheckboxWarenkorb UeberschriftWarenkorb">
					</div>
					<div class="ArtikelbildWarenkorb UeberschriftWarenkorb">Bild</div>
					<div class="ArtikelnameWarenkorb UeberschriftWarenkorb">Name</div>
					<div class="ArtikelmengeWarenkorb UeberschriftWarenkorb">Menge</div>
					<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb">Einzelpreis</div>
					<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb">Gesamtpreis</div>
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
						if ( $z > 0) $adresse_links .=  "&";
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
							<input <?php if (isset($_GET['aktion']) && $_GET['aktion'] == 'alle_markieren' ) echo "checked"; ?> type="checkbox" name="check_warenkorb_artikel_<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>" value="<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>" title="Den Artikel &quot;<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8');?>&quot; markieren"  />
						</div>
						<div class="ArtikelbildWarenkorb "> 
							<a class="ArtikelnameWarenkorbhyper" href="./?page=produkt&pid=<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>"><img class="Artikelbild" alt="Artikelbild" title="<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8' );?>" src="<?php echo $AktuellerArtikel->get_artikelbild();?>" ></a>
						</div>
						<div class="ArtikelnameWarenkorb "> <a class="ArtikelnameWarenkorbhyper" href="./?page=produkt&pid=<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>"><?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8');?> </a> </div> 
						<div class="ArtikelmengeWarenkorb ">
							<?php echo htmlspecialchars ( $AktuellerArtikel->get_menge(), ENT_QUOTES, 'UTF-8' );?>
							<a href="<?php echo $adresse_links."aktion=bestellmenge_warenkorbartikel_aendern&aktionparam=".htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>" title="Menge &auml;ndern" class="link_menge_aendern" ></a>
						</div>
						<div class="ArtikelPreisWarenkorb"><?php echo number_format($AktuellerArtikel->get_einzelpreis_artikel(),2, ",", ""); ?> &euro;</div>
						<div class="ArtikelPreisWarenkorb"><?php echo number_format($AktuellerArtikel->get_gesamtpreis_artikel(),2, ",", ""); ?> &euro;</div>
						<div class="ArtikelLoeschenWarenkorb">
							<a href="<?php echo $adresse_links."aktion=artikel-warenkorb-entfernen&aktionparam=sicherheitsfrage.".htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>" title="Artikel aus dem Warenkorb entfernen" class="loeschen_link" >
							</a>
						</div>
					</div>
			<?php
				}
			?>
				<div class="aktuelleArtikelimWarenkorb" >
					<div class="ArtikelmarkiercheckboxWarenkorb ArtikelwarenkorbSummenZeile" ></div>
					<div class="ArtikelbildWarenkorb ArtikelwarenkorbSummenZeile"></div>
					<div class="ArtikelnameWarenkorb ArtikelwarenkorbSummenZeile"></div> 
					<div class="ArtikelmengeWarenkorb ArtikelwarenkorbSummenZeile"></div>
					<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb ArtikelwarenkorbSummenZeile">Summe:</div>
					<div class="ArtikelPreisWarenkorb ArtikelwarenkorbSummenZeile"><?php echo number_format($warenkorb1->get_gesamtpreis_artikel_im_warenkorb(),2, ",", ""); ?> &euro;</div>
					<div class="ArtikelLoeschenWarenkorb ArtikelwarenkorbSummenZeile"></div>
				</div>
			</div>
			<div class="bereich_button_warenkorb_volle_uebersicht" >
				<a class="warenkorb_alle_markieren_link" href="<?php 
					//Link, um alle Artikel zu markieren bzw. demarkieren
					$aufschrift = "Alle Artikel markieren"; 
					if (isset($_GET['aktion']) && $_GET['aktion'] == 'alle_markieren' ) {
						echo "./?page=warenkorb"; $aufschrift = "Alle Artikel demarkieren";
					} else{ 
						echo $adresse_links."aktion=alle_markieren";
					} ?>" title="<?php echo $aufschrift ?>" ><?php echo $aufschrift; ?></a>
					
				<div class="button_warenkorb_volle_uebersicht_rechts_ausrichten" >
					<input type="hidden" value="markierung_loeschen_warenkorb" name="type" /> 
				
					<input type="submit" name="submit" value="Markierte Artikel l&ouml;schen" title="Markierte Artikel l&ouml;schen" />
					<a href="#" title="Zur Kasse" class="grauer_link_button" >Zur Kasse</a>
				</div>
				<div class="clear_right" ></div>
			</div>
		</form>
	<?php
		}
		$msg = new Meldungsfenster();
		//$msg->erstelleHTMLQuelltextTextinputbox("Test", "Test123","Dieses ist ein Test", "Hallo", "hallo", "Ok", "Abbrechen", "#", "Post", true, "");
	?>
</article>