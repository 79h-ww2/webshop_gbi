<?php
	$durchschnittsterne = round(($sterne1*1 + $sterne2*2 + $sterne3*3 + $sterne4*4 + $sterne5*5) /($sterne1 + $sterne2 + $sterne3 + $sterne4 + $sterne5) ,1);
?>
<div class="popupBewertungProduktauflistung" >
	<div class="haken_sprechblase" >
	</div>
	<div class="contentPopupBewertungProduktauflistung" >
		<div class="popupBewertungProduktauflistungSterneGesamt" >
			<?php echo $durchschnittsterne; ?> von 5 Sterne
		</div>
		<div class="ZeileSterne" >
			<span class="beschriftung" >
				1 Stern:
			</span>
		</div>
		<div class="ZeileSterne" >
			<span class="beschriftung" >
				2 Sterne:
			</span>
		</div>
		<div class="ZeileSterne" >
			<span class="beschriftung" >
				3 Sterne:
			</span>
		</div>
		<div class="ZeileSterne" >
			<span class="beschriftung" >
				4 Sterne:
			</span>
		</div>
		<div class="ZeileSterne" >
			<span class="beschriftung" >
				5 Sterne:
			</span>
		</div>
	</div>
</div>