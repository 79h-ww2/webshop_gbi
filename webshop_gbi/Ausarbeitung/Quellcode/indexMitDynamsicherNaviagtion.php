<!-- NAVIGATION -->
<!--
Der Quellcode zeigt nur einen kleinen Ausschnitt aus der kompletten Index-Datei.
Der nachfolgende Quellcode wurde von Herrn Schnürer geeriert.
-->
<nav class="nav">
 <ul class="navigation">
 <?php 
  $navi = new Navigation();
  $arr_kategorie = $navi->erstelle_array_kategorien();	
  for ($i = 0; $i < count($arr_kategorie); $i++){
   $kategorie = $arr_kategorie[$i];
   if ( $i != 0){
    //Auflistung der Produktkategorie (Zubehör)
   }
   else{
    //Auslistung der Produktkategorie (ohne Link)
    $bauart = $navi->erstelle_array_bauart();
    foreach ($bauart as $b){
     //Auflisten der Fahrradbauarten    
    }
 ?>
 </ul>
</nav>
