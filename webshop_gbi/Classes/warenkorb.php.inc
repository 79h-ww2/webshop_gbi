<?php 
include_once "Classes/warenkorbeintrag.php.inc";
		
class warenkorb{ 
     
 function __construct(){ 
 	if (!isset($_SESSION["Warenkorb"])){
 	 
 		$_SESSION["Warenkorb"] = array();
	 } 
  	}
  	
  	/*  Menge im Warenkorb, falls 2 mal der gleiche Artikel hinzugefügt, wird ingsgesamt nur 1 Artikel
  	 * mit der gewünschte Menge angezeigt
  	 */
 	public function artikel_in_den_warenkorb_legen ($artikelnummer, $menge){
		$artikelschonvorhanden = -1;
		for( $i = 0; $i < count($_SESSION["Warenkorb"]); $i++){
 			$w = $_SESSION["Warenkorb"];
 			$y = $w[$i];
 			if ($y->get_artikelnummer() == $artikelnummer) $artikelschonvorhanden = $i;
		}
		if ($artikelschonvorhanden!= -1){
			$w = $_SESSION["Warenkorb"];
			$y = $w[$artikelschonvorhanden];
			$x = $y->get_menge();
			$x+= $menge;
			$_SESSION["Warenkorb"][$artikelschonvorhanden]->set_menge($x);
		}
			else {
 		$index=count($_SESSION["Warenkorb"]);
 		$eintrag = new warenkorbeintrag($menge, $artikelnummer);
 		$_SESSION["Warenkorb"][$index] = $eintrag;
			}
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