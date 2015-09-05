<?php				
function check_mobile() {
$agents = array('Windows CE', 'Pocket', 'Mobile',
			   'Portable', 'Smartphone', 'SDA',
			   'PDA', 'Handheld', 'Symbian',
			   'WAP', 'Palm', 'Avantgo',
			   'cHTML', 'BlackBerry', 'Opera Mini',
			   'Nokia');
	
// Pruefen der Browserkennung
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
