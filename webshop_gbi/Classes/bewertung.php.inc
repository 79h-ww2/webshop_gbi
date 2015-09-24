<?php
	class Bewertung{
		
		private $arr_sterne;
		
		/**
		 * Konstruktor
		 * @param unknown $arr_sterne
		 */
		function __construct($arr_sterne){
			$this->arr_sterne = $arr_sterne;
		}
		
		/**
		 * gibt als HTML-Code die Sterne aus
		 */
		public function zeige_sterne(){
			
			//Berechnet die Bewertung des Produkts (sollte hinterher in eine Klasse ausgelagert werden #################################### )
			$sterne_isgesammt = 0;
			$durschnittt_sterne = 0;
			for ($i = 0; $i < 5; $i++) {
				$sterne_isgesammt += $this->arr_sterne[$i];
				$durschnittt_sterne += $this->arr_sterne[$i] *($i + 1);
			};
			if ($sterne_isgesammt > 0){
				$durschnittt_sterne = $durschnittt_sterne/ $sterne_isgesammt;
			}
			
			$durschnittt_sterne_abs = round($durschnittt_sterne,0);
				
			//gelbe Sterne anzeigen
			for ($i = 0; $i < $durschnittt_sterne_abs; $i++){
				echo '<img alt="Stern gef&uuml;llt" src="./Images/Design/stern_gefuellt.png" class="stern" />';
			}
			//nicht ausgefüllte Sterne hinzufügen
			for ($j = $i; $j < 5; $j++){
				echo '<img alt="Stern ungef&uuml;llt" src="./Images/Design/stern_ungefuellt.png" class="stern" />';
			}
				
				
			echo " ".$sterne_isgesammt." Bewertung";
		}
	}
?>