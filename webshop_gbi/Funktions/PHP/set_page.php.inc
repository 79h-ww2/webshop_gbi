<?php
    if ( isset ( $_GET['page']) && $_GET['page'] != "" ) {
    
        switch ( $_GET['page'] ){
            case 'reg':
                include "./Pages/registrierung.php.inc";
            break;
            case 'such_erg':
            	include "./Pages/suchergebnis.php.inc";
            break;
            case 'suche_erweitert':
            	include "./Pages/erweiterte_suche.php.inc";
            break;
            case 'impressum':
            	include './Pages/impressum.php.inc';
            break;
            case 'agb':
            	include './Pages/AGB.php.inc';
            break;
            case 'datenschutz':
            	include './Pages/datenschutz.php.inc';
            break;
            case 'seriousRockaway26':
            	include './Pages/seriousRockaway26.php.inc';
            	break;
            case 'uebersicht':
            	include './Pages/uebersicht.php.inc';
            	break;
            case 'produkt':
            	include_once 'Pages/beispiel_seite_warenkorb.php.inc';
            break;
            	
            case 'profilbearbeiten':
            	//profil kann nur bearbeitet werden, wenn der Kunde angemelet ist 
            	if (isset($_SESSION['angemeldet'])){
            		include './Pages/profilbearbeiten.php.inc';
            	}else{
            		echo "Sie müssen angemeldet sein, um Ihr Profil ändern zu können.";
            	}
            break;
            	
            default:
            	echo "<br/><h2>Gewünschte Seite wurde nicht gefunden.</h2>";
        }
    }
    else{
        //Startseite zeigen
        include "./Pages/startseite.php.inc";
    }
?>
