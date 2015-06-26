
<div class="popupWarenkorb" >
	<div class="haken_sprechblase" >
	</div>
	<div class="contentPopupWarenkorb" >
	<?php 
	
	$warenkorb1 = new warenkorb();
	if($warenkorb1->menge_im_warenkorb()>0)
	{
		
	?>
		
		<div class="popupArtikelWarenkorb" >
			<div class="aktuelleArtikelimWarenkorb" >
			<div class="ArtikelbildWarenkorb UeberschriftWarenkorb"> Bild </div>
			<div class="ArtikelnameWarenkorb UeberschriftWarenkorb"> Name </div>
			<div class="ArtikelmengeWarenkorb UeberschriftWarenkorb"> Menge </div>
					
				
		</div><?php
		$Artikel = $warenkorb1->artikel_im_warenkorb_anzeigen();
for ($i = 0; $i < count($Artikel) && $i<4; $i++){
	$AktuellerArtikel = $Artikel[$i];
	?> <div class="aktuelleArtikelimWarenkorb" >
	<div class="ArtikelbildWarenkorb "> <img class="Artikelbild" alt="Artikelbild" title="<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8' );?>" src="<?php echo $AktuellerArtikel->get_artikelbild();?>" > </div>
			<div class="ArtikelnameWarenkorb "> <a class="ArtikelnameWarenkorbhyper" href="./?page=produkt&pid=<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8');?>"><?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8');?> </a> </div> 
			<div class="ArtikelmengeWarenkorb "> <?php echo htmlspecialchars ( $AktuellerArtikel->get_menge(), ENT_QUOTES, 'UTF-8' );?> </div> </div>
			<?php

	 }
	 echo "</div>";
	}
		else { 
		echo "<div id=\"keineArtikelimWarenkorb\">Keine Artikel im Warenkorb vorhanden </div>";
		}
		?>
		<div class="WarenkorbButtonPopup">
<a href=".?page=datenschutz" title="Warenkorb anzeigen" class="link_button" id="" >
					Gesamter Warenkorb (<?php echo $warenkorb1->menge_im_warenkorb();
				?>)
				</a>
				<a href=".?page=datenschutz" title="zur Kasse" class="link_button" id="" >
					zur Kasse	
				</a>
				</div>
	</div>
</div>