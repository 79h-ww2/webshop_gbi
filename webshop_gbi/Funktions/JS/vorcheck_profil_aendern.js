/**
 * überprüft die Formular-Eingabe, bevor sie an den Server gesendet wird
 * @returns {Boolean} gibt den Wert "true" zurück, wenn das Formular richtig ausgefüllt wurde. Wenn es falsch ausgefüllt wurde, wird ein "false" zurückgegeben.
 */
function vorcheckEingabeEmailPasswort(){
	
	var fehlermeldung = '';
	
	/*
	 * sind alle Textfelder gefüllt?
	 */
	
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['email', 'passwort', 'wpasswort']; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['ihre Email-Adresse', 'ein Passwort', 'die Passwort-Wiederholung'];
	

	//überprüft, ob alle Felder ausgefüllt sind
	fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, 'form_email_passwort_aendern');
	
	if (fehlermeldung == ''){
		//überprüft, ob die beiden Passwörter übereinstimmen
		if ( document.forms['form_email_passwort_aendern']['passwort'].value != document.forms['form_email_passwort_aendern']['wpasswort'].value ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += "Die Passw&ouml;rter stimmen nicht überein.";
			
			//Textbox rot umranden
			document.forms['form_email_passwort_aendern']['passwort'].style.borderColor = 'red';
			document.forms['form_email_passwort_aendern']['passwort'].style.borderStyle = 'solid';
			
			document.forms['form_email_passwort_aendern']['wpasswort'].style.borderColor = 'red';
			document.forms['form_email_passwort_aendern']['wpasswort'].style.borderStyle = 'solid';
		}
		
		//überprüft, ob die Email-Adresse gültig ist
		if ( checkEmail(document.forms['form_email_passwort_aendern']['email'].value) == false ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += "Die Email-Adresse ist ung&uuml;ltig.";
			
			//Textbox rot umranden
			document.forms['form_email_passwort_aendern']['email'].style.borderColor = 'red';
			document.forms['form_email_passwort_aendern']['email'].style.borderStyle = 'solid';
		}
	}
	
	//zeigt die Fehlermeldung auf der Webseite an
	if (fehlermeldung != ''){
		document.getElementById('email_passwort_fehlermeldung').innerHTML = fehlermeldung;
	}
	
	//übergibt den Rückgabewert "true", wenn kein Fehler aufgetreten ist. Ist Fehler aufgetreten wird ein "false" ausgegeben
	return fehlermeldung == ''; 
}

/**
 * überprüft die Formular-Eingabe, bevor sie an den Server gesendet wird
 * @returns {Boolean} gibt den Wert "true" zurück, wenn das Formular richtig ausgefüllt wurde. Wenn es falsch ausgefüllt wurde, wird ein "false" zurückgegeben.
 */
function vorcheckEingabeAdresse(){
	
	var fehlermeldung = '';
	
	/*
	 * sind alle Textfelder gefüllt?
	 */
	
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['vorname', 'name', 'strasse', 'hausnr', 'plz', 'ort']; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['ihren Vornamen', 'ihren Namen', 'ihre Stra&szlig;e', 'ihre Hausnummer', 'ihr Postleitzahl', 'ihr Ort'];
	
	//überprüft, ob alle Felder ausgefüllt sind
	fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, 'form_adresse_aendern');
	
	//wenn alle Felder ausgefüllt sind, wird überprüft, ob die Eingaben gültig sind
	if(fehlermeldung == '') {
		//überprüft, ob die PLZ gültig ist
		if (document.forms['form_adresse_aendern']['plz'].value.length != 5 || isNumeric(document.forms['form_adresse_aendern']['plz'].value) == false ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += "Die Postleitzahl ist ung&uuml;ltig. Bitte geben Sie eine g&uuml;ltige Postleitzahl ein.";
			
			//Textbox rot umranden
			document.forms['form_adresse_aendern']['plz'].style.borderColor = 'red';
			document.forms['form_adresse_aendern']['plz'].style.borderStyle = 'solid';
		}
	}
	
	//zeigt die Fehlermeldung auf der Webseite an
	if (fehlermeldung != ''){
		document.getElementById('EingabeAdresse_fehlermeldung').innerHTML = fehlermeldung;
	}
	
	//übergibt den Rückgabewert "true", wenn kein Fehler aufgetreten ist. Ist Fehler aufgetreten wird ein "false" ausgegeben
	return fehlermeldung == ''; 
}