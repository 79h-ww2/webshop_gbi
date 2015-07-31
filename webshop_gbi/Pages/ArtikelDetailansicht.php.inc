<?php include_once 'Classes/ArtikelDetails.php.inc';?>
<div class = "startseite">
<article class="detailContent">
        
        <?php 
        
        //zeigt die Artikelseite nur an, wenn eine PID übergeben wurde
        if(isset($_GET['pid'])){
		
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
    		<h3><a href="#" title="Mountainbikes">Mountainbike</a></h3>
    		
    		<div class="menge_exemplare_gruen">
    			<?php 
		
					$artikelDetails = new ArtikelDetails();
					
					$artikel = $artikelDetails->beschreibungAnzeigen($_GET['pid']);
					
					
					echo '<span id="exemplare_auf_lager" >'.htmlspecialchars($artikel->Menge,ENT_QUOTES,'UTF-8').'</span> Exemplare verfügbar';
					
				?>
    		</div>
    		
    		<div class="warenkorbFeld">
    			<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
    			</script>
    			<script type="text/javascript" src="Funktions/JS/vorcheck_warenkorb.js">
    			</script>
    			<?php
    				//Variable, die anzeigt, ob die vor einen Submit angegeben Menge gültig war (Serverseitig nach den Submit überprüft)
    				$mengen_fehler = (isset($mengen_fehler)) ? $mengen_fehler : false;
    			?>
	    		<form name="from_warenkorb"  action="./?page=produkt&pid=<?php echo htmlspecialchars($_GET['pid'],ENT_QUOTES,'UTF-8');?>" method="post" onsubmit="return eintrag_in_warenkorb_vorcheck();"  >
				<label for="menge">Menge:</label>
				<input class ="textfeld" type="text" name="menge" 
				<?php 
					//Mariert das Fenster rot, wenn der Mengenwert falsch war
					if($mengen_fehler && isset($_POST['menge'])){
						echo 'style="border-style: solid; border-color:red;" value="'.htmlspecialchars($_POST['menge'],ENT_QUOTES,'UTF-8').'" ';
					}
				?> />
				<input class ="buttonInWarenkorb" type="submit" value="In den Warenkorb" />
				<input type="hidden" name="pid" value="<?php echo htmlspecialchars($_GET['pid'],ENT_QUOTES,'UTF-8');  ?>" />
				<input type="hidden" value="neuerArtikelimWarenkorb" name="type"/>
				<div id="fehlermeldung_warenkorb">
					<?php
						//Wenn die Mengenangabe falsch war, wird eine Fehlermeldung angezeigt
						if ($mengen_fehler && isset($result_ueberpruefung)){
							echo htmlspecialchars($result_ueberpruefung->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
						}
					?>
				</div>
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
    
    <?php }else{echo "Keine Artikelnummer übergeben !!!";} ?>
</article>
</div>
