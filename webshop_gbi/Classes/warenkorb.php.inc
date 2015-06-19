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
 		
 		$menge = 0;
 		for( $i = 0; $i < count($_SESSION["Warenkorb"]); $i++){
 			$w = $_SESSION["Warenkorb"];
 			$y = $w[$i];
 			$menge += $y->get_menge();
 		}
 		return $menge;		
 	 	}
 	 public function artikel_im_warenkorb_anzeigen(){
 	 	$w = $_SESSION["Warenkorb"];
 	 	return $w;
 	 	  	 		
 	  }
}
?>


