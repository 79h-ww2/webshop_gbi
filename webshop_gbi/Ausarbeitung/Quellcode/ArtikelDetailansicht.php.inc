//Der Quellcode zeigt nur einen kleinen 
//Ausschnitt aus der kompletten Index-Datei.
//Der nachfolgende Quellcode wurde von Herrn Schnuerer geeriert.
<?php include_once 'Classes/ArtikelDetails.php.inc';?>
<div class = "startseite">
 <article class="detailContent">
  <?php 
   $artikelDetails = new ArtikelDetails();
   $artikel = $artikelDetails->beschreibungAnzeigen($_GET['pid']);
   echo 
    '<h2>'.htmlspecialchars($artikel->Bezeichnung,ENT_QUOTES,'UTF-8').'</h2>';
  ?>
//...
