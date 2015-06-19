<form action="./?page=produkt&pid=<?php echo htmlspecialchars($_GET['pid'],ENT_QUOTES,'UTF-8');?>" method="post" >
	<label for="menge">Menge:</label>
	<input type="text" name="menge" />
	<input type="submit" value="In den Warenkorb" />
	<input type="hidden" name="pid" value="<?php echo htmlspecialchars($_GET['pid'],ENT_QUOTES,'UTF-8');  ?>" />
	<input type="hidden" value="neuerArtikelimWarenkorb" name="type"/>
	
</form>

<?php
$warenkorb1 = new warenkorb();
echo($warenkorb1->menge_im_warenkorb());

?>