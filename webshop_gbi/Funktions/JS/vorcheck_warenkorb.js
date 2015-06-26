

function eintrag_in_warenkorb_vorcheck(){
		
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['menge']; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['die Menge der Artikel an, die in den Warenkorb gepackt werden soll'];
	
	//überprüft, ob alle Felder ausgefüllt sind
	fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, 'from_warenkorb');
	
	
}