var anzahlFensterOffen = 0;


function zeigeMeldungsbox ( idInfobox, titel, meldungstext, icon)
{
	anzahlFensterOffen++;
	document.getElementById('infoBox_' + idInfobox ).style.display = 'block';

	document.getElementById('infoBox_meassage_' + idInfobox).innerHTML = meldungstext;
	document.getElementById('infoBox_titel_' + idInfobox).innerHTML = titel;
	
	var bildname = "";
	switch ( icon )
	{
		case 'info':
			bildname = 'ico_info.png';
		break;
		case 'error':
			bildname = 'ico_fehler.png';
		break;
		case 'question':
			bildname = 'ico_frage.png';
		break;
		case 'warning':
			bildname = 'ico_warnung.png';
		break;
		default:
			bildname = 'ico_info.png';
	}
	
	document.getElementById('meldungsbox_icon_img_' + idInfobox).src = './images/icons_meldungsbox/' + bildname;
	document.getElementById('meldungsbox_icon_img_' + idInfobox).title = icon;
	
	zeigeAbdeckung ( true );
};

function schliesseInfoBox(idInfobox)
{
	document.getElementById('infoBox_' + idInfobox ).style.display = 'none';
	anzahlFensterOffen--;

	if ( anzahlFensterOffen <= 0) zeigeAbdeckung ( false );
};

function zeigeAbdeckung ( BoolVar )
{
	if ( BoolVar )
	{
		 document.getElementById('meldungsfenster_abdeckung' ).style.display = 'block';
	}
	else
	{
		 document.getElementById('meldungsfenster_abdeckung' ).style.display = 'none';
	};
}

//Wartet eine übergebene Zeit, bis die auf der Seite definierte Funktion "aktion_nach_warten()" ausgeführt wird
function warteBox_warten( warteZeit )
{
	setTimeout(function(){
		aktion_nach_warten();
	},warteZeit);
}

//schließt das WarteFenster
function schliesseWarteBox(idWartebox)
{
	document.getElementById('warteBox_' + idWartebox ).style.display = 'none';
	anzahlFensterOffen--;

	if ( anzahlFensterOffen <= 0) zeigeAbdeckung ( false );
};
