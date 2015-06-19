/**
 * die Email-Adresse prüfen
 * Quelle: http://www.w3resource.com/javascript/form/email-validation.php
 * @param {String} email Die Email-Adresse, die überprüft werden soll
 * @returns {Boolean} Gibt aus, ob die Email-Adresse gültig ist 
 */
function checkEmail(email)
{
	return /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(email);
}

/**
 * Überprüft, ob es sich um eine Nummer handelt
 * @param {String} input
 * @returns {Boolean}
 */
function isNumeric(input)
{
    return (input - 0) == input && (''+input).trim().length > 0;
}

/**
 * Überprüft, ob alle Felder ausgefüllt sind
 * @param felder Array mit den Feldnamen
 * @param meldungswoerter Array mit den Meldungswörtern für die temp_fehlermeldung
 * @param formular Name des Formulars, wo sich die Textfelder befinden
 * @returns Gibt die temp_fehlermeldung aus, wenn nicht alle Textfelder ausgefüllt sind
 */
function sindAlleFelderAusgefuellt(felder, meldungswort, formular){
	//Array, wo alle nicht ausgefüllten Felder gespeichert werden sollen
	var nicht_ausgefuellte_felder = [];
	
	var temp_fehlermeldung = '';
	
	//überprüft jedes Feld
	for ( var i = 0; i < felder.length; i++){
		if  ( document.forms[formular][felder[i]].value == ''){
			nicht_ausgefuellte_felder.push(meldungswort[i]);
			
			//Textbox rot umranden
			document.forms[formular][felder[i]].style.borderColor = 'red';
			document.forms[formular][felder[i]].style.borderStyle = 'solid';
		}
		else{
			//alte Textboxumrandung löschen, falls der Fehler behoben wurde
			document.forms[formular][felder[i]].style.borderColor = '';
			document.forms[formular][felder[i]].style.borderStyle = '';
		}
	}
	
	//wenn nicht jedes Feld ausgefüllt ist, wird eine temp_fehlermeldung generiert
	if (nicht_ausgefuellte_felder.length > 0){
		if ( nicht_ausgefuellte_felder.length == 1){
			temp_fehlermeldung = 'Bitte geben Sie ' +  nicht_ausgefuellte_felder[0] + ' an.';
		}else{
			for (var j = 0; j < nicht_ausgefuellte_felder.length; j++){
				if (j == 0){
					temp_fehlermeldung = 'Bitte geben Sie ' +  nicht_ausgefuellte_felder[j];
				}else if ( j < (nicht_ausgefuellte_felder.length -1)){
					temp_fehlermeldung += ', ' + nicht_ausgefuellte_felder[j];
				}else{
					temp_fehlermeldung += ' und ' + nicht_ausgefuellte_felder[j] + ' an.';
				}
			}
		}
	}
	
	return temp_fehlermeldung;
}