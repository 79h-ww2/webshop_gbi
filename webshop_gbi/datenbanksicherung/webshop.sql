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
INSERT INTO `bestellprodukte` VALUES (1,'2',1),(2,'2',3);
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
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bestellung`
--

LOCK TABLES `bestellung` WRITE;
/*!40000 ALTER TABLE `bestellung` DISABLE KEYS */;
INSERT INTO `bestellung` VALUES (6,'Auftrag erhalten','2015-08-17','vorkasse','2015-08-17 11:42:32','standardversand','nein',1,NULL,'','','','männlich','Otto','Tester','Teststraße','2','12345','Testhausen'),(6,'Auftrag erhalten','2015-08-18','vorkasse','2015-08-18 11:05:07','standardversand','nein',2,NULL,'','','','männlich','Otto','Tester','Teststraße','2','12345','Testhausen');
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
INSERT INTO `kunde` VALUES (6,'Otto','12345','Testhausen','benedikt@kunde.de',NULL,'Teststraße','Lotto','2015-08-20 22:53:57','männlich','161ebd7d45089b3446ee4e0d86dbcf92',NULL,'nein','ja',NULL,'a','2');
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
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `produktbilder`
--

LOCK TABLES `produktbilder` WRITE;
/*!40000 ALTER TABLE `produktbilder` DISABLE KEYS */;
INSERT INTO `produktbilder` VALUES (1,'Liste','./Images/Produktbilder/1/Produktbild_Liste.jpg','1','nein'),(2,'Liste','./Images/Produktbilder/2/Liste.jpg','2','nein'),(3,'Detail','./Images/Produktbilder/1/Detail_Hinterrad_Gross.jpg','1','nein'),(4,'Detail','./Images/Produktbilder/1/Detail_Lenker_Gross.jpg','1','nein'),(5,'Detail','./Images/Produktbilder/1/Detail_Pedale_Gross.jpg','1','nein'),(6,'Detail','./Images/Produktbilder/1/Detail_Sattel_Gross.jpg','1','nein'),(7,'Detail','./Images/Produktbilder/1/Detail_Vorderrad_Gross.jpg','1','nein'),(8,'Produktbild','./Images/Produktbilder/1/Produktbild_Gross.jpg','1','nein'),(9,'Produktbild','./Images/Produktbilder/2/Gross.jpg','2','nein'),(10,'Detail','./Images/Produktbilder/2/Hinterrad_Gross.jpg','2','nein'),(11,'Detail','./Images/Produktbilder/2/Lenker_Gross.jpg','2','nein'),(12,'Detail','./Images/Produktbilder/2/Pedale_Gross.jpg','2','nein'),(13,'Detail','./Images/Produktbilder/2/Sattel_Gross.jpg','2','nein'),(14,'Detail','./Images/Produktbilder/2/Vorderrad_Gross.jpg','2','nein');
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
  `Preis` float(6,2) DEFAULT NULL,
  `Stand` datetime DEFAULT NULL,
  `Farbe` varchar(20) DEFAULT NULL,
  `Bezeichnung` varchar(50) DEFAULT NULL,
  `Verfuegbare Menge` int(11) DEFAULT NULL,
  `Menge Besuche` int(11) DEFAULT NULL,
  `geloescht` varchar(4) DEFAULT NULL,
  `produktkategorie` int(11) DEFAULT NULL,
  `preis_alt` float(5,2) DEFAULT NULL,
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
INSERT INTO `produkte` VALUES ('1',NULL,'Das smarte Rockaway ist ein Freizeitbike, das überall zu Hause ist - von Alltagsstrecken in der Stadt bis auf Ausflugstouren übers Land. Ob auf Feld- und Waldwegen, auf Schotterstraßen oder asphaltierten Radwegen, das Rockaway bringt seinen Fahrer zuverlässig und flott ans Ziel. Auf kleinen Anstiegen findet sich mit der zuverlässigen Shimano Altus 21 Gang Schaltung schnell die passende Übersetzung. In Kombination mit Shimano Umwerfer und Shimano Zahnkranz sorgt dieser Antrieb für nachhaltigen Fahrspaß.\r\n\r\nDie Shimano Schalt- Bremshebelkombination bietet dabei gerade Einsteigern vor allem Komfort und Sicherheit. Die Federgabel von Suntour schluckt kleine Unebenheiten mühelos weg und macht zusammen mit den griffigen Reifen selbst holprige Pisten zum Vergnügen. Dank des komfortablen Sportsattels und der gemäßigt sportlichen Sitzposition, die Rahmengeometrie, Vorbau und Riserlenker vorgeben steigt der Rockawayfahrer auch nach längeren Ausflügen noch entspannt vom Rad. Stabile Laufräder mit Hohlkammerfelgen, ein wartungsfreies Patronen Innenlager und gut greifende V-Brakes runden das Bild ab. Mit dem Rockaway steht für einen wirklich günstigen Preis nicht nur ein guter Rahmen mit einer ausgewogenen Ausstattung zur Verfügung, sondern der Fahrspaß ist bereits schon all inklusive.',14,279.99,NULL,'blau','Serious Rockaway 26\"',2,5,'nein',1,NULL,NULL,NULL,NULL,'32 Gänge + Rückwärtsgang;Einparkassistent;Allradantrieb;Navigationssystem;Tagfahrlicht;Gratis Wackedackel für jedes Fahrrad:D'),('2','ja','Mit dem De Goya lässt sich auf Ausflugstour bequem durch malerische Landschaften cruisen oder komfortabel kurze Wege in der Stadt bewältigen.\r\n\r\nDie Federgabel dämpft selbst gröbere Unebenheiten locker weg und schont Wirbelsäule sowie Gelenke. Auf dem Touren Komfortsattel sitzt man in moderat aufrechter Sitzposition auch über längere Strecken gut; zumal die Sitzposition über den verstellbaren Vorbau je nach Bedarf angepasst werden kann. 7 Gänge erlauben bequemes Fahren, auch wenn es etwas bergan gehen sollte. Bergab sorgen gut greifende V-Brakes in Kombination mit der beliebten Rücktrittbremse für Sicherheit. Der Fahrspaß und die Sicherheit sind starke Argumente für ein De Goya, nicht zuletzt aber besticht es mit einer sehr ästhetischen Optik der Anbauteile, einem Hauch von Nostalgie durch den Sattel und die Griffe sowie zurückhaltendem Understatement des Rahmens in schlichtem schwarzmatt.\r\n\r\nIm Detail ist das de Goya mit hochwertiger Schwalbe Pannenschutzbereifung, rostfreien Speichen, stabilen Hohlkammerfelgen und wartungsfreiem Innenlager auch da erstklassig ausgestattet, wo man es nicht auf dem ersten Blick sieht, sich aber langfristig besonders auszahlt. ',3,400.00,NULL,'schwarz','Ortler deGoya Damen (2015)',0,12,'nein',1,NULL,NULL,'Damenrad','Oertler','500 Gänge + Rückwärtsgang;Anfahrhilfe;Turboantrieb;Stützräder;Nachtfahrlicht;Gratis Wackedackel für jedes Fahrrad :D'),('666','nein','abc',NULL,2.00,'2015-07-28 00:00:00','rot','Beispiel Zubehör',2,21,NULL,2,NULL,NULL,'Herrenrad','Hugo',NULL);
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

-- Dump completed on 2015-08-22 19:03:41
