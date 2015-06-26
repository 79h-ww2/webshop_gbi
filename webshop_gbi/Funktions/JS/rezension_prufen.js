function vorcheckEingabe_bewertung(){
	
	var fehlermeldung = '';
	
	/*
	 * sind alle Textfelder gefüllt?
	 */
	
	//Array mit allen Feldern, die ausgefüllt sein müssen
	var felder = ['sternbewertung', 'uberschrift_feld', 'rezension_area']; 
	
	//Array mit Meldungswörtern, die in der Fehlermeldung angezeigt werden sollen
	var meldungswort = ['ihre Sternbewertung', 'die Uberschrift', 'ihre Rezension'];
	
	//Array, wo alle nicht ausgefüllten Felder gespeichert werden sollen
	var nicht_ausgefuellte_felder = [];
	
	//überprüft jedes Feld
	for ( var i = 0; i < felder.length; i++){
		if  ( document.forms['form_bewertung'][felder[i]].value == ''){
			nicht_ausgefuellte_felder.push(meldungswort[i]);
			
			//Textbox rot umranden
			document.forms['form_bewertung'][felder[i]].style.borderColor = 'red';
			document.forms['form_bewertung'][felder[i]].style.borderStyle = 'solid';
		}
		else{
			//alte Textboxumrandung löschen, falls der Fehler behoben wurde
			document.forms['form_bewertung'][felder[i]].style.borderColor = '';
			document.forms['form_bewertung'][felder[i]].style.borderStyle = '';
		}
	}
	
	//wenn nicht jedes Feld ausgefüllt ist, wird eine Fehlermeldung generiert
	if (nicht_ausgefuellte_felder.length > 0){
		if ( nicht_ausgefuellte_felder.length == 1){
			fehlermeldung = 'Bitte geben Sie ' +  nicht_ausgefuellte_felder[0] + ' an.';
		}else{
			for (var j = 0; j < nicht_ausgefuellte_felder.length; j++){
				if (j == 0){
					fehlermeldung = 'Bitte geben Sie ' +  nicht_ausgefuellte_felder[j];
				}else if ( j < (nicht_ausgefuellte_felder.length -1)){
					fehlermeldung += ', ' + nicht_ausgefuellte_felder[j];
				}else{
					fehlermeldung += ' und ' + nicht_ausgefuellte_felder[j] + ' an.';
				}
			}
		}
	}
	
	//zeigt die Fehlermeldung auf der Webseite an
	if (fehlermeldung != ''){
		document.getElementById('fehlermeldung_bewertung').innerHTML = fehlermeldung;
	}
	
	//übergibt den Rückgabewert "true", wenn kein Fehler aufgetreten ist. Ist Fehler aufgetreten wird ein "false" ausgegeben
	return fehlermeldung == ''; 
}