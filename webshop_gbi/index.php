<!DOCTYPE html>
<html lang="de">

<head>
    <title>Startseite</title>
    <meta charset="utf-8" />
    
    <link rel="stylesheet" href="Styles/style.css" type="text/css"/>
    <meta name accesskey="viewport" content="width=device-widht, initila-scale=1.0"/>
</head>


<body class="body">

    <header class="mainHeader">
    
    <div class="HeaderContent">
        <div class="TableRow">
            <div class="logoCell">
                <a href="index.php"> <img src="Images/Design/Logo/fahrrad_pixel.png" alt="Starseite" class="logo" /></a>
            </div>
            
            <div class="searchCell">
            
            </div>
            
            <div class="warenkorbCell">
                <img src="Images/Design/warenkorb.png" class="waenkorb"  />
            </div>
            
            <div class="accountCell">
                <img src="Images/Design/account.png" class="account" />
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
    
    
    </header>
    
    <div class="mainContent">
        <div class="content">
			<?php
                include "./Funktions/PHP/set_page.php.inc";
            ?>
            <!--<article class="topContent">
                <header>
                    <h2><a href="#" title="First Post">Fahrrad des Tages</a> </h2>
                </header>
                
                <footer>
                </footer>
                
                <content>
                    <p>Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt
                    ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores
                    et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
                    Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore 
                    et dolore magna aliquyam erat, sed diam voluptua.
                    At vero eos et accusam et justo duo dolores et ea rebum.
                    Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.</p>
                    
                    <p>Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt
                    ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores
                    et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.
                    Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore
                    et dolore magna aliquyam erat, sed diam voluptua.
                    At vero eos et accusam et justo duo dolores et ea rebum.
                    Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.</p>
                </content>
            </article>-->
        </div>
    </div>
    
    <!-- aktivieren, zwalls Sidebar gew�nscht sind 
    
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
        <p>Copyright &copy; 2015 Hs-OWL</p>
    </footer>

</body>

</html>
