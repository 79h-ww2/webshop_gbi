<?php
$durchschnittsterne = 0;
$anzahlBewertungen = ($arr_sterne [0] + $arr_sterne [1] + $arr_sterne [2] + $arr_sterne [3] + $arr_sterne [4]);
if ($anzahlBewertungen > 0)
	$durchschnittsterne = round ( ($arr_sterne [0] * 1 + $arr_sterne [1] * 2 + $arr_sterne [2] * 3 + $arr_sterne [3] * 4 + $arr_sterne [4] * 5) / ($arr_sterne [0] + $arr_sterne [1] + $arr_sterne [2] + $arr_sterne [3] + $arr_sterne [4]), 1 );
?>
<div class="popupBewertungProduktauflistung">
	<div class="haken_sprechblase"></div>
	<div class="contentPopupBewertungProduktauflistung">
		<div class="popupBewertungProduktauflistungSterneGesamt">
			<?php echo $durchschnittsterne; ?> von 5 Sterne
		</div>
		<div class="popupBewertungTable">
			<div class="ZeileSterne">
				<tr>
					<td><span class="beschriftung"> 1 Stern:</span></td>
					<td>
					<?php
					$anzahl = $arr_sterne [0];
					if ($anzahl == '') {
						$anzahl = '-';
					}
					?>
					<span class="anzahlBewertung"> <?php echo $anzahl;?></span>
					</td>

				</tr>
			</div>
			<div class="ZeileSterne">
				<tr>
					<td><span class="beschriftung"> 2 Sterne:</span></td>
					<td>
					<?php
					$anzahl = $arr_sterne [1];
					if ($anzahl == '') {
						$anzahl = '-';
					}
					?>
						<span class="anzahlBewertung"> <?php echo $anzahl;?></span>
					</td>
				</tr>
			</div>
			<div class="ZeileSterne">
				<tr>
					<td><span class="beschriftung"> 3 Sterne:</span></td>
					<td>
					<?php
					$anzahl = $arr_sterne [2];
					if ($anzahl == '') {
						$anzahl = '-';
					}
					?>
						<a><?php echo $anzahl;?></a>
					</td>
				</tr>
			</div>
			<div class="ZeileSterne">
				<tr>
					<td><span class="beschriftung"> 4 Sterne:</span></td>
					<td>
					<?php
					$anzahl = $arr_sterne [3];
					if ($anzahl == '') {
						$anzahl = '-';
					}
					?>
						<a><?php echo $anzahl;?></a>
					</td>
				</tr>
			</div>
			<div class="ZeileSterne">
				<tr>
					<td><span class="beschriftung"> 5 Sterne:</span></td>
					<td>
					<?php
					$anzahl = $arr_sterne [4];
					if ($anzahl == '') {
						$anzahl = '-';
					}
					?>
						<a><?php echo $anzahl;?></a>
					</td>
				</tr>
			</div>
		</div>
		<div class="popupBewertungLinkAlleBewertungen">
			<?php
			
$text = '';
			if ($anzahlBewertungen == 1) {
				$text = 'Eine Bewertung anzeigen';
			} elseif ($anzahlBewertungen > 1) {
				$text = 'Alle ' . $anzahlBewertungen . ' Bewertung anzeigen';
			}
			?>
			<a href="#"><?php echo $text; ?></a>
		</div>
	</div>
</div>
