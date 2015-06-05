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
            default:
            	echo "<h2>Gewünschte Seite wurde nicht gefunden.</h2>";
        }
    }
    else{
        //Startseite zeigen
        include "./Pages/startseite.php.inc";
    }
?>