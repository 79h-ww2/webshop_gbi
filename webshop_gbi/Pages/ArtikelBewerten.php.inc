<!-- Vorher schauen ob angemeldet: wenn nicht zum zum Loginfenster, wenn angemeldet schauen ob bereits Bewertung abgegeben wurde -->
<script src="http://code.jquery.com/jquery-1.11.2.min.js"></script>
 <script type="text/javascript" src="Funktions/JS/bewertung.js"></script>
 <?php
                	//wenn der Kunde noch nicht angemeldet ist, wird auf die Login-Seite weitergeleitet
                	if (!(isset($_SESSION['angemeldet']))){
               ?>
               <h3>Bevor Sie eine Bewertung abgeben können, müssen Sie sich anmelden!</h3>
                <?php
                		include 'Pages/Login.php.inc';
                	}
                	//wenn er angemeldet ist bekommt der Kunde ein Popup zur Verwaltung seines Profils angezeigt
                	else{
                		$eingabe_ungueltig_bewertung = isset($eingabe_ungueltig_bewertung) ? $eingabe_ungueltig_bewertung : false;
                		?>
                		 	 <script type="text/javascript" src="Funktions/JS/rezension_prufen.js"></script>
                		    </script>
                		 	  
                			 <h2>
                				     Rezension
                				</h2>
                			<div class="artBewerten">
                				<div class="produktimg">
                					<img src="Images/Produktbilder/Mustermodell.png" alt="Produktimg" />
                				</div>
                				<h3 class="produktname">Produktname</h3>
                				<form method="post" action="<?php echo $url; ?>" onsubmit="return vorcheckEingabe_bewertung();" id="rezension" name="form_bewertung" >
                					<div class="sterne">
                						<input class="sternbewertung" type="text" name="sternbewertung">
                						<ul class="sternliste">
                							<li class="stern1"><a href="#"></a></li>
                							<li class="stern2"><a href="#"></a></li>
                							<li class="stern3"><a href="#"></a></li>
                							<li class="stern4"><a href="#"></a></li>
                							<li class="stern5"><a href="#"></a></li>
                						</ul>
                		
                					</div>
                					<div class="textfelder">
                		
                						<input class="uberschrift" type="text" name="uberschrift_feld">
                		
                						<textarea class="rezension" name="rezension_area"></textarea>
                		
                					</div>
                					<input class="sendebutton" type="submit" name="action" value="Senden"></input>
                					 <p class="fehlermeldung_bewertung" id="fehlermeldung_bewertung" >
                				            	<?php
                				            		//zeigt die Fehlermeldung an, wenn nicht alle Felder richtig ausgefüllt wurden
                				            		if ($eingabe_ungueltig_bewertung){
                				            			echo htmlspecialchars($eingabe_check_result_bewertung->get_fehlermeldung(),ENT_QUOTES,'UTF-8');
                				            		} 
                				            	?>
                				            </p>
                				</form>
                			</div>
                			<?php
                	}
                ?>