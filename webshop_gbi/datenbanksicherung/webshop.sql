-- MySQL dump 10.13  Distrib 5.5.43, for debian-linux-gnu (armv7l)
--
-- Host: localhost    Database: webshop
-- ------------------------------------------------------
-- Server version	5.5.43-0+deb7u1

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
-- Table structure for table `bestellung`
--

DROP TABLE IF EXISTS `bestellung`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bestellung` (
  `KId` int(11) NOT NULL DEFAULT '0',
  `PId` int(11) NOT NULL DEFAULT '0',
  `Menge` int(11) DEFAULT NULL,
  `Status` varchar(25) DEFAULT NULL,
  `Datum` date DEFAULT NULL,
  `Zahlungsart` varchar(25) DEFAULT NULL,
  `stand` datetime DEFAULT NULL,
  `versandart` varchar(50) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  PRIMARY KEY (`PId`,`KId`),
  KEY `KId` (`KId`),
  CONSTRAINT `bestellung_ibfk_1` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`),
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
  `KId` int(11) NOT NULL,
  `Text` text,
  `Ueberschrift` varchar(50) DEFAULT NULL,
  `PId` int(11) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  PRIMARY KEY (`KId`),
  KEY `PId` (`PId`),
  CONSTRAINT `kommentare_ibfk_1` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kommentare`
--

LOCK TABLES `kommentare` WRITE;
/*!40000 ALTER TABLE `kommentare` DISABLE KEYS */;
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
  `hausNr` varchar(5) DEFAULT NULL,
  PRIMARY KEY (`KId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kunde`
--

LOCK TABLES `kunde` WRITE;
/*!40000 ALTER TABLE `kunde` DISABLE KEYS */;
/*!40000 ALTER TABLE `kunde` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `produktbilder`
--

DROP TABLE IF EXISTS `produktbilder`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `produktbilder` (
  `BId` int(11) NOT NULL,
  `Art` varchar(25) DEFAULT NULL,
  `Pfad` text,
  `PId` int(11) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  PRIMARY KEY (`BId`),
  KEY `PId` (`PId`),
  CONSTRAINT `produktbilder_ibfk_1` FOREIGN KEY (`PId`) REFERENCES `produkte` (`PId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `produktbilder`
--

LOCK TABLES `produktbilder` WRITE;
/*!40000 ALTER TABLE `produktbilder` DISABLE KEYS */;
/*!40000 ALTER TABLE `produktbilder` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `produkte`
--

DROP TABLE IF EXISTS `produkte`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `produkte` (
  `PId` int(11) NOT NULL,
  `Artikel des Tages` enum('ja','nein') DEFAULT NULL,
  `Beschreibung` text,
  `Art` varchar(50) DEFAULT NULL,
  `Preis` float(6,2) DEFAULT NULL,
  `Stand` datetime DEFAULT NULL,
  `Farbe` varchar(20) DEFAULT NULL,
  `Bezeichnung` varchar(50) DEFAULT NULL,
  `Verfuegbare Menge` int(11) DEFAULT NULL,
  `Bewertung` int(1) DEFAULT NULL,
  `Menge Besuche` int(11) DEFAULT NULL,
  `geloescht` enum('ja','nein') DEFAULT NULL,
  PRIMARY KEY (`PId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `produkte`
--

LOCK TABLES `produkte` WRITE;
/*!40000 ALTER TABLE `produkte` DISABLE KEYS */;
/*!40000 ALTER TABLE `produkte` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-05-10 22:06:37
