<?php
	class Meldungsfenster
	{
		function __construct()
		{

			//css der Meldungsbox einbinden
			echo '<link rel="stylesheet" type="text/css" href="Styles/meldungsfenster.css" />';

			//Java-Script einbinden
			echo '<script type="text/javascript" src="./Funktions/JS/meldungsfenster.js" ></script>';

			//erstellt eine Abdeckung, die dafür sorgt, dass beim geöffneten Meldungsfenster kein Link der Webseite mehr geklickt werden kann
			echo "<div id=\"meldungsfenster_abdeckung\" ></div>";
		}




		//erstellt den Quelltext einer Info-Box ( Box mit Meldung )
		public function erstelleHTMLQuelltextInfoBox_mit_Meldung ( $idInfobox, $titel, $meldungstext, $icon, $onButtonClick, $sichtbar)
		{
			$meldungstext = htmlspecialchars($meldungstext,ENT_QUOTES,'UTF-8');
			$titel = htmlspecialchars($titel,ENT_QUOTES,'UTF-8');
			
			$this->erstelleHTMLQuelltextInfoBox_mit_Meldung_ohne_escapen_von_sonderzeichen ( $idInfobox, $titel, $meldungstext, $icon, $onButtonClick, $sichtbar);
		}
		
		
		//erstellt den Quelltext einer Info-Box ( Box mit Meldung )
		public function erstelleHTMLQuelltextInfoBox_mit_Meldung_ohne_escapen_von_sonderzeichen ( $idInfobox, $titel, $meldungstext, $icon, $onButtonClick, $sichtbar)
		{
			$icon_url = $this->getURLIcon ( $icon );
			$sichtbar_style = ( $sichtbar ) ? "style=\"display:block\"" : "";

			if ( $sichtbar_style ) echo '<script type="text/javascript" >anzahlFensterOffen++; zeigeAbdeckung ( true );</script>';

			
			
			//ließt alle Get-Parameter aus der Adressenleiste aus (nötig, wenn kein Java-Script aktiviert ist)
			//Erstellt eine Adresse für einen Link, der bei deaktivierten JavaScript genutzt werden kann
			$adresse_no_script = ( count($_GET) > 0 ) ?  "./?" : "./";
			
			$get_feldnamen = array_keys($_GET);
			for ( $i = 0; $i < count($_GET); $i++)
			{
				$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
				$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
			
				if ($feldname != "account-activate"){ //Übernimmt nicht den Aktivierungs-Code zur Adresse, damit der Benutzer nicht mehrfach aktiviert wird
					if ( $i > 0) $adresse_no_script .= "&";
					$adresse_no_script .= $feldname."=".$wert;
				}
			}
			
			echo
			"
				<noscript>
					<div id=\"no_javaScript_fensterabdeckung\" ></div>
				</noscript>
				<div id=\"infoBox_".htmlspecialchars($idInfobox,ENT_QUOTES,'UTF-8')."\"  class=\"meldungsfenster_frame_groesse_1\"  ".$sichtbar_style." >
					<div class=\"meldungsbox_titelleiste\" >
						<div class=\"meldungsbox_titelleiste_content\" >
							<span id=\"infoBox_titel_".htmlspecialchars($idInfobox,ENT_QUOTES,'UTF-8')."\" >
								".$titel."
							</span>
							<div class=\"clear_right\" >
							</div>
						</div>
					</div>
					<div class=\"meldungsbox_content\" >
						<div class=\"meldungsbox_icon\" >
							<img id=\"meldungsbox_icon_img_".htmlspecialchars($idInfobox,ENT_QUOTES,'UTF-8')."\" src=\"".$icon_url."\" title=\"".htmlspecialchars($icon,ENT_QUOTES,'UTF-8')."\" >
						</div>
						<div class=\"meldungsbox_content_meassage\" id=\"infoBox_meassage_".htmlspecialchars($idInfobox,ENT_QUOTES,'UTF-8')."\" >
							".$meldungstext."
						</div>
						<div class=\"clear_left\" >
						</div>
						<div class=\"gruppe_button_meldungsbox\" >
							<noscript>
								<a  class=\"link_button_msgbox .link_button_msgbox\" href=\"$adresse_no_script\" >Ok</a>
							</noscript>
							<script type=\"text/javascript\">
								document.write('<input type=\"button\" class=\"button_meldungsbox\" onclick=\"schliesseInfoBox(\'".htmlspecialchars($idInfobox,ENT_QUOTES,'UTF-8')."\'); $onButtonClick\" value=\"OK\"  >');
							</script>
						</div>
						<div class=\"clear_right\" >
						</div>
					</div>
				</div>
			";
		}
		
		
		//erstellt die Meldungsbox, die angezeigt wird, wenn kein JavaScript beim Browser aktiviert ist
		public function erstelleMeldungsboxKeinJavascriptAktiviert()
		{
			//die Seite mit einen DIV abgedecken, damit kein Link, Button usw. mehr angeklickt werden kann
			echo '<div id="no_javaScript_fensterabdeckung" ></div>';
			
			echo
			"
				<div   class=\"meldungsfenster_frame_no_javaScript\" >
					<div class=\"meldungsbox_titelleiste\" >
						<div class=\"meldungsbox_titelleiste_content\" >
							
							<span>
								kein JavaScript aktiviert
							</span>

						</div>
					</div>
					<div class=\"meldungsbox_content\" >
						<form method=\"get\" action=\"".$_SERVER["PHP_SELF"]."\" >
							<div class=\"meldungsbox_icon\" >
								<img  src=\"".$this->getURLIcon ( 'warning' )."\" title=\"Warnung\" >
							</div>
							<div class=\"meldungsbox_content_meassage\"  >
								Diese Seite ben&ouml;tigt JavaScript, damit sie ausgef&uuml;hrt werden kann. Bei Ihren Browser wurde allerdings JavaScript deaktiviert, sodass die Seite zur Zeit nicht ausgef&uuml;hrt werden kann.
							</div>
							<div class=\"clear_left\" >
							</div>
							<div class=\"gruppe_button_meldungsbox\" >
								<input type=\"submit\" class=\"button_meldungsbox\" value=\"Seite neu laden\"  >
							</div>
							<div class=\"clear_right\" >
							</div>
						</form>
					</div>
				</div>
			";
		}


		//erstellt den Quelltext einer Info-Box ( Box ohne Meldung )
		public function erstelleHTMLQuelltextInfoBox ( $idInfobox, $onButtonClick)
		{
			$this->erstelleHTMLQuelltextInfoBox_mit_Meldung ( $idInfobox, "", "", "" , $onButtonClick , false);
		}





		//gibt die Adresse des gewählten Icons aus
		public function getURLIcon ( $symbol )
		{
			$URL = "";
			switch ( $symbol )
			{
				case 'info':
					$URL = "./Images/icons_meldungsbox/ico_info.png";
				break;
				case 'error':
					$URL = "./Images/icons_meldungsbox/ico_fehler.png";
				break;
				case 'question':
					$URL = "./Images/icons_meldungsbox/ico_frage.png";
				break;
				case 'warning':
				default:
					$URL = "./Images/icons_meldungsbox/ico_warnung.png";
				break;
			};

			return $URL;
		}

		//erstellt den Quelltext einer Confirmbox ( ohne Meldungstext )
		public function erstelleHTMLQuelltextConfirmBox ( $idBox, $onButton1_Click, $onButton2_Click, $aufschriftButton1, $aufschriftButton2 )
		{
			$this->erstelleHTMLQuelltextConfirmBox_mit_Meldung ( $idBox, "", "", "question" ,$onButton1_Click, $onButton2_Click,$aufschriftButton1, $aufschriftButton2,  false );
		}

		public function erstelleHTMLQuelltextConfirmBox_mit_Meldung ( $idBox, $titel, $meldungstext, $icon ,$onButton1_Click, $onButton2_Click, $aufschriftButton1, $aufschriftButton2,  $sichtbar )
		{
			$icon_url = $this->getURLIcon ( $icon );
			$sichtbar_style = ( $sichtbar ) ? "style=\"display:block\"" : "";

			if ( $sichtbar_style ) echo '<script type="text/javascript" >anzahlFensterOffen++; zeigeAbdeckung ( true );</script>';

			//ließt alle Get-Parameter aus der Adressenleiste aus (nötig, wenn kein Java-Script aktiviert ist)
			//Erstellt eine Adresse für einen Link, der bei deaktivierten JavaScript genutzt werden kann
			$adresse_no_script = ( count($_GET) > 0 ) ?  "./?" : ".";
				
			$get_feldnamen = array_keys($_GET);
			for ( $i = 0; $i < count($_GET); $i++)
			{
			$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
					$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
		
							if ( $i > 0) $adresse_no_script .= "&";
			
							$adresse_no_script .= $feldname."=".$wert;
			}
			
			echo
			"
				<noscript>
					<div id=\"no_javaScript_fensterabdeckung\" ></div>
				</noscript>
				<div id=\"infoBox_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\"  class=\"meldungsfenster_frame_groesse_1\"  ".$sichtbar_style." >
					<div class=\"meldungsbox_titelleiste\" >
						<div class=\"meldungsbox_titelleiste_content\" >
							<a class=\"schliessen_button_meldungsfenster\" href=\"#\" title=\"Schlie&szlig;en\" onclick=\"schliesseInfoBox('".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."');\" >
								X
							</a>
							<span id=\"infoBox_titel_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\" >
								".htmlspecialchars($titel,ENT_QUOTES,'UTF-8')."
							</span>
							<div class=\"clear_right\" >
							</div>
						</div>
					</div>
					<div class=\"meldungsbox_content\" >
						<img id=\"meldungsbox_icon_img_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\" class=\"meldungsbox_icon\" src=\"".$icon_url."\" title=\"".htmlspecialchars($icon,ENT_QUOTES,'UTF-8')."\" >
						<div class=\"meldungsbox_content_meassage\" id=\"infoBox_meassage_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\" >
							".htmlspecialchars($meldungstext,ENT_QUOTES,'UTF-8')."
						</div>
						<div class=\"clear_left\" >
						</div>
						<div class=\"gruppe_button_meldungsbox\" >
							<input type=\"button\"  id=\"meldungsbox_button1_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\"    class=\"button_meldungsbox\" onclick=\"schliesseInfoBox('".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."'); $onButton1_Click\" value=\"".htmlspecialchars($aufschriftButton1,ENT_QUOTES,'UTF-8')."\"  > 
							<input type=\"button\"   id=\"meldungsbox_button2".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\"  class=\"button_meldungsbox\" onclick=\"schliesseInfoBox('".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."'); $onButton2_Click\" value=\"".htmlspecialchars($aufschriftButton2,ENT_QUOTES,'UTF-8')."\"  >
						</div>
						<div class=\"clear_right\" >
						</div>
					</div>
				</div>
			";
		}
		
		
		//erstellt den Quelltext eines "Wartefensters"
		public function erstelleHTMLQuelltextWarteFenster ( $idWartebox, $sichtbar, $warte_zeit, $titel, $js_script_nach_warte_zeit)
		{
			$sichtbar_style = ( $sichtbar ) ? "style=\"display:block\"" : "";

			if ( $sichtbar_style ) echo '<script type="text/javascript" >anzahlFensterOffen++; zeigeAbdeckung ( true );</script>';
			
			//wenn die Wartezeit größer null ist und das sichtbar, läuft der Timer rückwärts und startet nach Ablauf der Zeit automatisch den angegebenen Skript
			if ($warte_zeit > 0 && $sichtbar )
			{
				echo
				"
					<script type=\"text/javascript\" >
					
						//Wartet eine übergebene Zeit, bis 'aktion_nach_warten()' ausgeführt wird
						var warteZeit  = ".htmlspecialchars($warte_zeit,ENT_QUOTES,'UTF-8').";
						warteBox_warten( warteZeit );
												
						//Funktion, die nach dem Warten ausgeführt wird
						function aktion_nach_warten()
						{
							//Warte-Box wird geschlossen
							 schliesseWarteBox('".htmlspecialchars($idWartebox,ENT_QUOTES,'UTF-8')."');
							 
							//übergebene Skript
							$js_script_nach_warte_zeit;
						}
					</script>
				";
			}

			echo
			"
				<div id=\"warteBox_".htmlspecialchars($idWartebox,ENT_QUOTES,'UTF-8')."\"  class=\"meldungsfenster_frame_groesse_1\"  ".$sichtbar_style." >
					<div class=\"meldungsbox_titelleiste\" >
						<div class=\"meldungsbox_titelleiste_content\" >
							<span id=\"infoBox_titel_".htmlspecialchars($idWartebox,ENT_QUOTES,'UTF-8')."\" >
								".htmlspecialchars($titel,ENT_QUOTES,'UTF-8')."
							</span>
						</div>
					</div>
					<div class=\"meldungsbox_content_pause\" >
						<div class=\"meldungsbox_icon_pause\" >
							<img title=\"Uhr\" src=\"./Images/icons_meldungsbox/icon_clock.png\" alt=\"Uhr\" >
						</div>
						<div class=\"meldungsbox_content_meassage_pause\"  >
							Bitte warten ...
						</div>
					</div>
				</div>
			";
		}
	}
?>
