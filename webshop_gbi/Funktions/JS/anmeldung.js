/**
 * überprüft die Formular-Eingabe, bevor sie an den Server gesendet wird
 * @returns {Boolean} gibt den Wert "true" zurück, wenn das Formular richtig ausgefüllt wurde. Wenn es falsch ausgefüllt wurde, wird ein "false" zurückgegeben.
 */
function vorcheckEingabe_anmeldung(formularName){
	
	var fehlermeldung = '';
	
	/*
	 * sind alle Textfelder gefüllt?
	 */
	
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['anmedlung_email', 'anmedlung_passwort' ]; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['ihre Email-Adresse', 'ihr Passwort'];
	
	fehlermeldung = sindAlleFelderAusgefuellt(felder, meldungswort, formularName);
		
	
	if (fehlermeldung == ''){
		//überprüft, ob die Email-Adresse gültig ist
		if ( checkEmail(document.forms[formularName]['anmedlung_email'].value) == false ){
			fehlermeldung += fehlermeldung == '' ? '' : ' ';
			fehlermeldung += "Die Email-Adresse ist ung&uuml;ltig.";
			
			//Textbox rot umranden
			document.forms[formularName]['anmedlung_email'].style.borderColor = 'red';
			document.forms[formularName]['anmedlung_email'].style.borderStyle = 'solid';
		}
	}
	
	var name_feld_fehlermeldung = formularName == 'anmeldung' ? 'fehlermeldung_anmelden' : 'fehlermeldung_login';
	
	//zeigt die Fehlermeldung auf der Webseite an
	if (fehlermeldung != ''){
		document.getElementById(name_feld_fehlermeldung).innerHTML = fehlermeldung;
	}
	
	//übergibt den Rückgabewert "true", wenn kein Fehler aufgetreten ist. Ist Fehler aufgetreten wird ein "false" ausgegeben
	return fehlermeldung == ''; 
}