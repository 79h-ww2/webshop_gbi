/**
 * Überprüft die eingegebene Menge der Ware, bevor der Artikel in den Warenkorb gepackt wird
 * Übernommen von Benedikt, um den Zeitplan einhalten zu können
 * @returns {Boolean} gibt zurück, ob ein Fehler beim Überprüfen gefunden wurde
 */
function eintrag_in_warenkorb_vorcheck(){
	
	//alte Fehlermeldungen ausblenden:
	document.forms['from_warenkorb']['menge'].style.borderColor = '';
	document.forms['from_warenkorb']['menge'].style.borderStyle = '';
	document.getElementById('fehlermeldung_warenkorb').innerHTML = '';
		
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['menge']; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['die Menge der Artikel an, die in den Warenkorb gepackt werden soll'];
	
	//überprüft, ob alle Felder ausgefüllt sind
	fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, 'from_warenkorb');
		
	if (fehlermeldung == ''){
		
		//überprüft, ob der Wert im Mengen-Inputfeld eine gültige Zahl ist
		if (isNumeric(document.forms['from_warenkorb']['menge'].value) == false){
			
			//wenn sie keine gültige Zahl ist -> Fehlermelung 
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += 'Die Menge muss ein Zahlwert sein.';
			
			//Textbox rot umranden
			document.forms['from_warenkorb']['menge'].style.borderColor = 'red';
			document.forms['from_warenkorb']['menge'].style.borderStyle = 'solid';
		}
		//Fehlermedung, wenn die Zahl nicht positive ist
		else if (parseInt(document.forms['from_warenkorb']['menge'].value) < 1){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += 'Die Menge muss eine positive Zahl sein, die größer als 0 ist.';
			
			//Textbox rot umranden
			document.forms['from_warenkorb']['menge'].style.borderColor = 'red';
			document.forms['from_warenkorb']['menge'].style.borderStyle = 'solid';
		}
		//Fehlermeldung, wenn mehr Exemplare gewählt wurden als vorhanden sind
		else if ( parseInt(document.getElementById('exemplare_auf_lager').innerHTML) < parseInt(document.forms['from_warenkorb']['menge'].value) ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += 'Es können nicht mehr Exemplare bestellt werden, als auf Lager sind.';
			
			//Textbox rot umranden
			document.forms['from_warenkorb']['menge'].style.borderColor = 'red';
			document.forms['from_warenkorb']['menge'].style.borderStyle = 'solid';
		}
	}
	
	//zeigt die Fehlermeldung auf der Webseite an
	if (fehlermeldung != ''){
		document.getElementById('fehlermeldung_warenkorb').innerHTML = fehlermeldung;
	}
	
	return fehlermeldung == ''; 
}