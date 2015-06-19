var html = '';
var html2 = '';

/**
 * speichert das Testergebnis ab
 */
function autovervollstaendigung_normale_suche(header)
{
	if ( window.XMLHttpRequest)
	{
		html = new XMLHttpRequest();
		html2 = new XMLHttpRequest();
	}
	else if ( window.ActiveXObject )
	{
		html = new ActiveXObject("Microsoft.XMLHTTP");
		html2 = new ActiveXObject("Microsoft.XMLHTTP");
	}
	else
	{
		//Browser wird nicht unterstützt
	};
	
	document.getElementById('form_suche_normal_autovervollstaendigung_box').style.display= "";
	
	if ( html != "" )
	{
		var url= "";
		
		if ( header == true){ //Suche in der Headerleiste
			var suchwort = document.getElementById('feld_suche_normal').value;
			url = "./Funktions/PHP/ajax_autovervollstaendigung_suche.php?modus=normal&suchwort=" + encodeURI(suchwort);
			html.open("get", url  , true);
			html.onreadystatechange = autovervollstaendigung_normale_suche_result;
			html.send(null);
		}
		else{ //Produktbezeichnung in der erweiterten Suche
			var suchwort = document.getElementById('suche_erweitert_produktbezeichnung').value;
			url = "./Funktions/PHP/ajax_autovervollstaendigung_suche.php?modus=erweitert&suchwort=" + encodeURI(suchwort);
			html2.open("get", url  , true);
			html2.onreadystatechange = autovervollstaendigung_normale_suche_result_erweiterte_suche;
			html2.send(null);
		}
	};
}

/**
 * nimmt den Datenbankresult der Suche entgegen entgegen und zeigt in auf der Webseite an (Suche in der Headerleiste)
 */
function autovervollstaendigung_normale_suche_result(){
	
	if ( html.readyState == 4 && html.responseText != "")	{
		document.getElementById('form_suche_normal_autovervollstaendigung_box').innerHTML = html.responseText;
		document.getElementById('form_suche_normal_autovervollstaendigung_box').style.display= "block";
	}
}

/**
 * nimmt den Datenbankresult der Suche entgegen entgegen und zeigt in auf der Webseite an (Produktbezeichnung in der erweiterten Suche)
 */
function autovervollstaendigung_normale_suche_result_erweiterte_suche(){
	
	if ( html2.readyState == 4 && html2.responseText != "")	{
		document.getElementById('form_erweiterte_suche_autovervollstaendigung_box').innerHTML = html2.responseText;
		document.getElementById('form_erweiterte_suche_autovervollstaendigung_box').style.display= "block";
	}
	else{
		document.getElementById('form_erweiterte_suche_autovervollstaendigung_box').style.display= "none";
	}
}