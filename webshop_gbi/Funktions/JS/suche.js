var html = '';

/**
 * speichert das Testergebnis ab
 */
function autovervollstaendigung_normale_suche()
{
	if ( window.XMLHttpRequest)
	{
		html = new XMLHttpRequest();
	}
	else if ( window.ActiveXObject )
	{
		html = new ActiveXObject("Microsoft.XMLHTTP");
	}
	else
	{
		//Browser wird nicht unterstützt
	};
	
	document.getElementById('form_suche_normal_autovervollstaendigung_box').style.display= "";
	
	if ( html != "" )
	{
		var suchwort = document.getElementById('feld_suche_normal').value;
		var url = "./Funktions/PHP/ajax_autovervollstaendigung_suche.php?modus=normal&suchwort=" + encodeURI(suchwort);

		html.open("get", url  , true);
		html.onreadystatechange = autovervollstaendigung_normale_suche_result;
		html.send(null);
	};
}

/**
 * nimmt den Datenbankresult der Suche entgegen entgegen und zeigt in auf der Webseite an
 */
function autovervollstaendigung_normale_suche_result(){
	
	if ( html.readyState == 4 && html.responseText != "")	{
		document.getElementById('form_suche_normal_autovervollstaendigung_box').innerHTML = html.responseText;
		document.getElementById('form_suche_normal_autovervollstaendigung_box').style.display= "block";
	}
}