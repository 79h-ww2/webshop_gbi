
<!DOCTYPE html>
<html lang="de">

<head>
    <title>Startseite</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    
    <link rel="stylesheet" href="Styles/style.css" type="text/css"/>
    <meta name accesskey="viewport" content="width=device-widht, initila-scale=1.0"/>
</head>


<body class="body">
	<?php	
		//zeigt die PHP-Fehlermeldungen an
		error_reporting(E_ALL);
		ini_set('display_errors', 1);
		
		//Startet eine neue Sitzung
		session_start();
		
		//lädt die Klasse für die Meldungsbox
		include_once './Classes/meldungsfenster.php.inc';
		
		//bildet ein Objekt das MSG-Box
		$msgbox = new Meldungsfenster(); 
		
		//lädt die Klasse für den Datenbankzugriff
		include_once './Classes/datenbank.php.inc';
	
		//lädt die Webseiten-Kontrolldatei
		include_once './Funktions/PHP/set_control.php.inc';
	?>

    <header class="mainHeader">
    
    <div class="HeaderContent">
        <div class="TableRow">
            <div class="logoCell">
                <a href="./"> <img src="Images/Design/Logo/fahrrad.png" alt="Starseite" class="logo" /></a>
            </div>
            
            <div class="searchCell">
            
            </div>
            
            <div class="warenkorbCell">
            	100 <!-- Anzahl Artikel im Warenkorb -->
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
                		echo "Profil";
                		include_once 'Pages/popupProfilVerwalten.php.inc';
                	}
                ?>
            </div>
            
        </div>
        
    </div>
    
    
    
    <!-- NAVIGATION -->
    <nav class="nav">
        <ul class="navigation">
            <li><a href="#">Fahrr&auml;der</a> <!-- HIER HINTER DARF KEIN </li> stehn SONST GEHTS NICHT!!! -->
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
    		<li><a href="https://www.youtube.com/watch?v=eOG90Q8EfRo">HowTo</a></li>
        </ul>
    </nav>
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
    
    <!-- aktivieren, zwalls Sidebar gewünscht sind 
    
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
        	<li><a href="#">Impressum</a></li>
        </ul>
    </footer>
</body>

</html>
