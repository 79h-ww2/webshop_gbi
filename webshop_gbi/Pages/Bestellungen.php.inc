    <?php
    	include_once 'Classes/Kunde.php.inc';
    	$profil = new Kunden();
    	//Kundennr bestimmen
    	$kid = $profil->get_kid_from_email($_SESSION['angemeldet']);
    	
    	$eingabe_ungueltig_email_passwort = isset($eingabe_ungueltig_email_passwort) ? $eingabe_ungueltig_email_passwort : false;
    	
 		$eingabe_ungueltig_adresse = isset($eingabe_ungueltig_adresse) ? $eingabe_ungueltig_adresse : false;
 		
 	?>
 	<script type="text/javascript" src="./Funktions/JS/vorcheck_std_funktionen.js" >
    </script>
    <script type="text/javascript" src="./Funktions/JS/vorcheck_profil_aendern.js" >
    </script>
    <form method="post" action="./?page=profilbearbeiten&type=adressebearbeiten" onsubmit="return vorcheckEingabeAdresse();" id="form_adresse_aendern" name="form_adresse_aendern" >
        <h2>
		     Meine Bestellungen
		</h2>
        <div class="reg_box_aufteilung" >
        	<div class="TableRow_reg" >
	        
		        <div class="form_content" >
		        
		   
           
		            
		            
		        </div>
	        </div>
        </div>
    </form>
    
    
   			        

