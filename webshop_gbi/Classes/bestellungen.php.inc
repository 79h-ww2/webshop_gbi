<?php 
	include_once "Classes/EingabeCheckGrundlegend.php.inc";
	include_once 'Classes/bestellungenslisteneintrag.php.inc';
	include_once 'Classes/Kunde.php.inc';
	include_once 'Classes/datenbank.php.inc';
	include_once 'Classes/warenkorb.php.inc';
	include_once 'Classes/warenkorbeintrag.php.inc';
	
	/**
	 * Ließt die Bankdaten der Firma GBI aus der Config-Datei ein
	 * @return multitype:string
	 */
	function get_konto_daten_gbi(){
		global $bankdaten_gbi;
		return  $bankdaten_gbi;
	}
	
	/**
	 * Diese Klasse dient dazu die Bestellungen zu verwalten
	 */
	class Bestellungen extends EingabeCheckGrundlegend{
		
		/**
		 * Konstruktor
		 */
		function __construct(){
			
			//erstellt eine Server-SESSION-Variable, um vorübergehend die Bestellungseinstellungen zu speichern
			if (!isset($_SESSION["bestellungenslisteneintrag"])){
				$_SESSION["bestellungenslisteneintrag"] = new Bestellungenslisteneintrag();
			}
		}
		
		/**
		 * Gibt die zwischengespeicherten Bestellungseinstellungen aus 
		 * @return Bestellungenslisteneintrag
		 */
		public function get_zwischengespeicherte_bestellungseinstellungen(){
			return $_SESSION["bestellungenslisteneintrag"];
		}
		
		/**
		 * Übergibt die Bestellungseinstellungen, die zwischengespeichert werden sollen
		 * @param Bestellungenslisteneintrag $bestellungseinstellungen Die Bestellungseinstellungen
		 */
		public function set_zwischengespeicherte_bestellungseinstellungen($bestellungseinstellungen){
			$_SESSION["bestellungenslisteneintrag"] = $bestellungseinstellungen;
		}
		
		/**
		 * Die Bestellung wird abgesendet
		 * @return boolean Gibt an, ob die Bestellung erfolgreich in der Datenbank gespeichert wurde
		 */
		public function zwischengespeicherter_bestellungslisteneintrag_bestellen(){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$kunde1 = new Kunden();
			
			//Sonderzeichen entfernen
			$kid = $db->db_real_escape_string($kunde1->get_kid_from_email($_SESSION['angemeldet']));
			$zahlungsart = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_zahlungsart());
			$versandart = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_versandart());
			$iban = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_iban());
			$bic = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_bic());
			$kinhaber = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_kontoinhaber());
			$lgeschlecht = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_geschlecht());
			$lvorname = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_vorname());
			$lname = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_name());
			$lstrasse = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_strasse());
			$lhausnummer = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_hausnr());
			$lplz = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_plz());
			$lort = $db->db_real_escape_string($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_ort());
			
			$query = "
					insert into bestellung
					(
						KId,
						Status,
						Datum,
						Zahlungsart,
						stand,
						versandart,
						geloescht,
						bankeinzug_iban,
						bankeinzug_bic,
						bankeinzug_kontoinhaber,
						lieferadresse_geschlecht,
						lieferadresse_vorname,
						lieferadresse_name,
						lieferadresse_strasse,
						lieferadresse_hausnummer,
						lieferadresse_plz,
						lieferadresse_ort
					)
					values
					(
						'$kid',
						'Auftrag erhalten',
						now(),
						'$zahlungsart',
						now(),
						'$versandart',
						'nein',
						'$iban',
						'$bic',
						'$kinhaber',
						'$lgeschlecht',
						'$lvorname',
						'$lname',
						'$lstrasse',
						'$lhausnummer',
						'$lplz',
						'$lort'
					);
			";
			
			$result = $db->db_query($query);
						
			//Datenbankverbindung schließen
			$db->db_close();
			
			$erfolgreich = ( !$result ) ? false : true;
			
			//Wenn die Bestellung erfolgreich erstellt wurde, wird die Bestellungsnummer ermittelt und der Warenkorb zur Bestellung hinzugefügt
			if ($erfolgreich){
				//Bestellungsnummer ermitteln
				$bestId = $this->bestimme_bestellunger_letzte_bestellung_kunde($kid);
				
				//Warenkorbprodukte zur Bestellung hinzufügen
				$erfolgreich = $this->warenkorb_produkte_in_bestellung_einfuegen($bestId);
			}
			
			return $erfolgreich;
		}
		
		/**
		 * Gibt die letzte Bestellungsnummer eines Kundens aus
		 * @param integer $kundennr Die Kundennummer des Kundens
		 * @return Ambigous <string, int> Die Bestellnummer
		 */
		public function bestimme_bestellunger_letzte_bestellung_kunde($kundennr){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$kundennr = $db->db_real_escape_string($kundennr);
			
			$query = "select BestId from bestellung where KId='$kundennr' order by BestId desc limit 0,1;";
			
			$result = $db->db_query($query);
			
			$bid = "";
			while($werte = $db->db_fetch_array($result)){
				$bid = $werte[0];
			}
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			return $bid;
		}
		
		
		/**
		 * Fügt die Produkt aus dem Warenkorb zur Bestellung hinzu
		 * @param unknown $bestellnummer Nummer der Bestellung
		 * @return boolean
		 */
		public function warenkorb_produkte_in_bestellung_einfuegen($bestellnummer){
			//Verbindung zur Datenbank aufbauen
			$db = datenbank_verbindung_aufbauen();
			if ( !($db->db_connect()) ) die ("Es konnte keine Verbindung zur Datenbank aufgebaut werden");
			
			$bestellnummer = $db->db_real_escape_string($bestellnummer);
			
			$warenkorb1 = new warenkorb();
			$Artikel = $warenkorb1->artikel_im_warenkorb_anzeigen();
			
			$query = "insert into bestellprodukte (BestId, PId, Menge) values ";
			
			//fügt jeden Eintrag im Warenkorb zum Insert-Befehl hinzu
			for ($i = 0; $i < count($Artikel); $i++){
				if ( $i > 0) $query.=",";
				$eintrag = $Artikel[$i];
				$menge = $db->db_real_escape_string($eintrag->get_menge());
				$artikelnummer = $db->db_real_escape_string($eintrag->get_artikelnummer());
				$query.="('$bestellnummer', '$artikelnummer', '$menge')";
			}
			
			
			$result = false;
			
			//wenn Artikel im Warenkorb vorhanden sind, wird der Insert-Befehl ausgeführt
			if (count($Artikel) > 0){
				$result = $db->db_query($query);
			}
			
			
			//Datenbankverbindung schließen
			$db->db_close();
			
			return (!$result) ? false : true;
		}
		
		/**
		 * Sendet eine Bestätigungs Email, die den Kunden über den Erhalt der Bestellung informiert
		 * @return boolean Gibt an, ob das Versenden der Email erfolgreich war
		 */
		public function sende_bestaetigungs_email(){
		
			$skript_name = 'index.php';
			$warenkorb1 = new warenkorb();
			
			
			$datum = date("d.m.Y", time());
			
			$kunde1 = new Kunden();
			
			//Anredesatz erstellen
			//Kundennr bestimmen
			$kid = $kunde1->get_kid_from_email($_SESSION['angemeldet']);
			$anrede = ($kunde1->get_geschlecht_from_kid($kid) == "weiblich") ? "Sehr geehrte Frau " : "Sehr geehrter Herr ";
			$kunden_namen = $kunde1->get_vorname_from_kid($kid)." ".$kunde1->get_name_from_kid($kid);
		
			$html_code_email =
			'
			<!DOCTYPE html>
			<html>
				<head>
					<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
					<title>Best&auml;tigungs-Email des Webshop GBI zur Bestellung vom '.$datum.'</title>
					<style type="text/css" >
						header{
							background: transparent linear-gradient(to right bottom, #6C7B35, #82A143, #788A5F) repeat scroll 0% 0%;
							display:block;
							width: 1004px;
							padding: 10px;
							margin: 0px auto;
						}
		
						img.logo{
							width: 128px;
						}
		
						body{
							background: #808080 none repeat scroll 0% 0%;
							color: #000305;
							font-family: Arial,"Lucida Sans Unicode";
							line-height: 1.5;
							text-align: left;
						}
		
						.content{
							background-color: #fff;
							margin: 0px auto;
							width: 924px;
							display: block;
							padding-left: 50px;
							padding-right: 50px;
							padding-top: 5px;
							padding-bottom: 15px;
						}
		
						h2{
							color:#D56509;
						}
		
						ul{
							padding-top: 0px;
							margin-top: 0px;
						}
		
						.ueberschriften{
							font-weight: bold;
							font-size: 20px;
							margin-top:20px;
						}
					
						.UeberschriftWarenkorb{
							font-weight: bold;
						}
					
						.auflistung_warenkorb{
							margin: 0px auto;
							display: table;
							width:800px;
						}
					
						.ArtikelbildWarenkorb, .ArtikelnameWarenkorb, .ArtikelmengeWarenkorb, .ArtikelPreisWarenkorb, .ArtikelLoeschenWarenkorb, .ArtikelmarkiercheckboxWarenkorb{
							display: table-cell;
							text-align: center;
							padding-left: 10px;
							padding-top: 10px;
							vertical-align: middle;
							border-bottom: solid 1px;
						}
					
						.ArtikelbildWarenkorb{
							width: 100px;
						}
					
						.Artikelbild{
							width: 100px;
							border-radius: 8px;
							-moz-border-radius: 8px;
    						-webkit-border-radius: 8px;
    						background-color: white;
    						padding: 4px;
						}
					
						.auflistung_warenkorb .aktuelleArtikelimWarenkorb .ArtikelnameWarenkorb{
							width:450px;
						}

						.auflistung_warenkorb .aktuelleArtikelimWarenkorb .ArtikelmengeWarenkorb{
							width:90px;
						}
					
						.auflistung_warenkorb .aktuelleArtikelimWarenkorb .ArtikelPreisWarenkorb{
							width:120px;
						}
					
						.ArtikelPreisWarenkorb{
							text-align: right;
						}
					
						a{
							text-decoration: none;
							color: #D56509; 
						}
							
						.ArtikelwarenkorbSummenZeile{
							border-bottom: medium none;
						}
							
						.Zahlungsart{
							display: table;
						}
							
						.zahlungsart_felder{
							display: table-cell;
							width:250px;
						}
							
						.rot{
							margin-top: 30px;
							font-weight: bold;
							color: red;
							padding-bottom:30px;
						}
							
						.rot ul{
							margin-top: 15px;
						}
					
					</style>
				</head>
			<body>
		<header>
			<img class="logo" src="http://'.$_SERVER["SERVER_ADDR"].str_replace($skript_name,"",$_SERVER["PHP_SELF"]).'/Images/Design/Logo/fahrrad.png" alt="Firmenlogo" />
		</header>
		<div class="content" >
			<h2>Best&auml;tigungs-Email des Webshop GBI zur Bestellung vom '.$datum.'</h2>
			'.$anrede.' '.htmlspecialchars($kunden_namen,ENT_QUOTES,'UTF-8').',
			<p>vielen Dank für Ihre Bestellung beim Webshop der Firma GBI. Mit dieser Email bestätigen wird den Erhalt Ihrer Bestellung.</p>
			<p>Sobald Ihre Zahlung bei uns eingegangen ist, wird Ihre Bestellung versendet. Wenn die Ware noch nicht versendet wurde, können Sie selbstverstänlich noch Änderungen an der Bestellung auf der Webseite durchführen.</p>
		
			<p>Damit Sie nochmal alle Detail der Bestellung überprüfen können, werden diese nochmal in dieser Email mitgesendet.</p>
			<div class="ueberschriften" >Versandart:</div>
			<ul>
				<li>'.htmlspecialchars(ucwords($this->get_zwischengespeicherte_bestellungseinstellungen()->get_versandart()),ENT_QUOTES,'UTF-8').'</li>
			</ul>
			<div class="ueberschriften" >Warenkorb:</div>
		
			<!-- ############################################################## -->
		
			<div class="auflistung_warenkorb" >
				<div class="aktuelleArtikelimWarenkorb" >
					<div class="ArtikelbildWarenkorb UeberschriftWarenkorb">Bild</div>
					<div class="ArtikelnameWarenkorb UeberschriftWarenkorb">Name</div>
					<div class="ArtikelmengeWarenkorb UeberschriftWarenkorb">Menge</div>
					<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb">Einzelpreis</div>
					<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb">Gesamtpreis</div>
				</div>
		';
		
		//Listet die Produkte des Warenkorbs auf
		$Artikel = $warenkorb1->artikel_im_warenkorb_anzeigen();
		for ($i = 0; $i < count($Artikel) && $i<4; $i++){
			$AktuellerArtikel = $Artikel[$i];
			$html_code_email .=
			'
				<div class="aktuelleArtikelimWarenkorb" >
						<div class="ArtikelbildWarenkorb ">
							<a class="ArtikelnameWarenkorbhyper" href="http://'.$_SERVER["SERVER_ADDR"].str_replace($skript_name,"",$_SERVER["PHP_SELF"]).'?page=produkt&pid='.htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, "UTF-8").'"><img class="Artikelbild" alt="Artikelbild" title="'.htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8' ).'" src="http://'.$_SERVER["SERVER_ADDR"].str_replace($skript_name,"",$_SERVER["PHP_SELF"]).$AktuellerArtikel->get_artikelbild().'" ></a>
						</div>
						<div class="ArtikelnameWarenkorb "> <a class="ArtikelnameWarenkorbhyper" href="./?page=produkt&pid='.htmlspecialchars ( $AktuellerArtikel->get_artikelnummer(), ENT_QUOTES, 'UTF-8').'">'.htmlspecialchars ( $AktuellerArtikel->get_artikelnamen(), ENT_QUOTES, 'UTF-8').'</a> </div>
						<div class="ArtikelmengeWarenkorb ">
							'.htmlspecialchars ( $AktuellerArtikel->get_menge(), ENT_QUOTES, 'UTF-8' ).'
						</div>
						<div class="ArtikelPreisWarenkorb">'.number_format($AktuellerArtikel->get_einzelpreis_artikel(),2, ",", "").' &euro;</div>
						<div class="ArtikelPreisWarenkorb">'.number_format($AktuellerArtikel->get_gesamtpreis_artikel(),2, ",", "").' &euro;</div>
				</div>
			';
		}
		
		//Berechung der Versandkosten
		$versandart = $this->get_zwischengespeicherte_bestellungseinstellungen()->get_versandart();
		$versandkosten = 0;
		
		if ($versandart == "standardversand" && $warenkorb1->get_gesamtpreis_artikel_im_warenkorb() <= 25 ){
			$versandkosten= 4;
		}elseif ($versandart == "expressversand"){
			$versandkosten=13;
		}
		
		
		$html_code_email .= '
			<div class="aktuelleArtikelimWarenkorb" >
				<div class="ArtikelbildWarenkorb ArtikelwarenkorbSummenZeile"></div>
				<div class="ArtikelnameWarenkorb ArtikelwarenkorbSummenZeile"></div>
				<div class="ArtikelmengeWarenkorb ArtikelwarenkorbSummenZeile"></div>
				<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb ArtikelwarenkorbSummenZeile">Zwischensumme:</div>
				<div class="ArtikelPreisWarenkorb ArtikelwarenkorbSummenZeile">'.number_format($warenkorb1->get_gesamtpreis_artikel_im_warenkorb(),2, ",", "").' &euro;</div>
			</div>
			<div class="aktuelleArtikelimWarenkorb" >
				<div class="ArtikelbildWarenkorb"></div>
				<div class="ArtikelnameWarenkorb"></div>
				<div class="ArtikelmengeWarenkorb "></div>
				<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb ">Versand:</div>
				<div class="ArtikelPreisWarenkorb">'.number_format($versandkosten,2, ",", "").' &euro;</div>
			</div>
			<div class="aktuelleArtikelimWarenkorb" >
				<div class="ArtikelbildWarenkorb ArtikelwarenkorbSummenZeile"></div>
				<div class="ArtikelnameWarenkorb ArtikelwarenkorbSummenZeile"></div>
				<div class="ArtikelmengeWarenkorb ArtikelwarenkorbSummenZeile"></div>
				<div class="ArtikelPreisWarenkorb UeberschriftWarenkorb ArtikelwarenkorbSummenZeile">Summe:</div>
				<div class="ArtikelPreisWarenkorb ArtikelwarenkorbSummenZeile">'.number_format($warenkorb1->get_gesamtpreis_artikel_im_warenkorb() + $versandkosten,2, ",", "").' &euro;</div>
			</div>
		</div>
		
		<!-- ############################################################## -->
		<div class="ueberschriften" >Zahlungsart:</div>
		<div class="Zahlungsart" >							
			<ul class="zahlungsart_felder" >
					<li>'.htmlspecialchars(ucwords($this->get_zwischengespeicherte_bestellungseinstellungen()->get_zahlungsart()),ENT_QUOTES,'UTF-8').'</li>
			</ul>
		';
		$weitere_Zahlungshinweise = "";
		
		if ( $this->get_zwischengespeicherte_bestellungseinstellungen()->get_zahlungsart() == 'bankeinzug' ){
			
			
			$html_code_email .= '
			<ul class="zahlungsart_felder" >
					<li>Kontoinhaber: '.htmlspecialchars($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_kontoinhaber(),ENT_QUOTES,'UTF-8').'</li>
					<li>IBAN: '.htmlspecialchars($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_iban(),ENT_QUOTES,'UTF-8').'</li>
					<li>BIC: '.htmlspecialchars($this->get_zwischengespeicherte_bestellungseinstellungen()->get_bankeinzug_daten()->get_bic(),ENT_QUOTES,'UTF-8').'</li>
			</ul>	
			';
		}
		else{
			$daten = get_konto_daten_gbi();
			
			$weitere_Zahlungshinweise = '
					<div class="rot" >
						Bitte überweisen Sie den oben genannten Betrag an folgendes Konto:
						<ul>
							<li>Kontoinhaber: '.htmlspecialchars($daten['inhaber'],ENT_QUOTES,'UTF-8').'</li>
							<li>IBAN: '.htmlspecialchars($daten['iban'],ENT_QUOTES,'UTF-8').'</li>
							<li>BIC: '.htmlspecialchars($daten['bic'],ENT_QUOTES,'UTF-8').'</li>
						</ul>
					</div>
			';
		}
		
		$anrede= ( $this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_geschlecht() == 'weiblich') ? "Frau" : "Herr";
		
		$html_code_email.= '
		</div>
		'.$weitere_Zahlungshinweise.'	
		<div class="ueberschriften" >Lieferadresse:</div>
		<ul>
			<li>'.$anrede.'</li>
			<li>'.htmlspecialchars($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_vorname().' '.$this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_name(),ENT_QUOTES,'UTF-8').'</li>
			<li>'.htmlspecialchars($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_strasse().' '.$this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_hausnr(),ENT_QUOTES,'UTF-8').'</li>
			<li>'.htmlspecialchars($this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_plz().' '.$this->get_zwischengespeicherte_bestellungseinstellungen()->get_liefer_ort(),ENT_QUOTES,'UTF-8').'</li>
		</ul>
		<br/>
		<p>Mit freundlichen Grüßen<br/>
		Ihr Webshop Team der Global Bike Inc.</p>		
	</div>
</body>
</html>
';
		
		$email = instanziere_email_objekt();
		return $email->html_email_senden($kunde1->get_email_from_kid($kid), "Bestätigungs-Email des Webshop GBI zur Bestellung vom 08.08.2015", $html_code_email);
		}
		
		
		
	}
?>
