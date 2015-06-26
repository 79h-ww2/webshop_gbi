

function eintrag_in_warenkorb_vorcheck(){
		
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['menge']; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['die Menge der Artikel an, die in den Warenkorb gepackt werden soll'];
	
	//überprüft, ob alle Felder ausgefüllt sind
	fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, 'from_warenkorb');
	
	if (fehlermeldung == ''){
		if (isNumeric(document.forms['from_warenkorb']['menge'].value) == false){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += 'Die Mege muss ein Zahlwert sein.';
			
			//Textbox rot umranden
			document.forms['from_warenkorb']['menge'].style.borderColor = 'red';
			document.forms['from_warenkorb']['menge'].style.borderStyle = 'solid';
		}
		else if (document.forms['from_warenkorb']['menge'].value < 1){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += 'Die Menge muss eine positive Zahl sein.';
		}
	}
	
	//zeigt die Fehlermeldung auf der Webseite an
	if (fehlermeldung != ''){
		document.getElementById('fehlermeldung_warenkorb').innerHTML = fehlermeldung;
	}
	
	return fehlermeldung == ''; 
}