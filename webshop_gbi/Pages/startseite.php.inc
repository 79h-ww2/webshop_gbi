<?php 

include_once 'Classes/ArtikelDesTages.php.inc';

$artikelDesTages = new ArtikelDesTages();

$ArtikelDesTagesPId= $artikelDesTages->ArtikelDesTagesPIdSuchen();

?>
<div class = "startseite">
<article class="detailContent">
    <header>
        <h2>Fahrrad des Tages</h2>
    </header>
        
    <content>
    
    <div class="detailLeft"> 
    	Detailansichten:
    		<div class="detailCell">
    		
    		<?php 
    		
    		foreach ($artikelDesTages->DetailbilderAnzeigen($ArtikelDesTagesPId) AS $PfadDetailbild) {
    			echo '<a href= "'.$PfadDetailbild.'"  data-lightbox="Produktbilder"> <img src="'.$PfadDetailbild.'" alt="Detail" class="BildMustermodellMinatur" /> </a>';
    		}
    		?>
    		
    		</div>
    </div>
    
    	<div class= "detailMiddle">
    	<img src="
    		<?php 
    		
    		echo $artikelDesTages->produktbildAnzeigen($ArtikelDesTagesPId);
    		
    		?>" alt="
    		<?php 
    		
    		$artikel = $artikelDesTages->beschreibungAnzeigen($ArtikelDesTagesPId);
    		
    		echo htmlspecialchars($artikel->Bezeichnung,ENT_QUOTES,'UTF-8');
    		
    		?>
    		" class="BildMustermodell" />
    		<?php 
    		if ($artikelDesTages->produktbildAnzeigen($ArtikelDesTagesPId)!="")
    			echo "</a>";
    		?>
    		
    		</div>
    	
    	<div class="detailContentText">
    		<?php 
							
					$artikel = $artikelDesTages->beschreibungAnzeigen($ArtikelDesTagesPId);
					
									
					echo  '<span id="bauart" > <h3><a href="#" title="'.htmlspecialchars($artikel->bauart,ENT_QUOTES,'UTF-8').'">'.htmlspecialchars($artikel->bauart,ENT_QUOTES,'UTF-8').'</a> </h3> </span>'
					
					?>
    		
    		
    		
    		<div class="menge_exemplare_gruen">
    			<?php 
					
					$artikel = $artikelDesTages->beschreibungAnzeigen($ArtikelDesTagesPId);
					
					
					echo '<span id="exemplare_auf_lager" >'.htmlspecialchars($artikel->Menge,ENT_QUOTES,'UTF-8').'</span> Exemplare verfügbar';
					
				?>
    		</div>
    		
    		
    		<div class="listeneintrag_auflistung_preis" >
    			<?php 
							
					$artikel = $artikelDesTages->beschreibungAnzeigen($ArtikelDesTagesPId);
					
					
					echo '<span id="preis" >'.htmlspecialchars($artikel->Preis,ENT_QUOTES,'UTF-8').'</span> €';
					
					?>
    		</div>		
    		
    		
	        
	        <?php 
	        
	        $eigenschaften = $artikelDesTages ->EigenschaftenAnzeigen($ArtikelDesTagesPId) ;
	        
	        if (count($eigenschaften)>0) {
	        	
	        	
	        	if (count($eigenschaften)==1 && $eigenschaften[0]=="") {
	        	}else {
	        	
	        	echo '<p><strong>Eigenschaften</strong></p>
        				<ul type="disc">';
	        	
	        	foreach ($eigenschaften as $eigenschaft){
	        		echo '<li>'.htmlspecialchars($eigenschaft,ENT_QUOTES,'UTF-8').'</li>';
	        	}
	        	echo '</ul>';
	        	}
	        }
	        
	        ?>
		        
    	</div>
    	
    </content>
</article>

<article class="bottomContent">
    <header>
        <h2>Meist angesehene Artikel</h2>
    </header>
    
    <footer>
        
    </footer>
    
    <content>
    <div class="BottomContentContainer">
    	<div class="BottomContentTableRow">
    		<div class="articleCell">
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellKlein" />
	    		<h4><a href="#" title="Mustermodell A">Mustermodell A</a></h4>
    		</div>
    		
    		<div class="articleCell">
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellKlein" />
	    		<h4><a href="#" title="Mustermodell B">Mustermodell B</a></h4>
    		</div>
    		
    		<div class="articleCell">
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellKlein" />
	    		<h4><a href="#" title="Mustermodell C">Mustermodell C</a></h4>
    		</div>
    		
    		<div class="articleCell">
	    		<img src="Images/Produktbilder/Mustermodell.png" alt="Mustermodell" class="BildMustermodellKlein" />
	    		<h4><a href="#" title="Mustermodell D">Mustermodell D</a></h4>
    		</div>
	    	
    	</div>
        </div>
    </content>
</article>
</div>