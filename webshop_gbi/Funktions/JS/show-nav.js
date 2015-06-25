$('.show-nav').on('click',function(){
	$('header').toggleClass('einblenden');
})
function einblenden(div){
	with(document.getElementById(div).style){
		if(display=="none"){
			
			display="table";
		}
		else{
			display="none";
			
		}
	}
}