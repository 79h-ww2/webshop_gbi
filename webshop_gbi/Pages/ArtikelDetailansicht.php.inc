<?php include_once 'Classes/ArtikelDetails.php.inc';?>
<div class = "startseite">
<article class="detailContent">
        
        <?php 
		
		$artikelDetails = new ArtikelDetails();
		
		$artikel = $artikelDetails->beschreibungAnzeigen($_GET['pid']);
		
		
		echo '<h2>'.htmlspecialchars($artikel->Bezeichnung,ENT_QUOTES,'UTF-8').'</h2>';
		
		?>

    <content>
    
    <div class="detailLeft"> 
    	Detailansichten:
    		<div class="detailCell">
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellMinatur" />
    		
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellMinatur" />
    		
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellMinatur" />
    		
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellMinatur" />
    		
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellMinatur" />
    		</div>
    </div>
    
    	<div class="detailMiddle">
    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mountainbike" class="BildMustermodell" />
    	</div>
    	
    	
    	<div class="detailContentText">
    		<?php 
		
					$artikelDetails = new ArtikelDetails();
					
					$artikel = $artikelDetails->beschreibungAnzeigen($_GET['pid']);
					
									
					echo  '<span id="bauart" > <h3><a href="#" title="Mountainbikes">'.htmlspecialchars($artikel->bauart,ENT_QUOTES,'UTF-8').'</a> </h3> </span>'
					
					?>
    		
    		
    		
    		<div class="menge_exemplare_gruen">
    			<?php 
		
					$artikelDetails = new ArtikelDetails();
					
					$artikel = $artikelDetails->beschreibungAnzeigen($_GET['pid']);
					
					
					echo '<span id="exemplare" >'.htmlspecialchars($artikel->Menge,ENT_QUOTES,'UTF-8').'</span> Exemplare verfügbar';
					
					?>
    		</div>
    		
    		
    		<div class="listeneintrag_auflistung_preis" >
    			<?php 
		
					$artikelDetails = new ArtikelDetails();
					
					$artikel = $artikelDetails->beschreibungAnzeigen($_GET['pid']);
					
					
					echo '<span id="preis" >'.htmlspecialchars($artikel->Preis,ENT_QUOTES,'UTF-8').'</span> €';
					
					?>
    		</div>
    		
    		<div class="warenkorbFeld">
    			<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
    			</script>
    			<script type="text/javascript" src="Funktions/JS/vorcheck_warenkorb.js">
    			</script>
	    		<form name="from_warenkorb"  action="./?page=produkt&pid=<?php echo htmlspecialchars($_GET['pid'],ENT_QUOTES,'UTF-8');?>" method="post" onsubmit="return eintrag_in_warenkorb_vorcheck();"  >
				<label for="menge">Menge:</label>
				<input class ="textfeld" type="text" name="menge" />
				<input class ="buttonInWarenkorb"type="submit" value="In den Warenkorb" />
				<input type="hidden" name="pid" value="<?php echo htmlspecialchars($_GET['pid'],ENT_QUOTES,'UTF-8');  ?>" />
				<input type="hidden" value="neuerArtikelimWarenkorb" name="type"/>
				<div id="fehlermeldung_warenkorb"></div>
				</form>
    		</div>
    		
    		<p><strong>Eigenschaften</strong></p>
    		
    		
	        <ul type="disc">
		        <li>32 Gänge + Rückwärtsgang</li>
		        <li>Einparkassistent</li>
		        <li>Allradantrieb</li>
		        <li>Navigationssystem</li>
		        <li>Tagfahrlicht</li>
		        <li>Gratis Wackedackel für jedes Fahrrad :D</li>
	        </ul>
    	</div>
    	
    </content>
</article>

<article class="middleContent">
    <header>
        <h2>Artikelbeschreibung</h2>
    </header>
    
    <footer>
        
    </footer>
    
    <content>
    	
    	<!-- <p class="middleContentText">
    	Das smarte Rockaway ist ein Freizeitbike, das überall zu Hause ist - von Alltagsstrecken in der Stadt bis auf
    	Ausflugstouren übers Land. Ob auf Feld- und Waldwegen, auf Schotterstraßen oder asphaltierten Radwegen, das Rockaway
    	bringt seinen Fahrer zuverlässig und flott ans Ziel. Auf kleinen Anstiegen findet sich mit der zuverlässigen Shimano
    	Altus 21 Gang Schaltung schnell die passende Übersetzung. In Kombination mit Shimano Umwerfer und Shimano Zahnkranz
    	sorgt dieser Antrieb für nachhaltigen Fahrspaß.
		<br>
		Die Shimano Schalt- Bremshebelkombination bietet dabei gerade Einsteigern vor allem Komfort und Sicherheit.
		Die Federgabel von Suntour schluckt kleine Unebenheiten mühelos weg und macht zusammen mit den griffigen Reifen selbst
		holprige Pisten zum Vergnügen. Dank des komfortablen Sportsattels und der gemäßigt sportlichen Sitzposition, die
		Rahmengeometrie, Vorbau und Riserlenker vorgeben steigt der Rockawayfahrer auch nach längeren Ausflügen noch
		entspannt vom Rad. Stabile Laufräder mit Hohlkammerfelgen, ein wartungsfreies Patronen Innenlager und gut greifende
		V-Brakes runden das Bild ab. Mit dem Rockaway steht für einen wirklich günstigen Preis nicht nur ein guter Rahmen mit
		einer ausgewogenen Ausstattung zur Verfügung, sondern der Fahrspaß ist bereits schon all inklusive.
		</p> -->
		
		<?php 
		
		$artikelDetails = new ArtikelDetails();
		
		$artikel = $artikelDetails->beschreibungAnzeigen($_GET['pid']);
		
		
		echo '<p class="middleContentText">'.htmlspecialchars($artikel->Beschreibung,ENT_QUOTES,'UTF-8').'</p>';
		
		?>
		        
    </content>
    <a href="./?page=artBewerten" title="ArtikelBewerten">Artikel bewerten</a>
</article>
</div>
