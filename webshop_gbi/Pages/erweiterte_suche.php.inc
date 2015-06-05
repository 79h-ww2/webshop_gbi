    <?php
    	include_once 'Classes/artikel.php.inc';
    	include_once 'Classes/navigation.php.inc';
    ?>
    <script type="text/javascript" src="./Funktions/JS/vorcheck_erweiterte_suche.js" >
    </script>
    <form method="post" action="#" onsubmit="return vorcheckEingabe();" id="suche_erweitert" name="form_suche_erweitert" >
        <h2>
		     Erweiterte Suche
		</h2>
        <div class="reg_box_aufteilung" >
        	<div class="TableRow_reg" >
	        	<div class="suche_box_iconbereich" >
	        	</div> 
	        
		        <div class="form_content" >
		        
		            <p class="reg_form_zeile" >
		                <label for="produktbezeichnung">Produkt- bezeichnung:</label>
		                <input type="text" name="produktbezeichnung"  value="" class="lang_reg" />
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label >Preispanne:</label>
		                <label for="preis_von" class="label_preisspanne" >von:</label>
		                <input type="text" name="preis_von" value="" class="bereich_preis" /> &euro;
		                <label for="preis_bis" class="label_preisspanne kleiner_abstand_vertikal" >bis:</label>
		                <input type="text" name="preis_bis" value="" class="bereich_preis" /> &euro;
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="kategorie">Kategorie:</label>
		                <select name="kategorie"   class="lang_reg">
		                	<option>alle</option>
		                	<?php
		                		$navi = new Navigation();
		                		$kategorien = $navi->erstelle_array_kategorien();
		                		foreach ($kategorien as $kategorie){
		                			if ($kategorie->Bezeichnung != 'Fahrrad'){
		                				echo "<option>".htmlspecialchars($kategorie->Bezeichnung,ENT_QUOTES,'UTF-8')."</option>\n";
		                			}else{
		                				echo "<option>".htmlspecialchars($kategorie->Bezeichnung,ENT_QUOTES,'UTF-8')."</option>\n";
		                			}
		                		}
		                	?>
		                </select>
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="bauart">Bauart:</label>
		                <select name="bauart"   class="lang_reg">
		                	<option>alle</option>
		                	<?php
		                		$navi = new Navigation();
		                		$bauarten = $navi->erstelle_array_bauart();
		                		foreach ($bauarten as $bauart){
		                			echo "<option>".htmlspecialchars($bauart->Bezeichnung,ENT_QUOTES,'UTF-8')."</option>\n";
		                		}
		                	?>
		                </select>
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="bauvariante">Bauvariante:</label>
		                <select name="bauvariante"  class="lang_reg">
		                	<option>alle</option>
		                	<option>Herrenrad</option>
		                	<option>Frauenrad</option>
		                </select>
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="artikelnr">Artikelnummer:</label>
		                <input type="text" name="artikelnr"  value="" class="lang_reg" />
		            </p>
		            
		            <p class="text_fehlermeldung" id="suche_fehlermeldung" >
		            </p>           
		            
		            <input type="submit" value="Suchen" title="Suchen" />
		            <div class="clear_right" >
		            </div>
		            	            			        
		        </div>
	        </div>
        </div>
    </form>