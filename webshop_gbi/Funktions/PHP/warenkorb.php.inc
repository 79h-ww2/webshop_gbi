<?php 
if (isset($_POST['menge']) && isset($_POST['pid'])){
	$warenkorb1 = new warenkorb();
	$warenkorb1->artikel_in_den_warenkorb_legen($_POST['pid'],$_POST['menge']);
} 		
?>