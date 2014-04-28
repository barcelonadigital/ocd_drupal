
(function($){
	$(document).ready(function(){
		//alert('aa');
		checkFormulas();
	});
}(window.jQuery));
	function checkFormulas(){
	  var field_formulas = Drupal.settings.field_formulas;
	  for (var key in field_formulas) {
	    var value = field_formulas[key];
	    if(value.indexOf("#DIVIDE")!=-1){
	      var array = value.split(",");
	      var a1 = document.querySelector("input[name='"+array[1].substring(1)+"']");
	      var a2 = document.querySelector("input[name='"+array[2].substring(1)+"']");
	      var a0 = document.querySelector("input[name='"+key+"']");
	      if (typeof a1 !== "undefined" && a1!=null && 
	    		  typeof a2 !== "undefined" && a2!=null &&
		    	  typeof a0 !== "undefined" && a0!=null) { 
	        var a1n = a1.value;
	        var a2n = a2.value;
	        if(isNumber(a1n) && isNumber(a2n)){
	          a0.value=(a1n/a2n);
	        }else{
	          a0.value='';
	        }
	        fireOnChange(a0);
	      }
	    }else if(value.indexOf("#RANGE")!=-1){
		  var value2 = value.substring(7,value.length-1);
		  array = value2.split(",");
	      var a1 = document.querySelector("input[name='"+array[0].substring(1)+"']");
	      var a0 = document.querySelector("input[name='"+key+"']");
	      var min = array[1];
	      var max = array[2];
	      var val1 = +array[3];
	      var val2 = +array[4];
	      var val3 = +array[5];
	      if (typeof a1 !== "undefined" && a1!=null &&
	          typeof a0 !== "undefined" && a0!=null) {
	    	var a1n = +(a1.value);
	    	if(a1n<min){
	    	  a0.value=val1;
	    	}else if(a1n>=min && a1n<max){
	    	  a0.value=val2;
	    	}else{
	    	  a0.value=val3;
	    	}
	    	fireOnChange(a0);
    	  }
	    }
	  }
	}
	function fireOnChange(a0) {
	    var event; // The custom event that will be created
	    if (document.createEvent) {
    	  event = document.createEvent("HTMLEvents");
    	  event.initEvent("change", true, true);
	    } else {
		  event = document.createEventObject();
		  event.eventType = "change";
	    }
	    event.eventName = "change";
	    if (document.createEvent) {
    	  a0.dispatchEvent(event);
	    } else {
		  a0.fireEvent("on" + event.eventType, event);
		}
	}
	function isNumber(n) {
	  return !isNaN(parseFloat(n)) && isFinite(n);
	}
