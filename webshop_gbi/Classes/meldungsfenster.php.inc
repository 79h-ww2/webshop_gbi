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
			$adresse_no_script = "./";
			
			$get_feldnamen = array_keys($_GET);
			$z = 0;
			for ( $i = 0; $i < count($_GET); $i++)
			{
				$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
				$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
			
				if ($feldname != "account-activate"){ //Übernimmt nicht den Aktivierungs-Code zur Adresse, damit der Benutzer nicht mehrfach aktiviert wird
					$adresse_no_script .= ( $z > 0) ? "&" : "?";
					$adresse_no_script .= $feldname."=".$wert;
					$z++;
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

		public function erstelleHTMLQuelltextConfirmBox_mit_Meldung ( $idBox, $titel, $meldungstext, $icon ,$aktionsnameButton1, $aktionsparamButton1, $aktionsnameButton2 ,$aktionsparamButton2, $aufschriftButton1, $aufschriftButton2,  $sichtbar )
		{
			$icon_url = $this->getURLIcon ( $icon );
			$sichtbar_style = ( $sichtbar ) ? "style=\"display:block\"" : "";

			if ( $sichtbar_style ) echo '<script type="text/javascript" >anzahlFensterOffen++; zeigeAbdeckung ( true );</script>';

			//ließt alle Get-Parameter aus der Adressenleiste aus (nötig, wenn kein Java-Script aktiviert ist)
			//Erstellt eine Adresse für einen Link, der bei deaktivierten JavaScript genutzt werden kann
			$adresse_no_script = "./?";
				
			$get_feldnamen = array_keys($_GET);
			$z = 0;
			for ( $i = 0; $i < count($_GET); $i++)
			{
				$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
				$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
		
				//übernimmt die Parameter von die 
				if ( $feldname != "aktion" && $feldname != "aktionparam"){
					if ( $z > 0) $adresse_no_script .=  "&";
					$adresse_no_script .= $feldname."=".$wert;
					$z++;
				}
			}
			
			echo
			"
				<noscript>
					<div id=\"no_javaScript_fensterabdeckung\" ></div>
				</noscript>
				<div id=\"infoBox_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\"  class=\"meldungsfenster_frame_groesse_1\"  ".$sichtbar_style." >
					<div class=\"meldungsbox_titelleiste\" >
						<div class=\"meldungsbox_titelleiste_content\" >
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
			";
			
			$trennzeichen = ($z > 0) ? "&" : "";
			
			
			echo
			"
							<a  class=\"link_button_msgbox link_button_msgbox\" href=\"".$adresse_no_script.$trennzeichen."aktion=".htmlspecialchars ($aktionsnameButton1,ENT_QUOTES,'UTF-8')."&aktionparam=".htmlspecialchars($aktionsparamButton1,ENT_QUOTES,'UTF-8')."\" >".htmlspecialchars($aufschriftButton1,ENT_QUOTES,'UTF-8')."</a>
							<a  class=\"link_button_msgbox link_button_msgbox\" href=\"".$adresse_no_script.$trennzeichen."aktion=".htmlspecialchars ($aktionsnameButton2,ENT_QUOTES,'UTF-8')."&aktionparam=".htmlspecialchars($aktionsparamButton2,ENT_QUOTES,'UTF-8')."\" >".htmlspecialchars($aufschriftButton2,ENT_QUOTES,'UTF-8')."</a>
							<!--<input type=\"button\"  id=\"meldungsbox_button1_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\"    class=\"button_meldungsbox\" onclick=\"schliesseInfoBox('".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."');\" value=\"".htmlspecialchars($aufschriftButton1,ENT_QUOTES,'UTF-8')."\"  > 
							<input type=\"button\"   id=\"meldungsbox_button2".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\"  class=\"button_meldungsbox\" onclick=\"schliesseInfoBox('".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."');\" value=\"".htmlspecialchars($aufschriftButton2,ENT_QUOTES,'UTF-8')."\"  >-->
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
		
		/**
		 * Erstellt ein Input-Fenster, wo der Benutzer ein en Wert für die Webseite eingeben kann
		 * @param unknown $idBox ID des Fensters
		 * @param unknown $titel Titel des Fensters
		 * @param unknown $meldungstext Meldungstext im Fenster
		 * @param unknown $textfeldBeschriftung Label, der das Textfeld beschriftet
		 * @param unknown $textfeldname Name des Textfelds. Unter diesen Namen werden die Daten übertragen
		 * @param unknown $aufschriftButton1 Aufschrift des ersten Buttons
		 * @param unknown $aufschriftButtonAbbrechen Aufschrift des Abbrechen-Buttons
		 * @param unknown $formActionLink Action-Link des Fensterformulars
		 * @param unknown $uebertragungsmethode Übertragungsmethode des Fensterformulars
		 * @param unknown $sichtbar Sichtbarkeit des Fensters
		 * @param unknown $js_eingabe_vorcheck JavaScript-Methode, die vor den Absenden die Eingabe des Formulars prüft
		 * @param unknown $js_id_fehlermeldung JavaScript-ID des Divs, wo die Fehlermeldung angezeigt werden soll, wenn die Eingabe nicht gültig war
		 * @param unknown $fehlermeldung Fehlermeldung (serverseitig programmiert)
		 * @param unknown $wertTextfeld Wert, der im Textfeld stehen soll
		 * @param unknown $form_name Name des Übertragungsformulars
		 * @param unknown $textfeld_breite gibt die Breite des Textfeldes an
		 * @param unknown $popupAufgabe Legt die Aufgabe fest, wofür das Popup verwendet wird
		 */
		public function erstelleHTMLQuelltextTextinputbox ($idBox, $titel, $meldungstext, $textfeldBeschriftung, $textfeldname ,$aufschriftButton1, $aufschriftButtonAbbrechen, $formActionLink, $uebertragungsmethode ,  $sichtbar, $js_eingabe_vorcheck, $js_id_fehlermeldung, $fehlermeldung, $wertTextfeld, $form_name, $textfeld_breite, $popupAufgabe)
		{
			$sichtbar_style = ( $sichtbar ) ? "style=\"display:block\"" : "";
		
			if ( $sichtbar_style ) echo '<script type="text/javascript" >anzahlFensterOffen++; zeigeAbdeckung ( true );</script>';
		
			//ließt alle Get-Parameter aus der Adressenleiste aus (nötig, wenn kein Java-Script aktiviert ist)
			//Erstellt eine Adresse für einen Link, der bei deaktivierten JavaScript genutzt werden kann
			$adresse_no_script = "./?";
		
			$get_feldnamen = array_keys($_GET);
			$z = 0;
			for ( $i = 0; $i < count($_GET); $i++)
			{
			$wert = htmlspecialchars ($_GET[$get_feldnamen[$i]],ENT_QUOTES,'ISO8859-1');
					$feldname = htmlspecialchars ($get_feldnamen[$i],ENT_QUOTES,'ISO8859-1');
		
							//übernimmt die Parameter von die
							if ( $feldname != "aktion" && $feldname != "aktionparam"){
									if ( $z > 0) $adresse_no_script .=  "&";
									$adresse_no_script .= $feldname."=".$wert;
									$z++;
									}
			}
				
			$textfeldumrandung = ($fehlermeldung != "") ? "border-color:red;" : "";
			
			echo
			"
				<noscript>
					<div id=\"no_javaScript_fensterabdeckung\" ></div>
				</noscript>
				<div id=\"infoBox_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\"  class=\"meldungsfenster_frame_groesse_1\"  ".$sichtbar_style." >
					<div class=\"meldungsbox_titelleiste\" >
						<div class=\"meldungsbox_titelleiste_content\" >
							<span id=\"infoBox_titel_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\" >
								".htmlspecialchars($titel,ENT_QUOTES,'UTF-8')."
							</span>
							<div class=\"clear_right\" >
							</div>
						</div>
					</div>
					<div class=\"meldungsbox_content\" >
						<form action=\"$formActionLink\" name=\"".htmlspecialchars($form_name,ENT_QUOTES,'UTF-8')."\" method=\"".htmlspecialchars($uebertragungsmethode,ENT_QUOTES,'UTF-8')."\" onsubmit=\"return $js_eingabe_vorcheck\" >
							<input type=\"hidden\" name=\"idBox\" value=\"$idBox\" />
							<input type=\"hidden\" name=\"type\" value=\"".htmlspecialchars($popupAufgabe,ENT_QUOTES,'UTF-8')."\" />
							<div class=\"meldungsbox_content_meassage\" id=\"infoBox_meassage_".htmlspecialchars($idBox,ENT_QUOTES,'UTF-8')."\" >
								<b>".htmlspecialchars($meldungstext,ENT_QUOTES,'UTF-8')."</b>
							</div>
							<div class=\"clear_left\" >
							</div>
							<div class=\"input_box_textfeldbereich\" >
								<label for=\"".htmlspecialchars($textfeldname,ENT_QUOTES,'UTF-8')."\">".htmlspecialchars($textfeldBeschriftung,ENT_QUOTES,'UTF-8').":</label>
								<input style=\"width:$textfeld_breite;$textfeldumrandung\" name=\"".htmlspecialchars($textfeldname,ENT_QUOTES,'UTF-8')."\" type=\"text\"  value=\"".htmlspecialchars($wertTextfeld,ENT_QUOTES,'UTF-8')."\" />
							</div>
							<div class=\"clear_right\" >
								<div class=\"fehlermeldung_input_popup\" id=\"".htmlspecialchars($js_id_fehlermeldung,ENT_QUOTES,'UTF-8')."\" >".htmlspecialchars($fehlermeldung,ENT_QUOTES,'UTF-8')."</div>
							</div>
							<div class=\"gruppe_button_meldungsbox\" >
			";
				
			$trennzeichen = ($z > 0) ? "&" : "";
			
				
			echo
			"
								<input type=\"submit\" name=\"submit\" value=\"".htmlspecialchars($aufschriftButton1,ENT_QUOTES,'UTF-8')."\" />
								<a class=\"grauer_link_button link_button_msgbox\" href=\"".$adresse_no_script.$trennzeichen."aktion=abbrechen&aktionparam=abbrechen_button\" >".htmlspecialchars($aufschriftButtonAbbrechen,ENT_QUOTES,'UTF-8')."</a>
							</div>
							<div class=\"clear_right\" >
							</div>
						</form>
					</div>
				</div>
			";
		}
		
	}
?>
