<?php
	$durchschnittsterne = 0;
	if (($arr_sterne[0]+ $arr_sterne[1] + $arr_sterne[2] + $arr_sterne[3] + $arr_sterne[4]) > 0) $durchschnittsterne = round(($arr_sterne[0]*1 + $arr_sterne[1]*2 + $arr_sterne[2]*3 + $arr_sterne[3]*4 + $arr_sterne[4]*5) /($arr_sterne[0]+ $arr_sterne[1] + $arr_sterne[2] + $arr_sterne[3] + $arr_sterne[4]) ,1);
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