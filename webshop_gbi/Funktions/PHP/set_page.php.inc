<?php
    if ( isset ( $_GET['page']) && $_GET['page'] != "" ) {
    
        switch ( $_GET['page'] ){
            case 'reg':
                include "./Pages/registrierung.php.inc";
            break;
            case 'such_erg':
            	include "./Pages/suchergebnis.php.inc";
            break;
        }
    }
    else{
        //Startseite zeigen
        include "./Pages/startseite.php.inc";
    }
?>