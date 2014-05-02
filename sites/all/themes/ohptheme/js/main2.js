(function() {

//   ___   __   ____  ____  ___  ____  ____   __  
//  / __) / _\ (  _ \(  __)/ __)(  __)(  _ \ / _\ 
// ( (__ /    \ ) _ ( ) _)( (__  ) _)  )   //    \
//  \___)\_/\_/(____/(____)\___)(____)(__\_)\_/\_/
//

// Ejemplo de uso de la búsqueda
  $(document).ready(function() {
    $("div.custom-cabecera input.custom-search-query").focus(function(event) {
      event.preventDefault();
      $(this).addClass("focus");
      if (event.type === "focus" || $(this).attr("value")) {
        $("div.custom-cabecera div.custom-search-results").show();
      }
    });
    $("div.custom-cabecera input.custom-search-query").blur(function(event) {
      event.preventDefault();
      $(this).removeClass("focus");
      $("div.custom-cabecera div.custom-search-results").hide();
    });
    $("div.custom-cabecera input.custom-search-query").keyup(function(event) {
      event.preventDefault();
      var respuesta_ajax;
      if ($(this).val()) {
        respuesta_ajax = "<li><a href=\"#\" class=\"user\"><img src=\"img-contenido/perfil-41x41.jpg\" alt=\"Chewacca Doku avatar\"><span>Patient</span> <strong>Che</strong>wacca Doku</a></li><li><a href=\"#\" class=\"tasks\"><span>Exercise</span> Standst<strong>ill</strong></a></li><li><a href=\"#\" class=\"community\"><span>Community</span> Forum post <strong>tit</strong>le</a></li><li><a href=\"#\" class=\"report\"><span>Statistic</span> Graphic <strong>tit</strong>le</a></li>";
      } else {
        respuesta_ajax = "";
      }
      $("div.custom-cabecera div.custom-search-results ul").html(respuesta_ajax);
    });
  });


//  ____  __  ____  _  _  _  _  __     __   ____  __  __  
// (  __)/  \(  _ \( \/ )/ )( \(  )   / _\ (  _ \(  )/  \ 
//  ) _)(  O ))   // \/ \) \/ (/ (_/\/    \ )   / )((  O )
// (__)  \__/(__\_)\_)(_/\____/\____/\_/\_/(__\_)(__)\__/ 
//

// Formulario 04-my_account.html. Cambia de Vista a edición
  $(document).ready(function() {
    $("a.editdataform").click(function(event) {
      event.preventDefault();
      $(".dataform").addClass("editmode");
      $(".dataform input").removeAttr("disabled");
      $("button.disabled").removeAttr("disabled");
      $("button.disabled").removeClass("disabled");
      $(".botoneslateralescontainer").addClass("editmode");
    });
    $("a.editdataseccio").click(function(event) {
      event.preventDefault();
      $(this).parent().parent().parent().find("input").removeAttr("readonly");
      $(this).parent().parent().parent().find("textarea").removeAttr("readonly");
      $(this).parent().parent().parent().addClass("editmode");
      var radiobutton = $(this).parent().parent().parent().find("input[type='radio']").first();
      if(typeof radiobutton !== 'undefined'){
          updateChecks(radiobutton);
      }
    });
    $("a.savedataseccio").click(function(event) {
      event.preventDefault();
      $(this).parent().parent().parent().find("input").attr("readonly","readonly");
      $(this).parent().parent().parent().find("textarea").attr("readonly","readonly");
      $(this).parent().parent().parent().removeClass("editmode");
    });
    $("a#buttonDesarPrescripcioCVSO").click(function(event) {
      value = jQuery( 'input[name=prescripcio]:checked' ).val();
      if (typeof value !== 'undefined' && value==='0') {
          event.preventDefault();
          location.href = "13-CVSO-candidat-OCD_solicitud.html";
      }
    });

// Para usar dropdown como un select. Para enviar los datos en formulario hay que recoger el contenido .text() de button.dropdown-toggle como valor.
    $(".dropdown-menu li a").click(function(event) {
      if($(this).attr("href")==='#'){
        event.preventDefault();
      }
      var triangulo=($(this).parent().parent().parent().children('button.btn.dropdown-toggle span.caret.triangulo'));
      $(this).parent().parent().parent().children('button.btn.dropdown-toggle').html($(this).text() + "<span class=\"caret"+(triangulo?" triangulo":"")+"\"></span>");
      $(this).parent().parent().parent().removeClass('open');
      
      if($(this).parent().parent().parent().children('button.btn.dropdown-toggle').length>0){
    	  var item = $(this).parent().parent().parent().children('button.btn.dropdown-toggle')[0];
          var targetId = $(item).data('targetinput');
    	  var valueSelected = $(this).data('value');
    	  if(typeof targetId !== 'undefined' && typeof valueSelected !== 'undefined'){
    		  //var targetObj = $('#'+targetId);
    		  //var targetObj=document.getElementsByName(targetId);
    		  var targetObj=$('[name="' + targetId + '"]');
    		  if(targetObj.length>0){
    			  $(targetObj).val(valueSelected);
    			  $(targetObj).change()
    		  }
    	  }
      }
    });
  });
  
    $("#buttonEnter").click(function(event) {
      value = $( 'button.btn.dropdown-toggle' ).text();
      if(value==='AP'){
          location.href = "01-AP-inici.html";
      }else if(value==='RAE'){
          location.href = "16-RAE-inici.html";
      }else if(value==='CVSO'){
          location.href = "10-CVSO-inici.html";
      }else if(value==='Hospital'){
          location.href = "31-Hospital-inici.html";
      }
    });

// Scroll i index flotant a la esquerra de la pantalla
  $(document).ready(function() {
    $(window).scroll(function () {
        var y = $(this).scrollTop();
        var diff = $('.custom-menuprincipal').height();
        var activePosition=$(document).height();
        $("a.drecera").each(function(i, item) {
            var targetdiv = $(item).attr("data-targetdiv");
            var targetdivObj = $('#'+targetdiv);
            var z = targetdivObj.offset().top - diff;
            if (y > z || z > activePosition) {
                $(item).removeClass('autoactive');
            }
            else{
                $(item).addClass('autoactive');
                activePosition = z;
            }
        });
    });
    
    //smoothscroll
    $("a.drecera").click(function(e) {
	    e.preventDefault();
	    var target = this.hash,
	    $target = $(target);
	    $('html, body').stop().animate({
	        'scrollTop': $target.offset().top - $('.custom-menuprincipal').height()
	    }, 500, 'swing', function () {
	        window.location.hash = target;
	    });
	});
  });

// Calcul index Tiffeneau
  $(document).ready(function() {
    $('input.espirovalues[type="text"]').change(function() {
        var valor1 = $("input[name='valorFEV']").val().replace(',', '.' );
        var valor2 = $("input[name='valorFVC']").val().replace(',', '.' );
        if($.isNumeric(valor1) && $.isNumeric(valor2)){
            var newval = (valor1/valor2)*100;
            $("input[name='indiceTiffeneau']").val(parseFloat(newval).toFixed(2));
        }else{
            $("input[name='indiceTiffeneau']").val('');
        }
    });
  });
  
  $(document).ready(function() {
    checkPrescripcioOCD();
    $('input[name="valorPO2"]').change(function() {
        checkPrescripcioOCD();
    });
    $('input[name="hipertensio"]').change(function() {
        checkPrescripcioOCD();
    });
    $('input[name="pulmonale"]').change(function() {
        checkPrescripcioOCD();
    });
    $('input[name="policitemia"]').change(function() {
        checkPrescripcioOCD();
    });
  });
  
  function checkPrescripcioOCD(){
      var valorPO2 = $("input[name='valorPO2']").val();
      var someSelected= false;
      var value = jQuery( 'input[name=hipertensio]:checked' ).val();
      if (typeof value !== 'undefined' && value==='0') {
          someSelected=true;
      }
      value = jQuery( 'input[name=pulmonale]:checked' ).val();
      if (typeof value !== 'undefined' && value==='0') {
          someSelected=true;
      }
      value = jQuery( 'input[name=policitemia]:checked' ).val();
      if (typeof value !== 'undefined' && value==='0') {
          someSelected=true;
      }
      if(typeof valorPO2 !== 'undefined' && $.isNumeric(valorPO2.replace(',', '.' ))){
          $("#motiu1").hide();
          $("#motiu2").hide();
          $("#motiu3").hide();
          $("#motiu4").hide();
          $("#fieldset2").hide();
          $("#drecera2").hide();
          if(valorPO2>=55 && valorPO2<60){
              $("#fieldset2").show();
              $("#drecera2").show();
              if(someSelected){
                  $("#motiu2").show();
                  
                  $("input[name=prescripcio][value=0]").prop('checked', true);
                  
                  $("#label1").hide();
                  $("#label2").hide();
                  $("#label3").hide();
              }else{
                  $("#motiu4").show();
                  
                  $("#label1").show();
                  $("#label3").show();
                  updateChecks($('#prescripcio_0'));
              }
          }else if(valorPO2>=60){
              $("#motiu3").show();

              $("#label1").show();
              $("#label3").show();
              updateChecks($('#prescripcio_0'));
          }else if(valorPO2<55){
              $("#motiu1").show();
              
              $("#label1").hide();
              $("#label2").hide();
              $("#label3").hide();
                  
              $("input[name=prescripcio][value=0]").prop('checked', true);
          }
      }
  }
  $(document).ready(function() {
	  checkNifNiePas();
	  $("#nie").keyup(function() {checkNifNiePas();});
	  $("#nif").keyup(function() {checkNifNiePas();});
	  $("#pas").keyup(function() {checkNifNiePas();});
	  $("#formSearch #cip").keyup(function() {checkNifNiePas();});
	  $("#nie").change(function() {checkNifNiePas();});
	  $("#nif").change(function() {checkNifNiePas();});
	  $("#pas").change(function() {checkNifNiePas();});
	  $("#formSearch #cip").change(function() {checkNifNiePas();});
  });
  function checkNifNiePas() {
	  var nieInput = $("#nie");
	  var nifInput = $("#nif");
	  var pasInput = $("#pas");
	  var cipInput = $("#formSearch #cip");
	  if (typeof nieInput !== 'undefined' && typeof $(nieInput).val() !== 'undefined' && $(nieInput).val() !== '') {
		  $(nieInput).not( "#newForm2 #nie" ).attr('disabled', false);
		  $(nifInput).not( "#newForm2 #nif" ).attr('disabled', true);
		  $(pasInput).not( "#newForm2 #pas" ).attr('disabled', true);
		  $(cipInput).attr('disabled', true);
		  $("#newForm2 #nie").attr('readonly', false);
		  $("#newForm2 #nif").attr('readonly', true);
		  $("#newForm2 #pas").attr('readonly', true);
	  }else if (typeof nifInput !== 'undefined' && typeof $(nifInput).val() !== 'undefined' && $(nifInput).val() !== '') {
		  $(nieInput).not( "#newForm2 #nie" ).attr('disabled', true);
		  $(nifInput).not( "#newForm2 #nif" ).attr('disabled', false);
		  $(pasInput).not( "#newForm2 #pas" ).attr('disabled', true);
		  $(cipInput).attr('disabled', true);
		  $("#newForm2 #nie").attr('readonly', true);
		  $("#newForm2 #nif").attr('readonly', false);
		  $("#newForm2 #pas").attr('readonly', true);
	  }else if (typeof pasInput !== 'undefined' && typeof $(pasInput).val() !== 'undefined' && $(pasInput).val() !== '') {
		  $(nieInput).not( "#newForm2 #nie" ).attr('disabled', true);
		  $(nifInput).not( "#newForm2 #nif" ).attr('disabled', true);
		  $(pasInput).not( "#newForm2 #pas" ).attr('disabled', false);
		  $(cipInput).attr('disabled', true);
		  $("#newForm2 #nie").attr('readonly', true);
		  $("#newForm2 #nif").attr('readonly', true);
		  $("#newForm2 #pas").attr('readonly', false);
	  }else if (typeof cipInput !== 'undefined' && typeof $(cipInput).val() !== 'undefined' && $(cipInput).val() !== '') {
		  $(nieInput).not( "#newForm2 #nie" ).attr('disabled', true);
		  $(nifInput).not( "#newForm2 #nif" ).attr('disabled', true);
		  $(pasInput).not( "#newForm2 #pas" ).attr('disabled', true);
		  $(cipInput).attr('disabled', false);
		  $("#newForm2 #nie").attr('readonly', true);
		  $("#newForm2 #nif").attr('readonly', true);
		  $("#newForm2 #pas").attr('readonly', true);
	  }else{
		  $(nieInput).not( "#newForm2 #nie" ).attr('disabled', false);
		  $(nifInput).not( "#newForm2 #nif" ).attr('disabled', false);
		  $(pasInput).not( "#newForm2 #pas" ).attr('disabled', false);
		  $(cipInput).attr('disabled', false);
		  $("#newForm2 #nie").attr('readonly', false);
		  $("#newForm2 #nif").attr('readonly', false);
		  $("#newForm2 #pas").attr('readonly', false);
	  }
  }
  
// Cambia los fondos de la tabla según el estado en admin-matrix.html
  $(document).ready(function() {
    $(".adminmatrix table td input[type='checkbox']").change(function() {
      if ($(this).prop("checked")) {
        $(this).parent().addClass("active");
      } else {
        $(this).parent().removeClass("active");
      }
    });
  });

// Cambia el estilo del label de radiobuttons en algunas páginas
  $(document).on("change", "input[type='radio']",function () {
	  updateChecks($(this));
      $(this).parent().addClass("active");
  });
  $(document).ready(function() {
    $("input[type='radio']").mousedown(function() {
        var $self = $(this);
        if( $self.is(':checked') ){
          var uncheck = function(){
            setTimeout(function(){
                $self.removeAttr('checked');
                $self.parent().removeClass("active");
                updateChecks($self);
                checkPrescripcioOCD();
            },0);
          };
          var unbind = function(){
            $self.unbind('mouseup',up);
          };
          var up = function(){
            uncheck();
            unbind();
          };
          $self.bind('mouseup',up);
          $self.one('mouseout', unbind);
        }
    });
  });
  $(document).ready(function() {
    $("input[type='checkbox']").change(function() {
      updateChecks($(this));
      $(this).parent().addClass("active");
    });
  });
  function updateChecks(radioButton) {
     radioButton.parent().parent().children("label").each(function(i, item) {
        if (!$(item).children("input[type='radio']").prop("checked") &&
                !$(item).children("input[type='checkbox']").prop("checked")) {
          $(item).removeClass("active");
        }
        if ($(item).hasClass("sub1")||$(item).hasClass("sub2")||$(item).hasClass("sub3")||$(item).hasClass("sub4")) {
            var parentRadio = $(item).attr("data-parent");
            var parentRadioObj = $('#'+parentRadio);
            if (typeof parentRadioObj !== "undefined" && parentRadioObj.prop("checked")) {
                $(item).show();
            }else if (typeof parentRadioObj === "undefined"){
                $(item).show();
            }else{
                $(item).hide();
            }
        }
      });
  }

// Ajusta el tamaño del input al contenido
  $(document).ready(function() {
    $('input.autosize[type="text"]').each(function() {
      $(this).attr('size', $(this).val().length);
    });
  });
  $('input.autosize[type="text"]').keyup(function() {
    var size;
    size = $(this).val().length;
    if (size === 0) {
      size = 1;
    }
    $(this).attr('size', size);
  });

// Lanzamiendo y configuración de slider, con plugin js/vendor/bootstrap-slider-edited.js
  $(document).ready(function() {
    $(".input-slider").slider({
      formater: function(value) {
        var decimales, resultado, step;
        step = this.step * 1;
        decimales = ((+step).toFixed(5)).replace(/^-?\d*\.?|0+$/g, '').length;
        resultado = value.toFixed(decimales);
        for(a=1;a<=8;a++){
          $(this.valueDiv[0]).removeClass('size'+a);
        }      
        if (resultado.length >= 1 && resultado.length <= 8) {
          $(this.valueDiv[0]).addClass('size'+resultado.length);
        } else {
          $(this.valueDiv[0]).addClass('size1');
        }
        resultado_inical=resultado;
        for(a=0;a<resultado_inical.length;a++){
          if(resultado_inical.substring(a,a+1)=='.'){
            resultado = "<span>"+resultado_inical.substring(0,a)+"</span>."+resultado_inical.substring(a+1)
          }
        }
        return resultado;
      },
      selection: 'none'
    });
  });

// Ejemplo de muesta y oculta y orden en schedule-new-session-1-C.html
  function sessionListEventos(){  // Asigna los eventos
    $('.session-list>ol>li>.header>.part-b>.actions>a.conf, .session-list>ol>li>.header>.part-b>.actions>a.close, .game-list>ol>li>.header>.part-b>.actions>a.conf, .game-list>ol>li>.header>.part-b>.actions>a.close').unbind().click(function(event) {
      event.preventDefault();
      var li = $(this).parents('li:first');
      if($(li).hasClass('open')){
        $(li).removeClass('open')
      } else {
        $(li).addClass('open')
      }
    });
    $(document).ready(function() {
      $('.session-list>ol>li>.header>.part-b>.actions>a.up, .session-list>ol>li>.header>.part-b>.actions>a.down, .game-list>ol>li>.header>.part-b>.actions>a.up, .game-list>ol>li>.header>.part-b>.actions>a.down').unbind().click(function(event) {
        event.preventDefault();
        // objeto li
        var li = $(this).parents('li:first');
        // numero en la lista
        var index = $(li).index();
        // el indice a intercambiar
        var indexFor = index;
        // objeto ol
        var ol = $(this).parents('ol:first');
        // todos los li en el ol
        var list = $(ol).children();
        if($(this).hasClass('up')){ // si sube
          if(index>0){ // si ya no está el primero
            indexFor = index - 1; // el destino del objeto pulsado es el anterior
          }
        } else { // si baja
          if(index<list.length-1){ // si ya no está el último
            indexFor = index + 1; // el destino del objeto pulsado es el siguiente
          }
        }
        var temp = list[indexFor]; // li temporal
        list[indexFor] = list[index];
        list[index] = temp;
        $(ol).empty(); // vacía ol
        $.each(list, function(index, val) { // rellena ol con el nuevo orden
           $(ol).append(val);
        });
        $(ol).children().each(function(index, el) {
          $(el).find('.part-a:first').text(index+1); // Le pone los números ordenadamente.
        });
        sessionListEventos(); // al manipularlo pierde los eventos, aquí volvemos a asignárselos.
      });
    });
  }
  $(document).ready(function() {
    sessionListEventos();
  });

// ____   __  ____  ____  ____  __  ___  __ _  ____  ____ 
//(    \ / _\(_  _)(  __)(  _ \(  )/ __)(  / )(  __)(  _ \
// ) D (/    \ )(   ) _)  ) __/ )(( (__  )  (  ) _)  )   /
//(____/\_/\_/(__) (____)(__)  (__)\___)(__\_)(____)(__\_)
//

 $(document).ready(function() {
   $('input.form-control.date').datepicker({
       format: "dd/mm/yyyy",
       weekStart: 1
       ,
       language: "linkcare"
   });
 });


//  ____  __  _  _  ____  ____    ____  __  ____  _  _    ____  _  _  ____  ____  __   __ _  ____ 
// (  __)(  )( \/ )(  __)(    \  (  __)/  \(  _ \( \/ )  (  _ \/ )( \(_  _)(_  _)/  \ (  ( \/ ___)
//  ) _)  )(  )  (  ) _)  ) D (   ) _)(  O ))   // \/ \   ) _ () \/ (  )(    )( (  O )/    /\___ \
// (__)  (__)(_/\_)(____)(____/  (__)  \__/(__\_)\_)(_/  (____/\____/ (__)  (__) \__/ \_)__)(____/
// 

  $(document).ready(function() {
	  var offsetFn = function () {
          var objBotoneslaterales = $('.botoneslaterales');
          var objMenuprincipal = $('.custom-menuprincipal');
		  var h = objBotoneslaterales.position().top-objMenuprincipal.height();
          return h;
      };
      $(".botoneslateralescontainer").affix({
          offset: { 
              top: offsetFn,
              bottom: (0)
          }
      });
  });


}).call(this);
