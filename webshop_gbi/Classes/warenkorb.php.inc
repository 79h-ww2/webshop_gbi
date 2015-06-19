<?php 
include_once "Classes/warenkorbeintrag.php.inc";
		
class warenkorb{ 
     
 function __construct(){ 
 	if (!isset($_SESSION["Warenkorb"])){
 	 
 		$_SESSION["Warenkorb"] = array();
	 } 
  	}
 	public function artikel_in_den_warenkorb_legen ($artikelnummer, $menge){
 		$index=count($_SESSION["Warenkorb"]);
 		$eintrag = new warenkorbeintrag($menge, $artikelnummer);
 		$_SESSION["Warenkorb"][$index] = $eintrag;
 	}
 	public function menge_im_warenkorb(){
 		//return count ($_SESSION["Warenkorb"]);
 		//return print_r($_SESSION);
 		$index=count($_SESSION["Warenkorb"]);
 		return $index;		
 	 	}
 	 public function artikel_im_warenkorb_anzeigen(){
 	 	
 	 } 
 }
?>


