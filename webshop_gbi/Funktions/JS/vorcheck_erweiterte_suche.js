/**
 * Überprüft, ob es sich um eine Nummer handelt
 * @param {String} input
 * @returns {Boolean}
 */
function isNumeric(input)
{
	input = input.replace(',', '.');
	
    return (input - 0) == input && (''+input).trim().length > 0;
}

function vorcheckEingabe(){
	
	var form = document.forms['form_suche_erweitert'];
	var fehler = false;
	
	//alte Markierungen löschen
	form['preis_bis'].style.borderColor = '';
	form['preis_von'].style.borderColor = '';
	
	//alte Fehlermeldungen ausblenden
	document.getElementById('suche_fehlermeldung').innerHTML = '';
	
	//üuberprüft, ob bei der Preisspanne beide Felder ausgefüllt sind
	if (form['preis_von'].value != '' && form['preis_bis'].value == '' || form['preis_von'].value == '' && form['preis_bis'].value != ''){
		document.getElementById('suche_fehlermeldung').innerHTML = 'Bitte füllen Sie beide Textfelder bei der Preisspanne aus.';
		
		//markiert das fehlende Feld rot
		if (form['preis_bis'].value == ''){
			form['preis_bis'].style.borderColor = 'red';
		}else{
			form['preis_von'].style.borderColor = 'red';
		}
		
		fehler = true;
	}
	//wenn beide Felder ausgefüllt sind wird überpürft, ob in beiden Feldern eine Zahl steht
	else if (form['preis_von'].value != '' &&  form['preis_bis'].value != ''){
		
		if (isNumeric(form['preis_von'].value) == false || isNumeric(form['preis_bis'].value) == false){
			document.getElementById('suche_fehlermeldung').innerHTML = 'Bitte geben Sie bei der Preisspanne Zahlenwerte an.<br/> Die Zahlen müssen folgendermaßen formatiert sein: 1200,99 .';
			fehler = true;
			
			//markiert das falsche Feld rot
			if (isNumeric(form['preis_von'].value) == false) form['preis_von'].style.borderColor = 'red';
			if (isNumeric(form['preis_bis'].value) == false) form['preis_bis'].style.borderColor = 'red';
		}
	}
	
	//wenn gar kein Feld ausgefüllt ist
	else if (form['produktbezeichnung'].value == '' && form['preis_von'].value == '' && form['preis_bis'].value == '' && form['kategorie'].selectedIndex == 0 && form['bauart'].selectedIndex == 0 && form['bauvariante'].selectedIndex == 0 && form['artikelnr'].value == ''){
		document.getElementById('suche_fehlermeldung').innerHTML = 'Bitte füllen Sie mindestens ein Feld aus.';
		fehler = true;
	}
	
	return !fehler;
}