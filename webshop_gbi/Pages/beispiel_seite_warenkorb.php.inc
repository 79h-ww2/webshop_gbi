<form action="" methode="post" >
	<label for="menge">Menge:</label>
	<input type="text" name="menge" />
	<input type="submit" value="In den Warenkorb" />
	<input type="hidden" name="pid" value="<?php echo htmlspecialchars($_GET['pid'],ENT_QUOTES,'UTF-8');  ?>" />
</form>