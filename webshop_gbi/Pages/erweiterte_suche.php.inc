    <?php
    	include_once 'Classes/artikel.php.inc';
    	include_once 'Classes/navigation.php.inc';
    ?>
    <script type="text/javascript" src="./Funktions/JS/vorcheck_erweiterte_suche.js" >
    </script>
    <form method="post" action="./?page=suche_erweitert" onsubmit="return vorcheckEingabe();" id="suche_erweitert" name="form_suche_erweitert" >
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
		                <input type="text" name="produktbezeichnung"  value="<?php if(isset($_POST['produktbezeichnung'])) echo htmlspecialchars($_POST['produktbezeichnung'],ENT_QUOTES,'UTF-8'); ?>" class="lang_reg" />
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label >Preispanne:</label>
		                <label for="preis_von" class="label_preisspanne" >von:</label>
		                <input type="text" name="preis_von" value="<?php if(isset($_POST['preis_von'])){ echo htmlspecialchars($_POST['preis_von'],ENT_QUOTES,'UTF-8'); if ($suche_vorcheck_fehler->get_feldstatus('preis_von')) echo '" style="border-color:red;"'; }?>" class="bereich_preis" /> &euro;
		                <label for="preis_bis" class="label_preisspanne kleiner_abstand_vertikal" >bis:</label>
		                <input type="text" name="preis_bis" value="<?php if(isset($_POST['preis_bis'])) { echo htmlspecialchars($_POST['preis_bis'],ENT_QUOTES,'UTF-8'); if ($suche_vorcheck_fehler->get_feldstatus('preis_bis')) echo '" style="border-color:red;"'; }?>" class="bereich_preis" /> &euro;
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="kategorie">Kategorie:</label>
		                <select name="kategorie"   class="lang_reg">
		                	<option>alle</option>
		                	<?php
		                		$navi = new Navigation();
		                		$kategorien = $navi->erstelle_array_kategorien();
		                		foreach ($kategorien as $kategorie){
		                			$option ="<option";
		                			$option .= (isset($_POST['kategorie']) && $_POST['kategorie'] == htmlspecialchars($kategorie->Bezeichnung,ENT_QUOTES,'UTF-8')) ? " selected>" : ">";
		                			echo $option.htmlspecialchars($kategorie->Bezeichnung,ENT_QUOTES,'UTF-8')."</option>\n";
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
		                			$option ="<option";
		                			$option .= (isset($_POST['bauart']) && $_POST['bauart'] == htmlspecialchars($bauart->Bezeichnung,ENT_QUOTES,'UTF-8')) ? " selected>" : ">";
		                			echo $option.htmlspecialchars($bauart->Bezeichnung,ENT_QUOTES,'UTF-8')."</option>\n";
		                		}
		                	?>
		                </select>
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="bauvariante">Bauvariante:</label>
		                <select name="bauvariante"  class="lang_reg">
		                	<option>alle</option>
		                	<option <?php if(isset($_POST['bauvariante']) && $_POST['bauvariante'] == "Herrenrad") echo "selected"?> >Herrenrad</option>
		                	<option <?php if(isset($_POST['bauvariante']) && $_POST['bauvariante'] == "Damenrad") echo "selected"?> >Damenrad</option>
		                </select>
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="artikelnr">Artikelnummer:</label>
		                <input type="text" name="artikelnr"  value="<?php if(isset($_POST['artikelnr'])) echo htmlspecialchars($_POST['artikelnr'],ENT_QUOTES,'UTF-8'); ?>" class="lang_reg" />
		            </p>
		            
		            <p class="reg_form_zeile" >
		                <label for="marke">Marke:</label>
		                <input type="text" name="marke"  value="<?php if(isset($_POST['marke'])) echo htmlspecialchars($_POST['marke'],ENT_QUOTES,'UTF-8'); ?>" class="lang_reg" />
		            </p>
		            
		            <input type="hidden" name="type" value="erweiterte_suche" />
		            
		            <p class="text_fehlermeldung" id="suche_fehlermeldung" >
		            	<?php
		            		//zeigt eine Fehlermeldung an, wenn die Textfelder nicht richtig ausgefüllt sind
		            		if (isset($_POST['suche_submit'])) echo $suche_vorcheck_fehler->get_fehlermeldung();
		            	?>
		            </p>           
		            
		            <input type="submit" value="Suchen"  name="suche_submit" title="Suchen" />
		            <div class="clear_right" >
		            </div>
		            	            			        
		        </div>
	        </div>
        </div>
    </form>