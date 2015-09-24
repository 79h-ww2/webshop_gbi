-- MySQL dump 10.13  Distrib 5.6.25, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: webshop
-- ------------------------------------------------------
-- Server version	5.6.25-0ubuntu0.15.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bauart`
--

DROP TABLE IF EXISTS `bauart`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bauart` (
  `BId` int(11) NOT NULL AUTO_INCREMENT,
  `Bezeichnung` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`BId`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bauart`
--

LOCK TABLES `bauart` WRITE;
/*!40000 ALTER TABLE `bauart` DISABLE KEYS */;
INSERT INTO `bauart` VALUES (1,'Trekkingrad'),(2,'Elektro Rad'),(3,'Cityrad'),(4,'Crossrad'),(5,'Kinderfahrrad'),(6,'Jugendfahrrad'),(7,'BMX'),(8,'Urban Bike'),(9,'Cruiser/ Retro'),(10,'Singlespeed'),(11,'Faltrad/ Klapprad'),(12,'Sport & Freizeit'),(13,'Rennrad'),(14,'Mountainbike');
/*!40000 ALTER TABLE `bauart` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bestellprodukte`
--

DROP TABLE IF EXISTS `bestellprodukte`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bestellprodukte` (
  `BestId` int(11) NOT NULL,
  `PId` varchar(11) NOT NULL,
  `Menge` int(11) NOT NULL,
  PRIMARY KEY (`BestId`,`PId`),
  KEY `PId` (`PId`),
  CONSTRAINT `bestellprodukte_ibfk_1` FOREIGN KEY (`BestId`) REFERENCES `bestellung` (`BestId`),
  CONSTRAINT `bestellprodukte_ibfk_2` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bestellprodukte`
--

LOCK TABLES `bestellprodukte` WRITE;
/*!40000 ALTER TABLE `bestellprodukte` DISABLE KEYS */;
/*!40000 ALTER TABLE `bestellprodukte` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bestellung`
--

DROP TABLE IF EXISTS `bestellung`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bestellung` (
  `KId` int(11) NOT NULL DEFAULT '0',
  `Status` varchar(25) DEFAULT NULL,
  `Datum` date DEFAULT NULL,
  `Zahlungsart` varchar(25) DEFAULT NULL,
  `stand` datetime DEFAULT NULL,
  `versandart` varchar(50) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  `BestId` int(11) NOT NULL AUTO_INCREMENT,
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
  `lieferadresse_ort` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`BestId`),
  KEY `bestellung_ibfk_2` (`KId`),
  CONSTRAINT `bestellung_ibfk_2` FOREIGN KEY (`KId`) REFERENCES `kunde` (`KId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bestellung`
--

LOCK TABLES `bestellung` WRITE;
/*!40000 ALTER TABLE `bestellung` DISABLE KEYS */;
/*!40000 ALTER TABLE `bestellung` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kommentare`
--

DROP TABLE IF EXISTS `kommentare`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `kommentare` (
  `KId` int(11) NOT NULL AUTO_INCREMENT,
  `Text` text,
  `Ueberschrift` varchar(50) DEFAULT NULL,
  `PId` varchar(11) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  `bewertung` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`KId`),
  KEY `PId` (`PId`),
  CONSTRAINT `kommentare_ibfk_1` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kommentare`
--

LOCK TABLES `kommentare` WRITE;
/*!40000 ALTER TABLE `kommentare` DISABLE KEYS */;
INSERT INTO `kommentare` VALUES (1,'Tolles Fahrrad und pünklich geliefert, aber nicht das Fahrrad, was ich bestellt habe. Das angekommende Fahrrad ist wesentlich besser als das, was ich  bestellt habe und wäre normalerweise teuer gewesen. Wegen der falschen Lieferung nur 4 Sterne.','Tolles Fahrrad, aber nicht meine Bestellung','1','nein',4),(2,'Testkommentar',NULL,'2','nein',1);
/*!40000 ALTER TABLE `kommentare` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kunde`
--

DROP TABLE IF EXISTS `kunde`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `kunde` (
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
  `Hausnummer` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`KId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kunde`
--

LOCK TABLES `kunde` WRITE;
/*!40000 ALTER TABLE `kunde` DISABLE KEYS */;
INSERT INTO `kunde` VALUES (6,'Otto','12345','Testhausen','benedikt@kunde.de',NULL,'Teststraße','Lotto','2015-08-20 22:53:57','männlich','161ebd7d45089b3446ee4e0d86dbcf92',NULL,'nein','ja',25120,NULL,'2');
/*!40000 ALTER TABLE `kunde` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `produktbilder`
--

DROP TABLE IF EXISTS `produktbilder`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `produktbilder` (
  `BId` int(11) NOT NULL AUTO_INCREMENT,
  `Art` enum('Liste','Produktbild','Detail') DEFAULT NULL,
  `Pfad` text,
  `PId` varchar(11) DEFAULT NULL,
  `geloescht` enum('nein','ja') DEFAULT 'nein',
  PRIMARY KEY (`BId`),
  KEY `PId` (`PId`),
  CONSTRAINT `produktbilder_ibfk_1` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`)
) ENGINE=InnoDB AUTO_INCREMENT=85 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `produktbilder`
--

LOCK TABLES `produktbilder` WRITE;
/*!40000 ALTER TABLE `produktbilder` DISABLE KEYS */;
INSERT INTO `produktbilder` VALUES (1,'Liste','./Images/Produktbilder/1/Produktbild_Liste.jpg','1','nein'),(2,'Liste','./Images/Produktbilder/2/Liste.jpg','2','nein'),(3,'Detail','./Images/Produktbilder/1/Detail_Hinterrad_Gross.jpg','1','nein'),(4,'Detail','./Images/Produktbilder/1/Detail_Lenker_Gross.jpg','1','nein'),(5,'Detail','./Images/Produktbilder/1/Detail_Pedale_Gross.jpg','1','nein'),(6,'Detail','./Images/Produktbilder/1/Detail_Sattel_Gross.jpg','1','nein'),(7,'Detail','./Images/Produktbilder/1/Detail_Vorderrad_Gross.jpg','1','nein'),(8,'Produktbild','./Images/Produktbilder/1/Produktbild_Gross.jpg','1','nein'),(9,'Produktbild','./Images/Produktbilder/2/Gross.jpg','2','nein'),(10,'Detail','./Images/Produktbilder/2/Hinterrad_Gross.jpg','2','nein'),(11,'Detail','./Images/Produktbilder/2/Lenker_Gross.jpg','2','nein'),(12,'Detail','./Images/Produktbilder/2/Pedale_Gross.jpg','2','nein'),(13,'Detail','./Images/Produktbilder/2/Sattel_Gross.jpg','2','nein'),(14,'Detail','./Images/Produktbilder/2/Vorderrad_Gross.jpg','2','nein'),(15,'Produktbild','Images/Produktbilder/M21/produktbild.jpg','M21','nein'),(16,'Liste','Images/Produktbilder/M21/liste.jpg','M21','nein'),(17,'Detail','Images/Produktbilder/M21/detail1.jpg','M21','nein'),(18,'Detail','Images/Produktbilder/M21/detail2.jpg','M21','nein'),(19,'Produktbild','Images/Produktbilder/M03/produkt.jpg','M03','nein'),(20,'Liste','Images/Produktbilder/M03/liste.jpg','M03','nein'),(21,'Detail','Images/Produktbilder/M00/detail1.jpg','M00','nein'),(23,'Detail','Images/Produktbilder/M00/detail3.jpg','M00','nein'),(24,'Detail','Images/Produktbilder/M00/detail4.jpg','M00','nein'),(26,'Detail','Images/Produktbilder/M00/detail5.jpg','M00','nein'),(27,'Detail','Images/Produktbilder/M00/detail6.jpg','M00','nein'),(28,'Detail','Images/Produktbilder/M00/detail7.jpg','M00','nein'),(29,'Detail','Images/Produktbilder/M00/detail8.jpg','M00','nein'),(30,'Detail','Images/Produktbilder/M00/detail9.jpg','M00','nein'),(31,'Detail','Images/Produktbilder/M00/detail10.jpg','M00','nein'),(32,'Detail','Images/Produktbilder/M00/detail11.jpg','M00','nein'),(33,'Produktbild','Images/Produktbilder/M00/produktbild.jpg','M00','nein'),(34,'Liste','Images/Produktbilder/M00/liste.jpg','M00','nein'),(35,'Produktbild','Images/Produktbilder/M01/Produktbild.jpg','M01','nein'),(36,'Produktbild','Images/Produktbilder/M05/produktbild.jpg','M05','nein'),(37,'Liste','Images/Produktbilder/M05/liste.jpg','M05','nein'),(38,'Liste','Images/Produktbilder/M01/Liste.jpg','M01','nein'),(39,'Detail','Images/Produktbilder/M05/seitenansicht.jpg','M05','nein'),(40,'Liste','./Images/Produktbilder/1/Produktbild_Liste.jpg','M02','nein'),(41,'Detail','./Images/Produktbilder/1/Detail_Hinterrad_Gross.jpg','M02','nein'),(42,'Detail','./Images/Produktbilder/1/Detail_Lenker_Gross.jpg','M02','nein'),(43,'Detail','./Images/Produktbilder/1/Detail_Pedale_Gross.jpg','M02','nein'),(44,'Detail','./Images/Produktbilder/1/Detail_Sattel_Gross.jpg','M02','nein'),(45,'Detail','./Images/Produktbilder/1/Detail_Vorderrad_Gross.jpg','M02','nein'),(46,'Produktbild','./Images/Produktbilder/1/Produktbild_Gross.jpg','M02','nein'),(47,'Detail','Images/Produktbilder/M04/detail1.jpg','M04','nein'),(48,'Detail','Images/Produktbilder/M04/detail2.jpg','M04','nein'),(49,'Detail','Images/Produktbilder/M04/detail3.jpg','M04','nein'),(50,'Detail','Images/Produktbilder/M04/detail4.jpg','M04','nein'),(51,'Produktbild','Images/Produktbilder/M04/Produktbilder.jpg','M04','nein'),(52,NULL,'Images/Produktbilder/M04/liste.jpg','M04','nein'),(53,'Detail','Images/Produktbilder/M06/detail1.jpg','M06','nein'),(54,'Detail','Images/Produktbilder/M06/detail2.jpg','M06','nein'),(55,'Detail','Images/Produktbilder/M06/detail3.jpg','M06','nein'),(56,'Detail','Images/Produktbilder/M06/detail4.jpg','M06','nein'),(57,'Detail','Images/Produktbilder/M06/detail5.jpg','M06','nein'),(60,'Produktbild','Images/Produktbilder/M06/produktbild.jpg','M06','nein'),(61,'Liste','Images/Produktbilder/M06/liste.jpg','M06','nein'),(62,'Produktbild','Images/Produktbilder/M07/produktbild.jpg','M07','nein'),(72,'Detail','Images/Produktbilder/M08/detail1.jpg','M08','nein'),(73,'Detail','Images/Produktbilder/M08/detail2.jpg','M08','nein'),(74,'Detail','Images/Produktbilder/M08/detail3.jpg','M08','nein'),(75,'Detail','Images/Produktbilder/M08/detail4.jpg','M08','nein'),(76,'Detail','Images/Produktbilder/M08/detail5.jpg','M08','nein'),(79,'Liste','Images/Produktbilder/M08/liste.jpg','M08','nein'),(80,'Produktbild','Images/Produktbilder/M08/liste.jpg','M08','nein'),(81,'Produktbild','Images/Produktbilder/M09/produktbild.png','M09','nein'),(82,'Liste','Images/Produktbilder/M09/liste.png','M09','nein'),(83,'Produktbild','Images/Produktbilder/M20/produktbild.jpg','M20','nein'),(84,'Liste','Images/Produktbilder/M20/liste.jpg','M20','nein');
/*!40000 ALTER TABLE `produktbilder` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `produkte`
--

DROP TABLE IF EXISTS `produkte`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `produkte` (
  `PId` varchar(11) NOT NULL,
  `Artikel des Tages` varchar(4) DEFAULT NULL,
  `Beschreibung` text,
  `bauart` int(11) DEFAULT NULL,
  `preis` float(10,2) DEFAULT NULL,
  `Stand` datetime DEFAULT NULL,
  `Farbe` varchar(20) DEFAULT NULL,
  `Bezeichnung` varchar(50) DEFAULT NULL,
  `Verfuegbare Menge` int(11) DEFAULT NULL,
  `Menge Besuche` int(11) DEFAULT NULL,
  `geloescht` varchar(4) DEFAULT NULL,
  `produktkategorie` int(11) DEFAULT NULL,
  `preis_alt` float(10,2) DEFAULT NULL,
  `groesse` tinyint(3) DEFAULT NULL,
  `bauvariante` varchar(9) DEFAULT NULL,
  `marke` varchar(50) DEFAULT NULL,
  `Eigenschaften` text,
  PRIMARY KEY (`PId`),
  KEY `bauart` (`bauart`),
  KEY `produktkategorie` (`produktkategorie`),
  CONSTRAINT `produkte_ibfk_1` FOREIGN KEY (`bauart`) REFERENCES `bauart` (`BId`),
  CONSTRAINT `produkte_ibfk_2` FOREIGN KEY (`produktkategorie`) REFERENCES `produktkategorie` (`PTId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `produkte`
--

LOCK TABLES `produkte` WRITE;
/*!40000 ALTER TABLE `produkte` DISABLE KEYS */;
INSERT INTO `produkte` VALUES ('1',NULL,'Das smarte Rockaway ist ein Freizeitbike, das überall zu Hause ist - von Alltagsstrecken in der Stadt bis auf Ausflugstouren übers Land. Ob auf Feld- und Waldwegen, auf Schotterstraßen oder asphaltierten Radwegen, das Rockaway bringt seinen Fahrer zuverlässig und flott ans Ziel. Auf kleinen Anstiegen findet sich mit der zuverlässigen Shimano Altus 21 Gang Schaltung schnell die passende Übersetzung. In Kombination mit Shimano Umwerfer und Shimano Zahnkranz sorgt dieser Antrieb für nachhaltigen Fahrspaß.\r\n\r\nDie Shimano Schalt- Bremshebelkombination bietet dabei gerade Einsteigern vor allem Komfort und Sicherheit. Die Federgabel von Suntour schluckt kleine Unebenheiten mühelos weg und macht zusammen mit den griffigen Reifen selbst holprige Pisten zum Vergnügen. Dank des komfortablen Sportsattels und der gemäßigt sportlichen Sitzposition, die Rahmengeometrie, Vorbau und Riserlenker vorgeben steigt der Rockawayfahrer auch nach längeren Ausflügen noch entspannt vom Rad. Stabile Laufräder mit Hohlkammerfelgen, ein wartungsfreies Patronen Innenlager und gut greifende V-Brakes runden das Bild ab. Mit dem Rockaway steht für einen wirklich günstigen Preis nicht nur ein guter Rahmen mit einer ausgewogenen Ausstattung zur Verfügung, sondern der Fahrspaß ist bereits schon all inklusive.',14,279.99,NULL,'blau','Serious Rockaway 26\"',19,14,'nein',1,NULL,NULL,NULL,NULL,'32 Gänge + Rückwärtsgang;Einparkassistent;Allradantrieb;Navigationssystem;Tagfahrlicht;Gratis Wackedackel für jedes Fahrrad:D'),('2','ja','Mit dem De Goya lässt sich auf Ausflugstour bequem durch malerische Landschaften cruisen oder komfortabel kurze Wege in der Stadt bewältigen.\r\n\r\nDie Federgabel dämpft selbst gröbere Unebenheiten locker weg und schont Wirbelsäule sowie Gelenke. Auf dem Touren Komfortsattel sitzt man in moderat aufrechter Sitzposition auch über längere Strecken gut; zumal die Sitzposition über den verstellbaren Vorbau je nach Bedarf angepasst werden kann. 7 Gänge erlauben bequemes Fahren, auch wenn es etwas bergan gehen sollte. Bergab sorgen gut greifende V-Brakes in Kombination mit der beliebten Rücktrittbremse für Sicherheit. Der Fahrspaß und die Sicherheit sind starke Argumente für ein De Goya, nicht zuletzt aber besticht es mit einer sehr ästhetischen Optik der Anbauteile, einem Hauch von Nostalgie durch den Sattel und die Griffe sowie zurückhaltendem Understatement des Rahmens in schlichtem schwarzmatt.\r\n\r\nIm Detail ist das de Goya mit hochwertiger Schwalbe Pannenschutzbereifung, rostfreien Speichen, stabilen Hohlkammerfelgen und wartungsfreiem Innenlager auch da erstklassig ausgestattet, wo man es nicht auf dem ersten Blick sieht, sich aber langfristig besonders auszahlt. ',3,400.00,NULL,'schwarz','Ortler deGoya Damen (2015)',18,24,'nein',1,NULL,NULL,'Damenrad','Oertler','500 Gänge + Rückwärtsgang;Anfahrhilfe;Turboantrieb;Stützräder;Nachtfahrlicht;Gratis Wackedackel für jedes Fahrrad :D'),('666','nein','abc',NULL,2.00,'2015-07-28 00:00:00','rot','Beispiel Zubehör',2,21,NULL,2,NULL,NULL,'Herrenrad','Hugo',NULL),('M00','nein','Das coole Kinderrad überzeugt nicht nur durch seine abenteuerlicheOptik, sondern vor allem durch Qualität und nützliche Details. Nebeneinem Rahmen mit tiefem Einsieg verfügt das Vermont-Kinderrad überstabile Aluminium Felgen, Rücktrittbremse und Vorderradbremsen mitkindgerechten einstellbaren Bremshebeln sowie einem Vorbaupolster.Weiteres Highlight ist die coole Piratenbox am Lenker, damit dieEroberungen auch transportiert werden können.',5,0.00,NULL,'grün\r','00 Bike',20,4,'nein',1,0.00,55,NULL,NULL,'null'),('M01','ja\r','Dies ist ein schönes Material.',4,0.00,NULL,'rot\r','E-Bike',20,4,'nein',1,0.00,45,'Damenrad','Kreidler\r','Vollmantelreifen'),('M02','ja\r','Das smarte Rockaway ist ein Freizeitbike, das überall zu Hause ist - vonAlltagsstrecken in der Stadt bis auf Ausflugstouren übers Land. Ob aufFeld- und Waldwegen, auf Schotterstraßen oder asphaltierten Radwegen,das Rockaway bringt seinen Fahrer zuverlässig und flott ans Ziel. Aufkleinen Anstiegen findet sich mit der zuverlässigen Shimano Altus 21Gang Schaltung schnell die passende Übersetzung. In Kombination mitShimano Umwerfer und Shimano Zahnkranz sorgt dieser Antrieb fürnachhaltigen Fahrspaß.',2,37.38,NULL,'gruen\r','Serious Rockaway 26\"',20,6,'nein',1,37.38,40,NULL,NULL,'null'),('M03','null','Im Schatten der imposanten Kreuzkofel-Gruppe gelegen, zählt dermalerische Valparola Pass (2192 m) zu den Rennradklassikern schlechthinin den italienischen Dolomiten. Dank seiner moderaten Steigungsprozentegewährt dieser „gutmütige\" Alpenpass auch weniger erfahrenenStraßenfahrern ein unvergessliches Erlebnis. Das setzt exakt an dieserStelle an: Es soll Einsteigern die Faszination Straßenradsportungefiltert vermitteln - ohne den Geldbeutel allzu sehr zu belasten. DasSerious Valparola ist der Einstig in die Rennradwelt. Der leichte unddennoch solide 7005er Aluminium Rahmen mit 3-Schicht-Pulverlackierungbesticht durch geringes Gewicht, gute Steifigkeitswerte und ausgewogeneFahreigenschaften. Damit auch bei längeren Anstiegen optimaleÜbersetzungen vorhanden sind, wurde bewusst eine Shimano 3-fachKurbelradgarnitur verbaut, die in Kombination mit Shimanos 24 Gang SoraSchaltung keine Wünsche offen lässt.  Beim Valparola wurden in SachenAusstattung keine Kompromisse gemacht und so sind auch Naben, Bremsenund Innenlager von Shimano.',1,0.00,NULL,'null','Serious Valparola',20,2,'nein',1,0.00,0,NULL,NULL,'null'),('M04','null','Das Ortler Lindau hält, was es verspricht: einfach und solideausgestattet, ohne wartungsanfällige Bauteile wie Federgabel, bietet eseinen vernünftigen Einstieg in die Trekkingradklasse. Das Ortler Lindaueignet sich hervorragend für gelegentliche Ausflüge oder die täglicheKurzstrecke zur Arbeit oder Uni. Ausgestattet mit STvZO Lichtanlage undgroßem Kettenkasten leistet es zuverlässige Dienste im Straßenverkehrund auf unbefestigten Wegen. Die Shimano 21-Gang Kettenschaltung bietethierbei gute Übersetzungen für längere Steigungen und flotten Vortriebin der Ebene.',1,0.00,NULL,'null','Ortler Lindau Herren',20,4,'nein',1,0.00,0,NULL,NULL,'null'),('M05','nein','Das Speedelectric ist ein sehr gutes Fahrrad zum cruisen in der Stadt.Der effiziente 250 Watt Motor bietet optimale Kraftentfaltung undVortrieb am Berg „ohne Wenn und Aber\". Aufgeladen zu 80 % in knapp 2,5Stunden, lassen sich dank moderner E-Power auch lange Distanzen undanspruchsvolle Touren mit vielen Höhenmetern bestreiten.Das Ortler Bozenverfügt über die neueste Genration der Bosch E-Bike Antriebe und ist mitdem leistungsstärksten 400 Wattstunden Akku von Bosch ausgestattet. DieIntensität der Tretkraftunterstützung kann in vier Stufen frei gewähltund damit die Reichweite des Pedelecs kilometergenau vom Fahrerbeeinflusst werden. Langlebig ausgestattet mit solider Shimano DeoreAntriebstechnologie, einer sensibel ansprechenden Suntour Federgabel,lässt das Ortler Bozen keine Wünsche offen. Axa LED Beleuchtung undleichtlaufende Schwalbe Energizer Pro Bereifung runden das perfekte E-Bike ab: Ortler Bozen Bosch Pedelec - intelligente Pedelec TechnologieMade in Poland.',6,5000.00,NULL,'orange\r','Speedelectric 03',20,2,'nein',1,0.00,20,'Damenrad','Radon\r','null'),('M06','null','Das Trekkingrad es verspricht: einfach und solide ausgestattet, ohnewartungsanfällige Bauteile wie Federgabel, bietet es einen vernünftigenEinstieg in die Trekkingradklasse. Das Ortler Lindau eignet sichhervorragend für gelegentliche Ausflüge oder die tägliche Kurzstreckezur Arbeit oder Uni. Ausgestattet mit STvZO Lichtanlage und großemKettenkasten leistet es zuverlässige Dienste im Straßenverkehr und aufunbefestigten Wegen. Die Shimano 21-Gang Kettenschaltung bietet hierbeigute Übersetzungen für längere Steigungen und flotten Vortrieb in derEbene.',1,0.00,NULL,'null','Trekkingrad',20,3,'nein',1,0.00,0,NULL,NULL,'null'),('M07','null','Am bayerischen Firmenstandort Waldorf ist der kompletteEntwicklungsprozess vereint. Seit über zwanzig Jahren ist Cube bestrebtfür jeden das perfekte Rad bieten zu können.Cube ist die richtigeEntscheidung wenn Sicherheit,Zuverlässigkeit und der Komfort an ersterStelle stehen. Cube ist Markenführer in Deutschland im mittleren undhochpreisigen Mountainbike - und Rennrad - Segment. In 60 Ländern istCube im Fachhandel erhältlich.',1,0.00,NULL,'null','Elektrorad',20,1,'nein',1,0.00,0,NULL,NULL,'null'),('M08','null',' Alu Cityofahrrad, 28 Zoll, 7-Gang-SHIMANO-Schaltung, »Navigator Comfort«, Prophete.Bei dem Prophete City-Rad »Navigator Comfort« haben wir besonderen Wertauf Stabilität, gutes Handling und einen bequemen Einstieg gelegt.Radeln mit stetigem Rückenwind. Kein Problem mit diesem Pedelec! Dankdes 36 Volt Motors ist es mit wenig Kraftaufwand machbar, auch längereStrecken zu fahren. Ob beim Ausflug ins Grüne oder auf dem Weg zurArbeit - das Fahrgefühl mit dem Pedelec wird jeden faszinieren und immerwieder aufs Neue begeistern.',1,0.00,NULL,'null','Cityrad',20,5,'nein',1,0.00,0,NULL,NULL,'null'),('M09','null','Entdecken Sie die Natur: Mit dem Focus Lost Lagoon CS 4.0 lassen Sie denAlltag schnell hinter sich. Der Aluminiumrahmen gefällt mit einerausgewogenen Geometrie auf langen wie auch kurzen Strecken. Dieeinstellbare Suntour Federgabel vermittelt Fahrkomfort in jedem Terrain.Die Shimano Kettenschaltung ist präzise, zuverlässig und mit 24 Gängenbestens auf das Lost Lagoon abgestimmt. Tektro V-Brakes verzögernkraftvoll auch bei schnellen Abfahrten. Leichte Concept Aluminium Partsvervollständigen das Focus und runden das wertige Gesamtbildwirkungsvoll ab. Das Lost Lagoon ist ein optisch reizvolles sowietechnisch ansprechendes Crossbike zu einem sehr attraktiven Preis. InSachen Preis und Leistung ist dieses flinke Rad nahezu unschlagbar.',1,0.00,NULL,'null','Crossrad',20,1,'nein',1,0.00,0,NULL,NULL,'null'),('M20','null','',1,3400.00,NULL,'null','Elektronisches Fahrrad',20,2,'nein',1,0.00,0,NULL,NULL,'null'),('M21','null','',1,1985.00,NULL,'null','CUBE REACTION HYBRID',20,6,'nein',1,NULL,0,NULL,NULL,'null');
/*!40000 ALTER TABLE `produkte` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `produktkategorie`
--

DROP TABLE IF EXISTS `produktkategorie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `produktkategorie` (
  `PTId` int(11) NOT NULL AUTO_INCREMENT,
  `Bezeichnung` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`PTId`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `produktkategorie`
--

LOCK TABLES `produktkategorie` WRITE;
/*!40000 ALTER TABLE `produktkategorie` DISABLE KEYS */;
INSERT INTO `produktkategorie` VALUES (1,'Fahrrad'),(2,'Zubehör'),(3,'Fahrradteil'),(4,'Fahrradbekleidung');
/*!40000 ALTER TABLE `produktkategorie` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-09-24 11:52:26
