
<!DOCTYPE html>
<html lang="de">

<head>
<title>Startseite</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" href="Styles/style.css" type="text/css" />
<link rel="stylesheet" href="Styles/lightbox.css">


 
    <?php
				
				  function check_mobile() {
				  $agents = array(
				  'Windows CE', 'Pocket', 'Mobile',
				  'Portable', 'Smartphone', 'SDA',
				  'PDA', 'Handheld', 'Symbian',
				  'WAP', 'Palm', 'Avantgo',
				  'cHTML', 'BlackBerry', 'Opera Mini',
				  'Nokia'
				  );
				 
				  // Prüfen der Browserkennung
				  for ($i=0; $i<count($agents); $i++) {
				  if(isset($_SERVER["HTTP_USER_AGENT"]) && strpos($_SERVER["HTTP_USER_AGENT"], $agents[$i]) !== false)
				  return true;
				  }
				 
				  return false;
				  }
				  if (check_mobile()) {
				  ?>
				  <meta name="viewport" content="width=device-width, minimum-scale=2, initial-scale=1.0, user-scalable=no">
				  <link rel="stylesheet" href="Styles/mobile.css" type="text/css"/>
				  <?php
				  }
				 
				?>
</head>


<body class="body">
	<?php
	// zeigt die PHP-Fehlermeldungen an
	error_reporting ( E_ALL );
	ini_set ( 'display_errors', 1 );
	
	//Klassen, die vor den erstellen einer Session-Variable geladen werden müssen, damit sie in der Session gespeichert werden können
	include_once 'Classes/warenkorb.php.inc';
	include_once 'Classes/bestellungenslisteneintrag.php.inc';
	
	// Startet eine neue Sitzung
	session_start ();
	
	// lädt die Klasse fÃ¼r die Meldungsbox
	include_once './Classes/meldungsfenster.php.inc';
	
	// bildet ein Objekt das MSG-Box
	$msgbox = new Meldungsfenster ();
	
	// lädt die Klasse fÃ¼r den Datenbankzugriff
	include_once './Classes/datenbank.php.inc';
	
	// lädt die Webseiten-Kontrolldatei
	include_once './Funktions/PHP/set_control.php.inc';
	
	// Klassen für die Navigation
	include_once 'Classes/artikel.php.inc';
	include_once 'Classes/navigation.php.inc';
	?>
	<header class="mainHeader">

		<div class="HeaderContent">
			<div class="TableRow">
				<div class="logoCell">
					<a href="./"> <img src="Images/Design/Logo/fahrrad.png"
						alt="Starseite" class="logo" /></a>
				</div>

				<div class="searchCell">
            	<?php include_once 'Pages/suche_header.php.inc'; ?>
            </div>

				<div class="warenkorbCell">
            <?php
												$warenkorb1 = new warenkorb ();
												echo '<span class="warenkorbCellMengeHeader" >'.$warenkorb1->menge_im_warenkorb ().'</span>';
												include_once 'Pages/popupWarenkorb.php.inc';
												?>

<div id="Warenkorb_Beschriftung">Warenkorb</div>


					<!-- Anzahl Artikel im Warenkorb -->
				</div>

				<div class="accountCell"
					onclick="if(document.getElementById('popupRegistrierung').style.visibility == 'visible') document.getElementById('popupRegistrierung').style.visibility = '';">
                <?php
																// wenn der Kunde noch nicht angemeldet ist, wird hier das Anmelde-Popup angezeigt
																if (! (isset ( $_SESSION ['angemeldet'] ))) {
																	echo "<div id=\"Text_Anmeldung\">Anmelden</div>";
																	include 'Pages/popupRegistrierung.php.inc';
																}  // wenn er angemeldet ist bekommt der Kunde ein Popup zur Verwaltung seines Profils angezeigt
else {
																	echo "<div id=\"Text_Anmeldung\">Mein Konto</div>";
																	include_once 'Pages/popupProfilVerwalten.php.inc';
																}
																?>
																
            </div>
				<div class="mobileaccountCell">
					<a href="./?page=login" class=mobileaccountCell_LoginLink> </a>
				</div>

			</div>

		</div>

		<div class="mobileHeader">
			<a class="menu-trigger">Menu</a>
		<div class="logoCell">
					<a href="./"> <img src="Images/Design/Logo/fahrrad.png" alt="Starseite" class="logo" /></a>
				</div>
		</div>

		<!-- NAVIGATION -->
		<nav class="nav">
		      <div class="mobileMenuHeader">
    	 <ul>
             <div class="warenkorbCell">
           			<?php
					$warenkorb1 = new warenkorb ();
					?>
					<a href=".?page=warenkorb"> </a>
					<?php 
					echo '<span class="warenkorbCellMengeHeader" >'.$warenkorb1->menge_im_warenkorb ().'</span>';
					?>
 

					<!-- Anzahl Artikel im Warenkorb -->
				</div>
            <div class="accountCell" onclick="if(document.getElementById('popupRegistrierung').style.visibility == 'visible') document.getElementById('popupRegistrierung').style.visibility = '';">
                	<?php
					// wenn der Kunde noch nicht angemeldet ist, wird hier das Anmelde-Popup angezeigt
					if (! (isset ( $_SESSION ['angemeldet'] ))) {
					?>
					 <a href="./?page=login"> </a>
					<?php 
					}  // wenn er angemeldet ist bekommt der Kunde ein Popup zur Verwaltung seines Profils angezeigt
					else {
					?>
					 <a href="./?page=konto_uebersicht"> </a>
					<?php 
					}
					?>											
            </div>
             <div class="mobileSearchCell">
              <a href="./?page=suche_erweitert" ></a>
             </div>     
               
                </ul>
    	</div>
			<ul class="navigation">
        	<?php
									$navi = new Navigation ();
									$arr_kategorie = $navi->erstelle_array_kategorien ();
									
									for($i = 0; $i < count ( $arr_kategorie ); $i ++) {
										$kategorie = $arr_kategorie [$i];
										if ($i != 0) {
											echo '<li><a href="./?page=uebersicht&PTId=' . htmlspecialchars ( $kategorie->PTId, ENT_QUOTES, 'UTF-8' ) . '">' . htmlspecialchars ( $kategorie->Bezeichnung, ENT_QUOTES, 'UTF-8' ) . '</a></li>';
										
										} else {
											if (check_mobile()) {
												echo '<li><a href="./?page=fahrrad_katg">' . htmlspecialchars ( $kategorie->Bezeichnung, ENT_QUOTES, 'UTF-8' ) . '</a>';
											}
											else{
											echo '<li><a href="./?page=#">' . htmlspecialchars ( $kategorie->Bezeichnung, ENT_QUOTES, 'UTF-8' ) . '</a>';
											echo '<ul>';
											
											$bauart = $navi->erstelle_array_bauart ();
											$z = 0;
											foreach ( $bauart as $b ) {
												if ($z == 0)
													echo '<div class="Spalte">';
												echo '<li><a class="Untermenu" href="./?page=uebersicht&PTId=' . htmlspecialchars ( $kategorie->PTId, ENT_QUOTES, 'UTF-8' ) . '&bauart=' . htmlspecialchars ( $b->BId, ENT_QUOTES, 'UTF-8' ) . '">' . htmlspecialchars ( $b->Bezeichnung, ENT_QUOTES, 'UTF-8' ) . '</a></li>';
												if ($z == 3) {
													echo '</div>';
													$z = - 1;
												}
												$z ++;
											}
											if ($z < 3)
												echo '</div>';
											
											echo '</ul>';
											}
										}
									}
									?>
        
            <?php
												/*
												 * <li><a href="#">Fahrr&auml;der</a>
												 * <ul>
												 * <div class="Spalte">
												 * <li><a class="Untermenu" href="#">E-Bikes</a></li>
												 * <li><a class="Untermenu" href="#">Modell 2</a></li>
												 * <li><a class="Untermenu" href="#">Modell 3</a></li>
												 * <li><a class="Untermenu" href="#">Modell 4</a></li>
												 * </div>
												 *
												 * <div class="Spalte">
												 * <li><a class="Untermenu" href="#">Modell 5</a></li>
												 * <li><a class="Untermenu" href="#">Modell 6</a></li>
												 * <li><a class="Untermenu" href="#">Modell 7</a></li>
												 * <li><a class="Untermenu" href="#">Modell 8</a></li>
												 * </div>
												 *
												 * <div class="Spalte">
												 * <li><a class="Untermenu" href="#">Modell 1</a></li>
												 * <li><a class="Untermenu" href="#">Modell 2</a></li>
												 * <li><a class="Untermenu" href="#">Modell 3</a></li>
												 * <li><a class="Untermenu" href="#">Modell 4</a></li>
												 * </div>
												 *
												 * <div class="Spalte">
												 * <li><a class="Untermenu" href="#">Modell 5</a></li>
												 * <li><a class="Untermenu" href="#">Modell 6</a></li>
												 * <li><a class="Untermenu" href="#">Modell 7</a></li>
												 * <li><a class="Untermenu" href="#">Modell 8</a></li>
												 * </div>
												 * </ul>
												 *
												 *
												 *
												 * <li><a href="Pages/zubehoer.php">Zubeh&ouml;r</a></li>
												 * <li><a href="#">Fahrradteile</a></li>
												 * <li><a href="#">Fahrradbekleidung</a></li>
												 * <li><a href="#">Marken</a></li>
												 * <li><a href="https://www.youtube.com/watch?v=eOG90Q8EfRo">HowTo</a></li>-->
												 */
												?>
        </ul>
		</nav>
		
		
		<div style="clear: left"></div>
    <?php if (isset($_SESSION['angemeldet'])) {include_once 'Pages/status_leiste.php.inc';} ?>
    </header>

	<div class="mainContent">
		<div class="content">
        	
			<?php
			if (isset ( $_GET ['aktion'] ) && $_GET ['aktion'] == "abmelden"){
				echo '<h2 class="abmeldungsnachricht" >Sie wurden erfolgreich abgemeldet.</h2>';
			}
			elseif (isset ( $_GET ['aktion'] ) && $_GET ['aktion'] == "bestellung_uebermittelt" ){
				echo '<h2 class="abmeldungsnachricht" >Die Bestellung wurde erfolgreich an GBI übermittelt.</h2>';
			}
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
	<script src="Funktions/JS/jquery-1.11.2.min.js"></script>
	<script src="Funktions/JS/jquery.min.js"></script>
	<script src="Funktions/JS/show-nav.js"></script>
	<script src="Funktions/JS/sternbewertung.js"></script>
	<script src="Funktions/JS/lightbox-plus-jquery.min.js"></script>
</body>

</html>
