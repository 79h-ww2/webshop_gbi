<?php
?>
<h2>
	Suchergebnisse
</h2>

<div class="auflistung_produkte" >
	<?php  for($i =0; $i < 10; $i++){?>
	<!--  Produkt -->
	<div class="listeneintrag_auflistung_produkte" title="Mountainbike Serious Rockaway 26&quot;" >
		<div class="listeneintrag_auflistung_produkte_content" >
			<div class="listeneintrag_auflistung_produkte_bild" >
				<img src="./Images/Produktbilder/1/liste.jpg" />
			</div>
			<div class="listeneintrag_auflistung_produkte_beschriftung"  >
					<div>
						<a class="listeneintrag_auflistung_produkte_beschriftungstext" href="#" >
							Mountainbike Serious Rockaway 26"
						</a>
					</div>
					<div class="listeneintrag_bewertung" >
						<img alt="Stern gef&uuml;llt" src="./Images/Design/stern_gefuellt.png" class="stern" />
						<img alt="Stern gef&uuml;llt" src="./Images/Design/stern_gefuellt.png" class="stern"/>
						<img alt="Stern gef&uuml;llt" src="./Images/Design/stern_gefuellt.png" class="stern" />
						<img alt="Stern gef&uuml;llt" src="./Images/Design/stern_gefuellt.png" class="stern"/>
						<img alt="Stern ungef&uuml;llt" src="./Images/Design/stern_ungefuellt.png" class="stern" />
						2000
												
						<?php 
							$sterne1= 1000;
							$sterne2= 0;
							$sterne3= 0;
							$sterne4= 1000;
							$sterne5= 0;
							include './Pages/popupBewertungProduktauflistung.php.inc'; 
						?>
					</div>
					<div class="menge_exemplare_gruen" >
						10 Exemplare verfügbar
					</div>
					<div class="listeneintrag_auflistung_kategorie" >
						Kategorie: Mountainbike
					</div>
					<div class="listeneintrag_auflistung_preis">
						600 &euro;
						<span class="listeneintrag_auflistung_preis_alt" >
							900 &euro;
						</span>
					</div>
					<div class="clear_right" >
					</div>
			</div>
		</div>
	</div>
	<!--  Produkt-Ende -->
	<?php } ?>
</div>

<!-- Leiste zur Auswahl der nächsten Seite -->
<div class="box_seitennavigation_ergebnis_seiten" >
</div>