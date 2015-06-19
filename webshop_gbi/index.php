
<!DOCTYPE html>
<html lang="de">

<head>
    <title>Startseite</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    
    <link rel="stylesheet" href="Styles/style.css" type="text/css"/>
</head>


<body class="body">
	<?php	
		//zeigt die PHP-Fehlermeldungen an
		error_reporting(E_ALL);
		ini_set('display_errors', 1);
		
		include_once 'Classes/warenkorb.php.inc';
		session_start();
		//$warenkorb1 = new warenkorb();
		//echo($warenkorb1->menge_im_warenkorb());
		//	die($warenkorb1->menge_im_warenkorb());
		//Startet eine neue Sitzung
		
		
		//lÃ¤dt die Klasse fÃ¼r die Meldungsbox
		include_once './Classes/meldungsfenster.php.inc';
		
		//bildet ein Objekt das MSG-Box
		$msgbox = new Meldungsfenster(); 
		
		//lÃ¤dt die Klasse fÃ¼r den Datenbankzugriff
		include_once './Classes/datenbank.php.inc';
	
		//lÃ¤dt die Webseiten-Kontrolldatei
		include_once './Funktions/PHP/set_control.php.inc';
		
		//Klassen fÃ¼r die Navigation
		include_once 'Classes/artikel.php.inc';
		include_once 'Classes/navigation.php.inc';
	?>

    <header class="mainHeader">
    
    <div class="HeaderContent">
        <div class="TableRow">
            <div class="logoCell">
                <a href="./"> <img src="Images/Design/Logo/fahrrad.png" alt="Starseite" class="logo" /></a>
            </div>
            
            <div class="searchCell">
            	<?php include_once 'Pages/suche_header.php.inc'; ?>
            </div>
            
            <div class="warenkorbCell">
    
            	<?php
            	
$warenkorb1 = new warenkorb();

echo($warenkorb1->menge_im_warenkorb());
include_once 'Pages/popupWarenkorb.php.inc';
?>

<div id="Warenkorb_Beschriftung" >Warenkorb
</div>

 <!-- Anzahl Artikel im Warenkorb -->
            </div>
            
            <div class="accountCell" onclick="if(document.getElementById('popupRegistrierung').style.visibility == 'visible') document.getElementById('popupRegistrierung').style.visibility = '';">
                <?php
                	//wenn der Kunde noch nicht angemeldet ist, wird hier das Anmelde-Popup angezeigt
                	if (!(isset($_SESSION['angemeldet']))){
                		echo "Anmelden";
                		include 'Pages/popupRegistrierung.php.inc';
                	}
                	//wenn er angemeldet ist bekommt der Kunde ein Popup zur Verwaltung seines Profils angezeigt
                	else{
                		echo "Mein Konto";
                		include_once 'Pages/popupProfilVerwalten.php.inc';
                	}
                ?>
            </div>
            
        </div>
        
    </div>
    
    
    
    <!-- NAVIGATION -->
    <nav class="nav">
        <ul class="navigation">
        	<?php 
        		$navi = new Navigation();
        		$arr_kategorie = $navi->erstelle_array_kategorien();
        		
        		for ($i = 0; $i < count($arr_kategorie); $i++){
        			$kategorie = $arr_kategorie[$i];
        			if ( $i != 0){
        				echo '<li><a href="./?page=uebersicht&PTId='.htmlspecialchars($kategorie->PTId,ENT_QUOTES,'UTF-8').'">'.htmlspecialchars($kategorie->Bezeichnung,ENT_QUOTES,'UTF-8').'</a></li>';
        			}
        			else{
        				echo '<li><a href="#">'.htmlspecialchars($kategorie->Bezeichnung,ENT_QUOTES,'UTF-8').'</a>';
        				echo '<ul>';
        				
        				$bauart = $navi->erstelle_array_bauart();
        				$z = 0;
        				foreach ($bauart as $b){
        					if ( $z == 0) echo '<div class="Spalte">';
        					echo '<li><a class="Untermenu" href="./?page=uebersicht&PTId='.htmlspecialchars($kategorie->PTId,ENT_QUOTES,'UTF-8').'&bauart='.htmlspecialchars($b->BId,ENT_QUOTES,'UTF-8').'">'.htmlspecialchars($b->Bezeichnung,ENT_QUOTES,'UTF-8').'</a></li>';
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
        
            <?php /*<li><a href="#">Fahrr&auml;der</a>
    			<ul> 
        			<div class="Spalte">
                        <li><a class="Untermenu" href="#">Modell 1</a></li>
                        <li><a class="Untermenu" href="#">Modell 2</a></li>
                        <li><a class="Untermenu" href="#">Modell 3</a></li>
                        <li><a class="Untermenu" href="#">Modell 4</a></li>
                     </div>
               
        			<div class="Spalte">
                        <li><a class="Untermenu" href="#">Modell 5</a></li>
                        <li><a class="Untermenu" href="#">Modell 6</a></li>
                        <li><a class="Untermenu" href="#">Modell 7</a></li>
                        <li><a class="Untermenu" href="#">Modell 8</a></li>
                     </div>
                     
                     <div class="Spalte">
                        <li><a class="Untermenu" href="#">Modell 1</a></li>
                        <li><a class="Untermenu" href="#">Modell 2</a></li>
                        <li><a class="Untermenu" href="#">Modell 3</a></li>
                        <li><a class="Untermenu" href="#">Modell 4</a></li>
                     </div>

        			<div class="Spalte">
                        <li><a class="Untermenu" href="#">Modell 5</a></li>
                        <li><a class="Untermenu" href="#">Modell 6</a></li>
                        <li><a class="Untermenu" href="#">Modell 7</a></li>
                        <li><a class="Untermenu" href="#">Modell 8</a></li>
                     </div>
                </ul>
                
                
                
            <li><a href="Pages/zubehoer.php">Zubeh&ouml;r</a></li>
            <li><a href="#">Fahrradteile</a></li>
            <li><a href="#">Fahrradbekleidung</a></li>
            <li><a href="#">Marken</a></li>
    		<li><a href="https://www.youtube.com/watch?v=eOG90Q8EfRo">HowTo</a></li>-->*/?>
        </ul>
    </nav>
    <div style="clear:left" ></div>
    <?php if (isset($_SESSION['angemeldet'])) include_once 'Pages/status_leiste.php.inc'; ?>
    </header>
    
    <div class="mainContent">
        <div class="content">
        	
			<?php
				if (isset($_GET['aktion']) && $_GET['aktion']== "abmelden") echo '<h2 class="abmeldungsnachricht" >Sie wurden erfolgreich abgemeldet.</h2>';			
                include "./Funktions/PHP/set_page.php.inc";
            ?>
        </div>
    </div>
    
    <!-- aktivieren, zwalls Sidebar gewÃ¼nscht sind 
    
    <aside class="top-sidebar">
        <article>
            <h2>Top sidebar</h2>
            <p>Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor.</p>
        </article>
    </aside>
    
    <aside class="middle-sidebar">
        <article>
            <h2>Middle sidebar</h2>
            <p>Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor.</p>
        </article>
    </aside>
    
    <aside class="bottom-sidebar">
        <article>
            <h2>Bottom sidebar</h2>
            <p>Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor.</p>
        </article>
    </aside>
    
    -->
    
    <footer class="mainFooter">
    	<ul>
        	<li>Copyright &copy; 2015 Hs-OWL</li>
        	<li><a href="./?page=impressum">Impressum</a></li>
        	<li><a href="./?page=agb">AGB</a></li>
        	<li><a href="./?page=datenschutz">Datenschutz</a></li>
        </ul>
    </footer>
</body>

</html>
