/**
 * überprüft die Formular-Eingabe, bevor sie an den Server gesendet wird
 * @returns {Boolean} gibt den Wert "true" zurück, wenn das Formular richtig ausgefüllt wurde. Wenn es falsch ausgefüllt wurde, wird ein "false" zurückgegeben.
 */
function vorcheckZahlungsart(){
	
	var fehlermeldung = '';
	
	//wenn das Bankeinzugsformular aktiviert ist
	if (document.getElementById('bankeinzug').checked == true){
	
		/*
		 * sind alle Textfelder gefüllt?
		 */
		//Array mit allen Feldern, die ausgefüllt sein müssen
		var felder = ['inhaber', 'iban', 'bic']; 
		
		//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
		var meldungswort = ['den Kontoinhaber', 'die IBAN-Nummer', 'den BIC-Code'];
		
	
		//überprüft, ob alle Felder ausgefüllt sind
		fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, 'form_zahlungsart');
		
		if (fehlermeldung == ''){
			//überprüft, ob die IBAN-Nummer eine gültige länge hat
			if ( document.forms['form_zahlungsart']['iban'].value.length > 34 && document.forms['form_zahlungsart']['iban'].value.length < 0 ){
				fehlermeldung += fehlermeldung == '' ? '' : ' ';
				fehlermeldung += "Die IBAN-Nummer hat eine ungültige Länge.";
				
				//Textbox rot umranden
				document.forms['form_zahlungsart']['iban'].style.borderColor = 'red';
				document.forms['form_zahlungsart']['iban'].style.borderStyle = 'solid';
			}
			
			//überprüft, ob der BIC-Code eine gültige Länge hat
			if ( !(document.forms['form_zahlungsart']['bic'].value.length == 8 || document.forms['form_zahlungsart']['bic'].value.length == 11) ){
				fehlermeldung += fehlermeldung == '' ? '' : ' ';
				fehlermeldung += "Der BIC-Code hat eine ungültige Länge.";
				
				//Textbox rot umranden
				document.forms['form_zahlungsart']['bic'].style.borderColor = 'red';
				document.forms['form_zahlungsart']['bic'].style.borderStyle = 'solid';
			}
		}
		
		//zeigt die Fehlermeldung auf der Webseite an
		if (fehlermeldung != ''){
			document.getElementById('zahlungsart_fehlermeldung').innerHTML = fehlermeldung;
		}
	}
	
	//übergibt den Rückgabewert "true", wenn kein Fehler aufgetreten ist. Ist Fehler aufgetreten wird ein "false" ausgegeben
	return fehlermeldung == ''; 
}

/**
 * Vorcheck der eingegebenen Lieferadresse
 */
function vorcheckLieferadresse(){
	
	var rueckgabe = true;
	
	//wenn das Formular zur Eingabe einer anderen Adresse aktiviert ist
	if (document.getElementById('adresse_andere').checked == true){
		rueckgabe = vorcheckEingabeAdresse();
	}
	
	return rueckgabe;
}

/**
 * Überprüft, ob die AGB zugestimmt wurde
 */
function vorcheckAGBZugestimmt(){
	if ( document.getElementById('ack_agb').checked == false){
		document.getElementById('fehler_check_agb').innerHTML = 'Sie müssen der AGB zustimmen, um den Bestellvorgang absenden zu können.';
	}else{
		document.getElementById('fehler_check_agb').innerHTML = '';
	}
	
	return document.getElementById('ack_agb').checked;
}