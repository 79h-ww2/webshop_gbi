/**
 * überprüft die Formular-Eingabe, bevor sie an den Server gesendet wird
 * @returns {Boolean} gibt den Wert "true" zurück, wenn das Formular richtig ausgefüllt wurde. Wenn es falsch ausgefüllt wurde, wird ein "false" zurückgegeben.
 */
function vorcheckEingabe(){
	
	var fehlermeldung = '';
	
	/*
	 * sind alle Textfelder gefüllt?
	 */
	
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['vorname', 'name', 'strasse', 'hausnr', 'plz', 'ort', 'email', 'passwort', 'wpasswort']; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['ihren Vornamen', 'ihren Namen', 'ihre Stra&szlig;e', 'ihre Hausnummer', 'ihr Postleitzahl', 'ihr Ort', 'ihre Email-Adresse', 'ein Passwort', 'die Passwort-Wiederholung'];
	
	fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, 'form_registrierung');
	
	if (fehlermeldung == ''){
		//überprüft, ob die PLZ gültig ist
		if (document.forms['form_registrierung']['plz'].value.length != 5 || isNumeric(document.forms['form_registrierung']['plz'].value) == false ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += "Die Postleitzahl ist ung&uuml;ltig. Bitte geben Sie eine g&uuml;ltige Postleitzahl ein.";
			
			//Textbox rot umranden
			document.forms['form_registrierung']['plz'].style.borderColor = 'red';
			document.forms['form_registrierung']['plz'].style.borderStyle = 'solid';
		}
		
		//überprüft, ob die beiden Passwörter übereinstimmen
		if ( document.forms['form_registrierung']['passwort'].value != document.forms['form_registrierung']['wpasswort'].value ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += "Die Passw&ouml;rter stimmen nicht überein.";
			
			//Textbox rot umranden
			document.forms['form_registrierung']['passwort'].style.borderColor = 'red';
			document.forms['form_registrierung']['passwort'].style.borderStyle = 'solid';
			
			document.forms['form_registrierung']['wpasswort'].style.borderColor = 'red';
			document.forms['form_registrierung']['wpasswort'].style.borderStyle = 'solid';
		}
		
		//überprüft, ob die Email-Adresse gültig ist
		if ( checkEmail(document.forms['form_registrierung']['email'].value) == false ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += "Die Email-Adresse ist ung&uuml;ltig.";
			
			//Textbox rot umranden
			document.forms['form_registrierung']['email'].style.borderColor = 'red';
			document.forms['form_registrierung']['email'].style.borderStyle = 'solid';
		}
	}
	
	//zeigt die Fehlermeldung auf der Webseite an
	if (fehlermeldung != ''){
		document.getElementById('reg_fehlermeldung').innerHTML = fehlermeldung;
	}
	
	//übergibt den Rückgabewert "true", wenn kein Fehler aufgetreten ist. Ist Fehler aufgetreten wird ein "false" ausgegeben
	return fehlermeldung == ''; 
}