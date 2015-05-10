<?php
	//lädt die von der Seite benötigten Funktionen
	if (isset($_POST['type'])){
		switch ($_POST['type']){
			case 'reg':
				include_once './Funktions/PHP/registrierung_durchfuehren.php.inc';
			break;
		}
	}
?>