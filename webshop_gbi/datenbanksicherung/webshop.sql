-- phpMyAdmin SQL Dump
-- version 4.3.11
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Erstellungszeit: 14. Aug 2015 um 12:48
-- Server-Version: 5.6.24
-- PHP-Version: 5.6.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Datenbank: `webshop`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `bauart`
--

CREATE TABLE IF NOT EXISTS `bauart` (
  `BId` int(11) NOT NULL,
  `Bezeichnung` varchar(50) DEFAULT NULL
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `bauart`
--

INSERT INTO `bauart` (`BId`, `Bezeichnung`) VALUES
(1, 'Trekkingrad'),
(2, 'Elektro Rad'),
(3, 'Cityrad'),
(4, 'Crossrad'),
(5, 'Kinderfahrrad'),
(6, 'Jugendfahrrad'),
(7, 'BMX'),
(8, 'Urban Bike'),
(9, 'Cruiser/ Retro'),
(10, 'Singlespeed'),
(11, 'Faltrad/ Klapprad'),
(12, 'Sport & Freizeit'),
(13, 'Rennrad'),
(14, 'Mountainbike');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `bestellprodukte`
--

CREATE TABLE IF NOT EXISTS `bestellprodukte` (
  `BestId` int(11) NOT NULL,
  `PId` int(11) NOT NULL,
  `Menge` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `bestellprodukte`
--

INSERT INTO `bestellprodukte` (`BestId`, `PId`, `Menge`) VALUES
(2, 2, 4),
(3, 2, 2);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `bestellung`
--

CREATE TABLE IF NOT EXISTS `bestellung` (
  `KId` int(11) NOT NULL DEFAULT '0',
  `Status` varchar(25) DEFAULT NULL,
  `Datum` date DEFAULT NULL,
  `Zahlungsart` varchar(25) DEFAULT NULL,
  `stand` datetime DEFAULT NULL,
  `versandart` varchar(50) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  `BestId` int(11) NOT NULL,
  `SAP_BestId` int(11) DEFAULT NULL,
  `bankeinzug_iban` varchar(38) DEFAULT NULL,
  `bankeinzug_bic` varchar(11) DEFAULT NULL,
  `bankeinzug_kontoinhaber` varchar(50) DEFAULT NULL,
  `lieferadresse_geschlecht` enum('männlich','weiblich') DEFAULT NULL,
  `lieferadresse_vorname` varchar(50) DEFAULT NULL,
  `lieferadresse_name` varchar(50) DEFAULT NULL,
  `lieferadresse_strasse` varchar(50) DEFAULT NULL,
  `lieferadresse_hausnummer` varchar(10) DEFAULT NULL,
  `lieferadresse_plz` varchar(5) DEFAULT NULL,
  `lieferadresse_ort` varchar(50) DEFAULT NULL
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `bestellung`
--

INSERT INTO `bestellung` (`KId`, `Status`, `Datum`, `Zahlungsart`, `stand`, `versandart`, `geloescht`, `BestId`, `SAP_BestId`, `bankeinzug_iban`, `bankeinzug_bic`, `bankeinzug_kontoinhaber`, `lieferadresse_geschlecht`, `lieferadresse_vorname`, `lieferadresse_name`, `lieferadresse_strasse`, `lieferadresse_hausnummer`, `lieferadresse_plz`, `lieferadresse_ort`) VALUES
(6, 'Auftrag erhalten', '2015-08-07', 'bankeinzug', '2015-08-07 01:32:37', 'expressversand', 'nein', 2, NULL, 'DE08700901001234567890', '1234567890a', 'Helena von Throja', 'weiblich', 'Helena', 'von Throja', 'Burgstraße', '2', '12345', 'Throja'),
(6, 'Auftrag erhalten', '2015-08-07', 'vorkasse', '2015-08-07 09:11:04', 'standardversand', 'nein', 3, NULL, '', '', '', 'männlich', 'Otto', 'Tester', 'Teststraße', '2', '12345', 'Testhausen');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `kommentare`
--

CREATE TABLE IF NOT EXISTS `kommentare` (
  `KId` int(11) NOT NULL,
  `Text` text,
  `Ueberschrift` varchar(50) DEFAULT NULL,
  `PId` int(11) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  `bewertung` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `kommentare`
--

INSERT INTO `kommentare` (`KId`, `Text`, `Ueberschrift`, `PId`, `geloescht`, `bewertung`) VALUES
(1, 'Tolles Fahrrad und pünklich geliefert, aber nicht das Fahrrad, was ich bestellt habe. Das angekommende Fahrrad ist wesentlich besser als das, was ich  bestellt habe und wäre normalerweise teuer gewesen. Wegen der falschen Lieferung nur 4 Sterne.', 'Tolles Fahrrad, aber nicht meine Bestellung', 1, 'nein', 4),
(2, 'Testkommentar', NULL, 2, 'nein', 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `kunde`
--

CREATE TABLE IF NOT EXISTS `kunde` (
  `KId` int(11) NOT NULL,
  `Vorname` varchar(50) DEFAULT NULL,
  `PLZ` varchar(5) DEFAULT NULL,
  `Ort` varchar(50) DEFAULT NULL,
  `Email` varchar(255) DEFAULT NULL,
  `Login-Name` varchar(50) DEFAULT NULL,
  `Strasse` varchar(50) DEFAULT NULL,
  `Name` varchar(50) DEFAULT NULL,
  `Stand` datetime DEFAULT NULL,
  `Geschlecht` enum('männlich','weiblich') DEFAULT NULL,
  `Passwort` varchar(50) DEFAULT NULL,
  `Geburtsdatum` date DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  `aktiviert` enum('ja','nein') DEFAULT NULL,
  `SAP_KId` int(11) DEFAULT NULL,
  `status` enum('a','l') DEFAULT NULL,
  `Hausnummer` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `kunde`
--

INSERT INTO `kunde` (`KId`, `Vorname`, `PLZ`, `Ort`, `Email`, `Login-Name`, `Strasse`, `Name`, `Stand`, `Geschlecht`, `Passwort`, `Geburtsdatum`, `geloescht`, `aktiviert`, `SAP_KId`, `status`, `Hausnummer`) VALUES
(2, 'Benedikt', '32839', 'Steinheim', 'benedikt@webshop-testmail.de', NULL, 'Papiermühlenweg', 'Brüntrup', '2015-06-04 12:05:00', '', '161ebd7d45089b3446ee4e0d86dbcf92', NULL, 'nein', 'ja', NULL, NULL, NULL),
(3, 'Benedikt', '32839', 'Steinheim', 'root@kunde.de', NULL, 'Papiermühlenweg', 'Brüntrup', '2015-06-10 12:29:02', '', '161ebd7d45089b3446ee4e0d86dbcf92', NULL, 'nein', 'ja', NULL, NULL, '2'),
(5, 'Root', '22222', 'Baum', 'root@webshop-testmail.de', NULL, 'Wurzel', 'Root', '2015-06-26 22:41:41', 'männlich', '161ebd7d45089b3446ee4e0d86dbcf92', NULL, 'nein', 'ja', NULL, NULL, '1'),
(6, 'Otto', '12345', 'Testhausen', 'benedikt@kunde.de', NULL, 'Teststraße', 'Tester', '2015-08-02 14:26:59', 'männlich', '161ebd7d45089b3446ee4e0d86dbcf92', NULL, 'nein', 'ja', NULL, NULL, '2');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `produktbilder`
--

CREATE TABLE IF NOT EXISTS `produktbilder` (
  `BId` int(11) NOT NULL,
  `Art` enum('Liste','Produktbild','Detail') DEFAULT NULL,
  `Pfad` text,
  `PId` int(11) DEFAULT NULL,
  `geloescht` enum('nein','ja') DEFAULT 'nein'
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `produktbilder`
--

INSERT INTO `produktbilder` (`BId`, `Art`, `Pfad`, `PId`, `geloescht`) VALUES
(1, 'Liste', './Images/Produktbilder/1/Produktbild_Liste.jpg', 1, 'nein'),
(2, 'Liste', './Images/Produktbilder/2/Liste.jpg', 2, 'nein'),
(3, 'Detail', './Images/Produktbilder/1/Detail_Hinterrad_Gross.jpg', 1, 'nein'),
(4, 'Detail', './Images/Produktbilder/1/Detail_Lenker_Gross.jpg', 1, 'nein'),
(5, 'Detail', './Images/Produktbilder/1/Detail_Pedale_Gross.jpg', 1, 'nein'),
(6, 'Detail', './Images/Produktbilder/1/Detail_Sattel_Gross.jpg', 1, 'nein'),
(7, 'Detail', './Images/Produktbilder/1/Detail_Vorderrad_Gross.jpg', 1, 'nein'),
(8, 'Produktbild', './Images/Produktbilder/1/Produktbild_Gross.jpg', 1, 'nein'),
(9, 'Produktbild', './Images/Produktbilder/2/Gross.jpg', 2, 'nein'),
(10, 'Detail', './Images/Produktbilder/2/Hinterrad_Gross.jpg', 2, 'nein'),
(11, 'Detail', './Images/Produktbilder/2/Lenker_Gross.jpg', 2, 'nein'),
(12, 'Detail', './Images/Produktbilder/2/Pedale_Gross.jpg', 2, 'nein'),
(13, 'Detail', './Images/Produktbilder/2/Sattel_Gross.jpg', 2, 'nein'),
(14, 'Detail', './Images/Produktbilder/2/Vorderrad_Gross.jpg', 2, 'nein');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `produkte`
--

CREATE TABLE IF NOT EXISTS `produkte` (
  `PId` int(11) NOT NULL,
  `Artikel des Tages` enum('ja','nein') DEFAULT NULL,
  `Beschreibung` text,
  `bauart` int(11) DEFAULT NULL,
  `Preis` float(6,2) DEFAULT NULL,
  `Stand` datetime DEFAULT NULL,
  `Farbe` varchar(20) DEFAULT NULL,
  `Bezeichnung` varchar(50) DEFAULT NULL,
  `Verfuegbare Menge` int(11) DEFAULT NULL,
  `Menge Besuche` int(11) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  `produktkategorie` int(11) DEFAULT NULL,
  `preis_alt` float(5,2) DEFAULT NULL,
  `groesse` tinyint(3) DEFAULT NULL,
  `bauvariante` enum('Herrenrad','Damenrad') DEFAULT NULL,
  `marke` varchar(50) DEFAULT NULL,
  `Eigenschaften` text
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `produkte`
--

INSERT INTO `produkte` (`PId`, `Artikel des Tages`, `Beschreibung`, `bauart`, `Preis`, `Stand`, `Farbe`, `Bezeichnung`, `Verfuegbare Menge`, `Menge Besuche`, `geloescht`, `produktkategorie`, `preis_alt`, `groesse`, `bauvariante`, `marke`, `Eigenschaften`) VALUES
(1, 'ja', 'Das smarte Rockaway ist ein Freizeitbike, das überall zu Hause ist - von Alltagsstrecken in der Stadt bis auf Ausflugstouren übers Land. Ob auf Feld- und Waldwegen, auf Schotterstraßen oder asphaltierten Radwegen, das Rockaway bringt seinen Fahrer zuverlässig und flott ans Ziel. Auf kleinen Anstiegen findet sich mit der zuverlässigen Shimano Altus 21 Gang Schaltung schnell die passende Übersetzung. In Kombination mit Shimano Umwerfer und Shimano Zahnkranz sorgt dieser Antrieb für nachhaltigen Fahrspaß.\r\n\r\nDie Shimano Schalt- Bremshebelkombination bietet dabei gerade Einsteigern vor allem Komfort und Sicherheit. Die Federgabel von Suntour schluckt kleine Unebenheiten mühelos weg und macht zusammen mit den griffigen Reifen selbst holprige Pisten zum Vergnügen. Dank des komfortablen Sportsattels und der gemäßigt sportlichen Sitzposition, die Rahmengeometrie, Vorbau und Riserlenker vorgeben steigt der Rockawayfahrer auch nach längeren Ausflügen noch entspannt vom Rad. Stabile Laufräder mit Hohlkammerfelgen, ein wartungsfreies Patronen Innenlager und gut greifende V-Brakes runden das Bild ab. Mit dem Rockaway steht für einen wirklich günstigen Preis nicht nur ein guter Rahmen mit einer ausgewogenen Ausstattung zur Verfügung, sondern der Fahrspaß ist bereits schon all inklusive.', 14, 279.99, NULL, 'blau', 'Serious Rockaway 26"', 2, 1, 'nein', 1, NULL, NULL, NULL, NULL, '32 Gänge + Rückwärtsgang;Einparkassistent;Allradantrieb;Navigationssystem;Tagfahrlicht;Gratis Wackedackel für jedes Fahrrad:D\r\n'),
(2, NULL, 'Mit dem De Goya lässt sich auf Ausflugstour bequem durch malerische Landschaften cruisen oder komfortabel kurze Wege in der Stadt bewältigen.\r\n\r\nDie Federgabel dämpft selbst gröbere Unebenheiten locker weg und schont Wirbelsäule sowie Gelenke. Auf dem Touren Komfortsattel sitzt man in moderat aufrechter Sitzposition auch über längere Strecken gut; zumal die Sitzposition über den verstellbaren Vorbau je nach Bedarf angepasst werden kann. 7 Gänge erlauben bequemes Fahren, auch wenn es etwas bergan gehen sollte. Bergab sorgen gut greifende V-Brakes in Kombination mit der beliebten Rücktrittbremse für Sicherheit. Der Fahrspaß und die Sicherheit sind starke Argumente für ein De Goya, nicht zuletzt aber besticht es mit einer sehr ästhetischen Optik der Anbauteile, einem Hauch von Nostalgie durch den Sattel und die Griffe sowie zurückhaltendem Understatement des Rahmens in schlichtem schwarzmatt.\r\n\r\nIm Detail ist das de Goya mit hochwertiger Schwalbe Pannenschutzbereifung, rostfreien Speichen, stabilen Hohlkammerfelgen und wartungsfreiem Innenlager auch da erstklassig ausgestattet, wo man es nicht auf dem ersten Blick sieht, sich aber langfristig besonders auszahlt. ', 3, 400.00, NULL, 'schwarz', 'Ortler deGoya Damen (2015)', 4, 1, 'nein', 1, NULL, NULL, 'Damenrad', 'Oertler', '500 Gänge + Rückwärtsgang;Anfahrhilfe;Turboantrieb;Stützräder;Nachtfahrlicht;Gratis Wackedackel für jedes Fahrrad :D\r\n'),
(666, 'nein', 'abc', NULL, 2.00, '2015-07-28 00:00:00', 'rot', 'Beispiel Zubehör', 2, 21, NULL, 2, NULL, NULL, 'Herrenrad', 'Hugo', NULL);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `produktkategorie`
--

CREATE TABLE IF NOT EXISTS `produktkategorie` (
  `PTId` int(11) NOT NULL,
  `Bezeichnung` varchar(50) DEFAULT NULL
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `produktkategorie`
--

INSERT INTO `produktkategorie` (`PTId`, `Bezeichnung`) VALUES
(1, 'Fahrrad'),
(2, 'Zubehör'),
(3, 'Fahrradteil'),
(4, 'Fahrradbekleidung');

--
-- Indizes der exportierten Tabellen
--

--
-- Indizes für die Tabelle `bauart`
--
ALTER TABLE `bauart`
  ADD PRIMARY KEY (`BId`);

--
-- Indizes für die Tabelle `bestellprodukte`
--
ALTER TABLE `bestellprodukte`
  ADD PRIMARY KEY (`BestId`,`PId`), ADD KEY `PId` (`PId`);

--
-- Indizes für die Tabelle `bestellung`
--
ALTER TABLE `bestellung`
  ADD PRIMARY KEY (`BestId`), ADD KEY `bestellung_ibfk_2` (`KId`);

--
-- Indizes für die Tabelle `kommentare`
--
ALTER TABLE `kommentare`
  ADD PRIMARY KEY (`KId`), ADD KEY `PId` (`PId`);

--
-- Indizes für die Tabelle `kunde`
--
ALTER TABLE `kunde`
  ADD PRIMARY KEY (`KId`);

--
-- Indizes für die Tabelle `produktbilder`
--
ALTER TABLE `produktbilder`
  ADD PRIMARY KEY (`BId`), ADD KEY `PId` (`PId`);

--
-- Indizes für die Tabelle `produkte`
--
ALTER TABLE `produkte`
  ADD PRIMARY KEY (`PId`), ADD KEY `bauart` (`bauart`), ADD KEY `produktkategorie` (`produktkategorie`);

--
-- Indizes für die Tabelle `produktkategorie`
--
ALTER TABLE `produktkategorie`
  ADD PRIMARY KEY (`PTId`);

--
-- AUTO_INCREMENT für exportierte Tabellen
--

--
-- AUTO_INCREMENT für Tabelle `bauart`
--
ALTER TABLE `bauart`
  MODIFY `BId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=15;
--
-- AUTO_INCREMENT für Tabelle `bestellung`
--
ALTER TABLE `bestellung`
  MODIFY `BestId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT für Tabelle `kommentare`
--
ALTER TABLE `kommentare`
  MODIFY `KId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT für Tabelle `produktbilder`
--
ALTER TABLE `produktbilder`
  MODIFY `BId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=15;
--
-- AUTO_INCREMENT für Tabelle `produktkategorie`
--
ALTER TABLE `produktkategorie`
  MODIFY `PTId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
--
-- Constraints der exportierten Tabellen
--

--
-- Constraints der Tabelle `bestellprodukte`
--
ALTER TABLE `bestellprodukte`
ADD CONSTRAINT `bestellprodukte_ibfk_1` FOREIGN KEY (`BestId`) REFERENCES `bestellung` (`BestId`),
ADD CONSTRAINT `bestellprodukte_ibfk_2` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`);

--
-- Constraints der Tabelle `bestellung`
--
ALTER TABLE `bestellung`
ADD CONSTRAINT `bestellung_ibfk_2` FOREIGN KEY (`KId`) REFERENCES `kunde` (`KId`);

--
-- Constraints der Tabelle `kommentare`
--
ALTER TABLE `kommentare`
ADD CONSTRAINT `kommentare_ibfk_1` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`);

--
-- Constraints der Tabelle `produktbilder`
--
ALTER TABLE `produktbilder`
ADD CONSTRAINT `produktbilder_ibfk_1` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`);

--
-- Constraints der Tabelle `produkte`
--
ALTER TABLE `produkte`
ADD CONSTRAINT `produkte_ibfk_1` FOREIGN KEY (`bauart`) REFERENCES `bauart` (`BId`),
ADD CONSTRAINT `produkte_ibfk_2` FOREIGN KEY (`produktkategorie`) REFERENCES `produktkategorie` (`PTId`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
