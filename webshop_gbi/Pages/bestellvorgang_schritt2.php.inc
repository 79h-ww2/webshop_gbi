<article class="middleContent content_einruecken" >
	<h2>Bestellvorgang: Schritt 2 von 6</h2>
	<form action="./?page=bestellung&schritt=2" name="form_warenkorb" method="post" id="form_bestellung" >
		<h2>Warenkorb</h2>
		<div class="reg_box_aufteilung" >
			<div class="warenkorb_iconbereich" ></div>
			<div class="form_content" >
				
				
				
				<div class="auflistung_warenkorb" >
					<div class="aktuelleArtikelimWarenkorb" >
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
							<div class="ArtikelbildWarenkorb "> 
								<img class="Artikelbild" alt="Artikelbild" title="<?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8' );?>" src="<?php echo $AktuellerArtikel->get_artikelbild();?>" >
							</div>
							<div class="ArtikelnameWarenkorb "><?php echo htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8');?></div> 
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
						<div class="ArtikelbildWarenkorb ArtikelwarenkorbSummenZeile"></div>
						<div class="ArtikelnameWarenkorb ArtikelwarenkorbSummenZeile"></div> 
						<div class="ArtikelmengeWarenkorb ArtikelwarenkorbSummenZeile"></div>
						<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb ArtikelwarenkorbSummenZeile">Zwischensumme:</div>
						<div class="ArtikelPreisWarenkorb ArtikelwarenkorbSummenZeile"><?php echo number_format($warenkorb1->get_gesamtpreis_artikel_im_warenkorb(),2, ",", ""); ?> &euro;</div>
						<div class="ArtikelLoeschenWarenkorb ArtikelwarenkorbSummenZeile"></div>
					</div>
					<?php 
						//Berechung der Versandkosten
						$versandart = $aktuelle_bestellung->get_versandart();
						$versandkosten = 0;
						
						if ($versandart == "standardversand" && $warenkorb1->get_gesamtpreis_artikel_im_warenkorb() <= 25 ){
							$versandkosten= 4;
						}elseif ($versandart == "expressversand"){
							$versandkosten=13;
						}
					?>
					<div class="aktuelleArtikelimWarenkorb" >
						<div class="ArtikelbildWarenkorb"></div>
						<div class="ArtikelnameWarenkorb"></div> 
						<div class="ArtikelmengeWarenkorb"></div>
						<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb">Versand:</div>
						<div class="ArtikelPreisWarenkorb"><?php echo number_format($versandkosten,2, ",", ""); ?> &euro;</div>
						<div class="ArtikelLoeschenWarenkorb"></div>
					</div>
					
					<div class="aktuelleArtikelimWarenkorb" >
						<div class="ArtikelbildWarenkorb ArtikelwarenkorbSummenZeile"></div>
						<div class="ArtikelnameWarenkorb ArtikelwarenkorbSummenZeile"></div> 
						<div class="ArtikelmengeWarenkorb ArtikelwarenkorbSummenZeile"></div>
						<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb ArtikelwarenkorbSummenZeile">Summe:</div>
						<div class="ArtikelPreisWarenkorb ArtikelwarenkorbSummenZeile"><?php echo number_format($versandkosten + $warenkorb1->get_gesamtpreis_artikel_im_warenkorb(),2, ",", ""); ?> &euro;</div>
						<div class="ArtikelLoeschenWarenkorb ArtikelwarenkorbSummenZeile"></div>
					</div>
					
				</div>
					
				<p class="text_fehlermeldung" ></p>
				<div class="button_warenkorb_volle_uebersicht_rechts_ausrichten" >	
					<a href="./" title="Abbrechen" class="grauer_link_button" >Abbrechen</a>
					<a href="./?page=bestellung" title="Zurück" class="grauer_link_button" >Zurück</a>
					<a href="./?page=bestellung&schritt=3" title="Weiter" class="grauer_link_button" >Weiter</a>
				</div>
				<div class="clear_right" ></div>	
					
			</div>
		</div>
	</form>
</article>