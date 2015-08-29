    <!-- NAVIGATION -->

	<!--
	Der Quellcode zeigt nur einen kleinen Ausschnitt aus der kompletten Index Datei.
	Der nachfolgende Quellcode wurde von Herrn Schnürer geeriert.
	-->
	
    <nav class="nav">
        <ul class="navigation">
        <?php 
        	$navi = new Navigation();
        	$arr_kategorie = $navi->erstelle_array_kategorien();
        		
        	for ($i = 0; $i < count($arr_kategorie); $i++){
        		$kategorie = $arr_kategorie[$i];
        		if ( $i != 0){
        			echo '<li><a href="./?page=uebersicht&PTId='
					.htmlspecialchars($kategorie->PTId,ENT_QUOTES,'UTF-8').'">'
					.htmlspecialchars($kategorie->Bezeichnung,ENT_QUOTES,'UTF-8').'</a></li>';
        			}
        		else{
        			echo '<li><a href="#">'.htmlspecialchars($kategorie->Bezeichnung,
					ENT_QUOTES,'UTF-8').'</a>';
        			echo '<ul>';
        				
        			$bauart = $navi->erstelle_array_bauart();
        			$z = 0;
        			foreach ($bauart as $b){
        				if ( $z == 0) echo '<div class="Spalte">';
        				echo '<li><a class="Untermenu" href="./?page=uebersicht&PTId='
						.htmlspecialchars($kategorie->PTId,ENT_QUOTES,'UTF-8').'&bauart='
						.htmlspecialchars($b->BId,ENT_QUOTES,'UTF-8').'">'
						.htmlspecialchars($b->Bezeichnung,ENT_QUOTES,'UTF-8').'</a></li>';
        				if ( $z == 3){
        					echo '</div>';
        					$z=-1;
        				}
        				$z++;
        			}
        			if ( $z < 3) echo '</div>';
        			
        			echo '</ul>';
        		}
        	}
        ?>
        
        </ul>
    </nav>
