var debug = false;	// debug=true per a mostrar logs (alerts)
var cr = '\n';
var valorRetorn;
var AJAX_PARAMETERS_DELIMITER = "$#@";
var selectMandatoryTargets = "";

// Control formules de calcul en temps de carrega
var estatCarregant = false;

var g = new docRsaClass();

function docRsaClass() {
    this.objectes;
    this.claus;
	this.clausIdx;
    
	this.cargarRec = function(p_obj) {
		var k;
		var o;
		if(p_obj.hasChildNodes()) {
			for(k=0; k<p_obj.childNodes.length; k++) {
				o = p_obj.childNodes[k];
				if(o.id != undefined) {
					if(o.id != '') {
						this.objectes[o.id] = o;
						this.claus[this.clausIdx] = o.id;
						this.clausIdx++;					
					}
				}
				this.cargarRec(o);
			}
		}
	}
	
    this.cargar = function() {
		this.objectes = new Array();
        this.claus = new Array();
		this.clausIdx = 0;
		
	    this.cargarRec(document.body);
	}
    
    this.getElementById = function(p_id) {
    	if(this.objectes == null) {
        	this.cargar();
    	}
    	if(this.objectes[p_id] == undefined) {
    		return null;
    	}
    	return this.objectes[p_id];
    }
    
    this.getClaus = function() {
    	if(this.objectes == null) {
    		this.cargar();
    	}
    	return this.claus;
    }
    
    this.print = function() {
    	var text = '';
    	for (var j=0; j<this.claus.length; j++) {
    		text += this.claus[j] + ';';
    	}
    	alert(text);
    }
};

function changeValue() {
    dadaCanviada = true;
	if(g.getElementById("form:hiddenDadaCanviada")) {
		g.getElementById("form:hiddenDadaCanviada").value = true;
    }
}

function getChangeValue() {
    return g.getElementById("form:hiddenDadaCanviada").value;
}

function recarregaValorsDomini(idVariable, idDomini, condition) {
	var desplegable = g.getElementById("form:INPUT_"+idVariable);
	var myComboLoader = new ConditionalCombo();
	var async=false;
	myComboLoader.prepare(url, method, async);
	myComboLoader.setForm("form");
	condition = replaceSpecialCharacters(condition);
	myComboLoader.directCall(desplegable, idVariable, condition);
}

function replaceSpecialCharacters(groupOfCharacters){	
	var CHARACTER_FIRST_INTERROGATION = "_CHARACTER_FIRST_INTERROGATION_";
	var VALUE_CHARACTER_FIRST_INTERROGATION = "?";
	var CARACTER_LAST_INTERROGATION = "_CHARACTER_LAST_INTERROGATION_";
	var VALUE_CHARACTER_LAST_INTERROGATION = "?";       
	var CHARACTER_PER_CENT = "_CHARACTER_PER_CENT_";
	var VALUE_CHARACTER_PER_CENT = "%";
	
	groupOfCharacters = replaceAll(groupOfCharacters, VALUE_CHARACTER_FIRST_INTERROGATION, CHARACTER_FIRST_INTERROGATION);	
	groupOfCharacters = replaceAll(groupOfCharacters, VALUE_CHARACTER_LAST_INTERROGATION, CARACTER_LAST_INTERROGATION);	
	groupOfCharacters = replaceAll(groupOfCharacters, VALUE_CHARACTER_PER_CENT, CHARACTER_PER_CENT);

	return groupOfCharacters; 
}

function replaceAll(base, dataToSearch, dataToReplace){

    while(base.indexOf(dataToSearch)!=-1)
    	base =  base.replace(dataToSearch, dataToReplace);
        
	return base;
}

function recarregaValorsDominiAutoSelect(idVariable) {
	if(g.getElementById("form:INPUT_"+idVariable)) {
		var valor = g.getElementById("form:INPUT_"+idVariable);
		var cond = g.getElementById("form:COND_"+idVariable);
		if(valor.value != "" && valor.value != null) {
    		valor.onchange();
		}
	}
}

function validacio_sync(target, formulaid, actualLevelVariables, actualVariable, actualVariableValue) {
	
	var retorna="";
	var label = "";
	var actualLevelValues = null;
	if(g.getElementById("form:LABEL_"+target.split(':')[0])) {
		label = g.getElementById("form:LABEL_"+target.split(':')[0]).innerHTML;
	}
	if(g.getElementById("form:LABEL_"+actualVariableValue)) { 
		label = g.getElementById("form:LABEL_"+actualVariableValue).innerHTML;
	}
	
	if(actualLevelVariables != null) {
	    var ids = actualLevelVariables.split(":");
	    actualLevelValues = "";
	    
        for(var i = 0; i< ids.length; i++ ) {
                var actual = ids[i];
                var attrActual = 'ATTR_' + actual;
                eval("var attrValue = " + attrActual +";");
				var ident = actual.split("_");
				var newValue = '<value reg_creg="' + ident[0] + '" nrs_cnrs="' + ident[1] + '" vnr_cvnr="' + ident[2] +'">';
				try {
					attrValue = delXmlHead(attrValue.replace("<value>", newValue));
				} catch (e) {
					//alert('Catch: attrValue:' +attrValue+ ' newValue: '+newValue + ' e:'+e);
				}
				actualLevelValues += attrValue;
        }   
    } 
    var reg_creg=g.getElementById("form:h_registerid");
    var nrs_cnrs=g.getElementById("form:h_levelid");
    var orn_corn="";
    var orn_corn_pare = "";
   
    if(g.getElementById("form:h_occurrence")) {
    	orn_corn=g.getElementById("form:h_occurrence").value;
    }
    if(g.getElementById("form:h_parentoccurrence")) {
    	orn_corn_pare=g.getElementById("form:h_parentoccurrence").value;
    }
    
    if(actualLevelValues != null) {
    	actualLevelValues = '<values reg_creg="' + reg_creg.value + '" nrs_cnrs="' + nrs_cnrs.value + '" for_cfor="' + formulaid  
    					+ '" orn_corn="' + (orn_corn == "" ? null : orn_corn) + '" orn_corn_pare="' + (orn_corn_pare=="" ? null :orn_corn_pare) +'">'
    					+ actualLevelValues + '</values>';
    }

    var attrActual = 'ATTR_' + actualVariable;
    eval("var attrValue = " + attrActual +";");
	var ident = actualVariable.split("_");
	var newValue = '<value reg_creg="' + ident[0] + '" nrs_cnrs="' + ident[1] + '" vnr_cvnr="' + ident[2] + '">';
	attrValue = delXmlHead(attrValue.replace("<value>", newValue));
	actualVariableValue = attrValue;

	var retorna = doValidateSync("form",formulaid, actualLevelValues, actualVariableValue);
	if(retorna != "TRUE") {
		return label + retorna + "\n";
	} else { 
		return "TRUE";
	}
}

function validacio_variable_sync(target, formulaid, actualLevelVariables, actualVariable, actualVariableValue) {
	var retorna = validacio_sync(target, formulaid, actualLevelVariables, actualVariable, actualVariableValue);
	if(retorna == "TRUE") return "";
	else return retorna;
}

function validacio_variable_nivell(formulaid, actualLevelVariables, actualVariable, actualVariableValue) {
	var retorna = validacio_sync('', formulaid, actualLevelVariables, actualVariable, actualVariableValue); 
	if(retorna == "TRUE") return true;
	else return retorna;
}

//y otra funciona "vacia" para rellenarla cuando tenga el objeto para la carga

function carregaAtribut(input) {
	var myAjaxObj= new VariableAttributesAjax();
	var async = false;
	myAjaxObj.prepare(url, method, async);
	myAjaxObj.setForm("form");	
	
	var res = myAjaxObj.directCall(input,false);
	return res;
}

function carregaAtributCM(input,cmCodi,cmDesc) {
	var valor = g.getElementById("form:INPUT_"+input).innerHTML;
	var compleix1 = true;
	var compleix2 = true;
	var missatge = '';
	if(cmCodi != -1 && cmDesc != -1) {
		if(parseInt(valor.length)<parseInt(Math.min(cmCodi,cmDesc)) && valor.length > 0) {
			missatge = 'El text ha de tenir longitud mínima ' +Math.min(cmCodi,cmDesc);
			compleix1 = false;
		}
	} else if (cmCodi != -1) {
		if(valor.length<cmCodi && valor.length > 0) {
			missatge = 'El text del codi ha de tenir longitud mínima ' + cmCodi;
			compleix1 = false;
		}
	} else if (cmDesc != -1) {
		if(valor.length<cmDesc && valor.length > 0) {
			missatge = 'El text de la descripció ha de tenir longitud mínima ' + cmDesc;
			compleix2 = false;
		}
	}
	
	if(!compleix1 || !compleix2) {
		g.getElementById("form:INPUT_"+input).innerText='';
		g.getElementById("form:INPUT_"+input).innerHTML='';
		g.getElementById('form:INPUT2_'+input).innerText='Sense determinar';
		g.getElementById('form:INPUT2_'+input).innerHTML='Sense determinar';
		alert(missatge);
		deleteNavigationPopUp();
		return true;
	}
	var myAjaxObj= new VariableAttributesAjax();
	var async = false;
	myAjaxObj.prepare(url, method, async);
	myAjaxObj.setForm("form");	
	
	var esNoCercable = (cmCodi == "-1" && cmDesc == "-1");
	//Mirar esto... quitandolo no da error de cruz roja en Tomcat
	var res = myAjaxObj.directCall(input,esNoCercable);
	return res;
}

function carregaAtributSimple(input, valor) {    // Recupera atributs de la variable en xml
	var reg = input.split("_")[1];
	var nrs = input.split("_")[2];
	var vnr = input.split("_")[3];

	var stringXml = '<value reg_creg="' + reg + '" nrs_cnrs="' + nrs + '" vnr_cvnr="' + vnr + '"><CODI></CODI><DESCRIPCIO>' + escapa_xml(valor) + '</DESCRIPCIO></value>';
	eval(input + " = stringXml;");
}

// Variables booleanes de tipus Missatge
function carregaAtributBooleanSimple(input, valor) {    // Recupera atributs de la variable en xml
	var reg = input.split("_")[1];
	var nrs = input.split("_")[2];
	var vnr = input.split("_")[3];
	
	var codi = '';
	var descripcio = 'Sense determinar';
	
	if(valor == null || valor == '') {
		codi = '';
		descripcio = 'Sense determinar';
	} else if(valor == true || valor == 'TRUE' || valor == 'true' || valor == 'S') {
		codi = 'S';
		descripcio = 'Si';
	} else {
		codi = 'N';
		descripcio = 'No';
	}
	var objCodi = g.getElementById("form:"+input.replace("ATTR_","INPUT_"));
	var objDesc = g.getElementById("form:"+input.replace("ATTR_","INPUT2_"));
	if(objCodi) {
		objCodi.innerText = codi;
		objCodi.innerHTML = codi;
	}
	if(objDesc) {
		objDesc.innerText = descripcio;
		objDesc.innerHTML = descripcio;
	}

	var stringXml = '<value reg_creg="' + reg + '" nrs_cnrs="' + nrs + '" vnr_cvnr="' + vnr + '"><CODI>'+escapa_xml(codi)+'</CODI><DESCRIPCIO>' + escapa_xml(descripcio) + '</DESCRIPCIO></value>';
	
	eval(input + " = stringXml;");
}

function carregaAtributBasic(input, index, valor) {    // Recupera atributs de la variable en xml 
	var reg = input.split("_")[1];
	var nrs = input.split("_")[2];
	var vnr = input.split("_")[3]; 
	if(index == "") {
		var stringXml = '<value reg_creg="' + reg + '" nrs_cnrs="' + nrs + '" vnr_cvnr="' + vnr + '"><CODI></CODI><DESCRIPCIO></DESCRIPCIO></value>';
	} else {
		var stringXml = '<value reg_creg="' + reg + '" nrs_cnrs="' + nrs + '" vnr_cvnr="' + vnr + '"><CODI>' + escapa_xml(index) + '</CODI><DESCRIPCIO>' +escapa_xml(valor) + '</DESCRIPCIO></value>';
	}
	
	eval(input + " = stringXml;");
}

function carregaAtributBasicAmbPipe(input, index, valor) {    // Recupera atributs de la variable en xml
	var nouValor = valor.substr(valor.indexOf('|')+1,valor.length);
	carregaAtributBasic(input, index, nouValor);
}

function carregaAtributCheck(input, index) {    // Recupera atributs de la variable en xml 
	var reg = input.split("_")[1];
	var nrs = input.split("_")[2];
	var vnr = input.split("_")[3];
	var stringXml = '';
	if(index == "S" || index == "TRUE") {
		stringXml = '<value reg_creg="' + reg + '" nrs_cnrs="' + nrs + '" vnr_cvnr="' + vnr + '"><CODI>S</CODI><DESCRIPCIO>Si</DESCRIPCIO></value>';
	} else {
		stringXml = '<value reg_creg="' + reg + '" nrs_cnrs="' + nrs + '" vnr_cvnr="' + vnr + '"><CODI>N</CODI><DESCRIPCIO>No</DESCRIPCIO></value>';
	}
	eval(input + " = stringXml;");
}

function valida_mandatory() {

    var retorna = true;
    var missatge = "";
    var clausActual = g.getClaus();
    for (var j=0; j<clausActual.length; j++) {
        occactual = '';
        
        var obj = g.getElementById(clausActual[j]);
        if(obj.type=="text") {
            if(obj.id.substr(0,15) == "form:MANDATORY_") {
                var id=obj.id.substr(15);
                if(obj.value=='S') {
                    if(g.getElementById('form:URL_'+id)) { // Es fitxer
                        if( (g.getElementById('form:INPUT_'+id).value == '' && g.getElementById('form:URL_'+id).value == '')
                        		|| (g.getElementById('form:INPUT_'+id).value != '' 
                        		&& g.getElementById('form:CHECK_'+id).checked && g.getElementById('form:URL_'+id).value == '') ) {
                            missatge += g.getElementById('form:LABEL_'+id).innerHTML + "\n";
                            retorna = false;
                        }
                    } else { 	// NO Es fitxer
                        if(g.getElementById('form:INPUT_'+id).value == '') {
                            missatge += g.getElementById('form:LABEL_'+id).innerHTML + "\n";
                            retorna = false;
                        }
                    }
                }
            }
        }
    }
    if( missatge != "") {
        alert("Els següents camps son obligatoris:\n"+missatge);
        deleteNavigationPopUp();
    }
    return retorna;
}

function valida_casella_seleccio() {
	
	var retorn = '';
	var occactual = '';
	var valors = '';
	var idVarActual = '';
	var tipusVarActual = '';
	var objActual = '';
	var nomVar = '';
	var clausActual = g.getClaus();
	for (var j=0; j<clausActual.length; j++) {
		var obj = g.getElementById(clausActual[j]);
		occactual = '';
		tipusVarActual = '';
		idVarActual = '';
		
		if(obj.id.indexOf("form:DATATYPE_") != -1) {
			idVarActual = obj.id.substr(14);
			tipusVarActual = (obj.value).substr(0, obj.value.indexOf(' ') ) ;
		} else {
			idVarActual = '';
			tipusVarActual = '';
		}
		
		if(g.getElementById('form:INPUT_'+idVarActual))  {
			objActual = g.getElementById('form:INPUT_'+idVarActual);
		} else {
			objActual = '';
			tipusVarActual = '';
		}

		if(tipusVarActual == "VARCHAR2" )  {
		    if(g.getElementById('form:LABEL_'+idVarActual) != null) {
			nomVar = g.getElementById('form:LABEL_'+idVarActual).innerHTML;
			if(g.getElementById('form:INPUT2_'+idVarActual) &&
				g.getElementById('form:IMAGE2_'+idVarActual) ) {	// Autoselect
				if(g.getElementById('form:INPUT_'+idVarActual).value != '' 
					&& (g.getElementById('form:INPUT2_'+idVarActual).innerHTML=='' 
							|| g.getElementById('form:INPUT2_'+idVarActual).innerHTML=='Sense determinar' )  ) {
				    retorn += "Variable " + nomVar + " sense descripció\n";
					}
				}
			}
		}
	}
	return retorn;
}



function valida_format() {
    
	var retorna = true;
	var nomVariable = "";
	var clausActual = g.getClaus();
	for (var j=0; j<clausActual.length; j++) {
		var obj = g.getElementById(clausActual[j]);
	    occactual = '';
		if(obj.type=="hidden") {
            if(obj.id.substr(0,14) == "form:DATATYPE_") {
            	
                var id=obj.id.substr(14);
                
                var valor = g.getElementById('form:INPUT_' +id).value;
                if(g.getElementById('form:LABEL_' +id)) {
                	nomVariable = g.getElementById('form:LABEL_' +id).innerHTML;
                }
                else {
                	nomVariable = '';
                }
                
			  	if(valor != '') {
			  	    var datatype = obj.value.split(" ");
			  	    retorna = validaEntrada(valor, nomVariable, obj.value);
			  	    if(retorna != '') {
			  	        return retorna;
                    }
                }
            }
        }
    }
    return retorna;
}


function valida() {

	var valor = '';
	
	valor = valida_format();
    if( valor != '' && valor !=true) {
    	alert(valor);
    	deleteNavigationPopUp();
        return false;
    }
    
    if( valida_mandatory() != true) {
        return false;
    }
    
    valor = valida_casella_seleccio();
    
    if( valor != "" && valor !=true) {
    	alert(valor);
    	deleteNavigationPopUp();
    	return false;
    }
    
    valor = validacio_variables();
    
    if( valor != "" && valor !=true) {
    	alert(valor);
        deleteNavigationPopUp();
        return false;
    }
    
    valor = validacio_totes_formules_validacio_nivell();
    
    if( valor != "" && valor !=true) {
    	alert(valor);
        deleteNavigationPopUp();
        return false;
    }
    
    valorsCarregatsXml = concatValorsXml();
    g.getElementById("form:valorsAtributs").value = valorsCarregatsXml;
  
    return true;
}

function activateFile(identificador) { 
    if(g.getElementById('form:CHECK_'+identificador).checked) 
        g.getElementById('form:URL_'+identificador).disabled=false; 
    else {
    	g.getElementById('form:URL_'+identificador).value=''; 
        g.getElementById('form:URL_'+identificador).disabled=true;
    }
 }

function openLink(identificador) {
    if(g.getElementById('form:INPUT_'+identificador).value != '') {
        window.open(g.getElementById('form:INPUT_'+identificador).value);
    }
    
    return false;
}

function changeLink(identificador) {
    g.getElementById('form:LINK_'+identificador).href=g.getElementById('form:INPUT_'+identificador).value;
}

//Funcio equivalent a modalWin, pero sense fer submit formulari, i evitar 2 cerques a la pantalla del catàleg
function clickPopup(form) {
	var windowName  = g.getElementById(form+":idVista").value;
	leftVal = (screen.width - 800) / 2;
    topVal = (screen.height - 600) / 2; 
    var atributs = 'height=600,width=800,top=' + topVal + ',left=' + leftVal + 'toolbar=no,directories=no,status=no,bar=yes,scrollbars=yes,resizable=yes';
    valorRetorn=window.open('', windowName, atributs);

	g.getElementById('formPopUp:igual').onclick();
}

function modalWin(form) {
	hform=document.forms[form]; // reference to the hidden form
	clickPopup(form);
	g.getElementById( form + ':igual').onclick();
    // Submit the hidden form. The output will be sent to the just opened window.
    hform.submit();
}

function modalWinPrefilter(action, form, target, identificador) {    
	
    leftVal = (screen.width - 800) / 2;
    topVal = (screen.height - 600) / 2; 
    valorRetorn=window.open('about:blank','popup','height=600,width=800,top=' + topVal + ',left=' + leftVal + 'toolbar=no,directories=no,status=no,bar=yes,scrollbars=yes,resizable=yes');
}


function canviDocument(identificador) {
    
    if(g.getElementById('form:INPUT_'+identificador).value=='') { 
        g.getElementById('form:DIV_CHECK_'+identificador).className='DivOculto';
        g.getElementById('form:URL_'+identificador).disabled=false;
    } else {
        g.getElementById('form:DIV_CHECK_'+identificador).className='';
        g.getElementById('form:URL_'+identificador).disabled=true;
    }
}  
   

function selectFile(ident) {

	g.getElementById('form:LINK_'+ident).target="";
    g.getElementById('form:selectedFile').value = g.getElementById('form:INPUT_'+ident).value;
}

function selectHelpFile(idFile) {
    g.getElementById('form:selectedFile').value = idFile;
}

         
function selectDomainCommon(formulari, code, identCode, identDescription, condition) {
	var atribut = '';
	var ident = identCode.substr(6);
	try {
		eval("atribut=ATTR_"+ident);
	} catch(e) {
		atribut = '';
	}
	var valor = g.getElementById('form:'+identCode).value;
	var modificabilitatPopUp = g.getElementById('formPopUp:HIDDEN_INPUT_MODIFICABLE');
	var modificabilitatVar   = g.getElementById('form:HIDDEN_INPUT_MODIFICABLE_'+ident);
	if(modificabilitatPopUp != null  && modificabilitatVar != null) {
		modificabilitatPopUp.value = g.getElementById('form:HIDDEN_INPUT_MODIFICABLE_'+ident).value;
	}
	if(atribut.indexOf("ASS_CIP") != -1) {
		valor = valorXpath(stringToXml(atribut), '//ASS_CIP/text()');
	}
	g.getElementById(formulari+':selectedDomain').value = code + '#' + identCode + '#' + identDescription;
	g.getElementById(formulari+':selectedString').value = g.getElementById('form:'+identCode).value;
	var selCond = g.getElementById(formulari+':selectedCondition');
	if(selCond) {
		var cond = g.getElementById('form:'+condition);
		if(cond) {
			var valorCond = cond.value;
			selCond.value = valorCond;
		} else {
			selCond.value = '';
		}
	}
}

function selectDomain(code, identCode, identDescription, condition) {
	selectDomainCommon('formPopUp', code, identCode, identDescription, condition);
}

function selectDomainPrefiltre(code, identCode, identDescription, condition) {
	selectDomainCommon('form', code, identCode, identDescription, condition);
}


function deshabilita_tot() {

	var valors = '';
	var idVarActual = '';
	var tipusVarActual = '';
	var objActual = '';

	var formularis = document.forms;
	
	for (var i=0; i<formularis.length; i++) {
		var components = formularis[i].elements;

		for (var j=0; j<components.length; j++) {
			tipusVarActual = '';
			idVarActual = '';

			var obj = formularis[i].elements[j];
			
			if(obj.id.indexOf("form:DATATYPE_") != -1) {
				idVarActual = obj.id.substr(14);
				tipusVarActual = (obj.value).substr(0, obj.value.indexOf(' ') ) ;
			} else {
				idVarActual = '';
				tipusVarActual = '';
			}
			
			if(g.getElementById('form:INPUT_'+idVarActual))  {
				objActual = g.getElementById('form:INPUT_'+idVarActual);
			} else {
				objActual = '';
				tipusVarActual = '';
			}

			if(tipusVarActual == "DOCUMENT") {
				g.getElementById('form:CHECK_' + idVarActual).disabled=true;
				modificabilitat(idVarActual,'FALSE', false);				
			} else if (tipusVarActual == "LINK") {
				//No hacer nada un link no se puede modificar ni hay que aplicarle estilo
			} else if (tipusVarActual == "DATE") {				
				modificabilitat(idVarActual,'FALSE', false);
				g.getElementById('form:IMAGE_' + idVarActual).disabled=true;
				g.getElementById('form:INPUT_' + idVarActual).readOnly=true;
			} else if (tipusVarActual == "MEMO") {
				modificabilitat(idVarActual,'FALSE', false);
			} else if(tipusVarActual == "VARCHAR2" || tipusVarActual == "NUMBER" || tipusVarActual == "BOOLEAN")  {
				
				if(g.getElementById('form:INPUT2_'+idVarActual) ) {	// Autoselect
					var in1=g.getElementById('form:INPUT_' + idVarActual);
					
					modificabilitat(idVarActual,'FALSE', false);

					var in2=g.getElementById('form:INPUT2_' + idVarActual);
					if(in2) in2.disabled=true;
					var im1=g.getElementById('form:IMAGE_' + idVarActual);
					if(im1) {
						im1.href="#";
					}
					var im2=g.getElementById('form:IMAGE2_' + idVarActual);

				} else {
					//si es select un combo
					modificabilitat(idVarActual,'FALSE', false);
					doSelectNotModificable(idVarActual)
				}
			} 
		}
	}
}
/**Test if the component is a dropdown If the component not exist ==> false
 */
function isDropDown(target){
	try{
		return (g.getElementById('form:INPUT_' + target).options != null)
	}
	catch(e){
		return false;
	}
}

/**Hacer que un componente select sea no modificable
 * 
 */
function doSelectNotModificable(target){
	
  if(isDropDown(target)) {
	  var obj1 = g.getElementById('form:SPAN_COMPONENT_P1'+target);
	  var obj2 = g.getElementById('form:SPAN_COMPONENT_P2'+target);

	  if(obj1.style.display == 'none') {
		  obj1.style.display = 'none';
		  obj2.style.display = 'inline';
	  } else {
		  obj1.style.display = 'inline';
		  obj2.style.display = 'none';
	  }
  }
}

/** Copia el elemento seleecionado del combo en un componente HTML al que se le 
 * pueda hacer un componente.value=blablabla
 *
 **/ 
function copyDataFromSelectToText(id, idDestino){

  var componenteOrigen = g.getElementById(id);
  var componenteDestino = g.getElementById(idDestino);

  var encontrado = false;
  var i = 0;
      
  while( (i < componenteOrigen.length) && !encontrado){

    if(componenteOrigen.options[i].selected){
      encontrado = false;            
      componenteDestino.value = componenteOrigen.options[i].text;
      resizeInput(componenteDestino);
    }
    i++;
  }
}

/**Dado un campo de tipo input se le pone el tam?ano en funci?n del contenido
 * 
 */
function resizeInput(componente){
	
	var texto = componente.value;	
	componente.size = texto.length+3;
}

function validaAndDiv() {
	var validaOk = valida();
	if (validaOk) {
		document.body.scroll='no';
		var elems = document.forms['form'].elements;
		for (var i=elems.length ; i>=0; i--) {
			if (elems[i]) {
				if (elems[i].type=='select-one')
					elems[i].style.visibility='hidden';
			}
		}
	}
	return validaOk;
}

function doNothing() {}


function checkOnclick(identificador) {
    if(g.getElementById('form:INPUT2_'+identificador).checked) {
        g.getElementById('form:INPUT_'+identificador).value="S";
    } else {
        g.getElementById('form:INPUT_'+identificador).value="N";
    }
    g.getElementById('form:INPUT_'+identificador).onchange();
}

function changeCheck(identificador) {
    
}


/**
 * Carrega pantalla desde la variable  valorsCarregatsXml que conte XML de la ocurrencia
 */
function carregaValorsOccurrencia() {
	showOverlayDiv();

	var occ="";
	
	var retorna = "";
	var recarregaCondicio = false;
	
	if((g.getElementById("form:errorMsg") && g.getElementById("form:errorMsg").innerHTML != '') 
		|| g.getElementById("form:nextAction").value == 'removeChildOccurrence' ) {	// Cas d'haver-hi esborrat una ocurrència filla
		occ = g.getElementById('form:valorsAtributs').value.split('|#|');
		recarregaCondicio = true;
		if(g.getElementById("form:hiddenDadaCanviada").value=='true') {
			changeValue();
		}
	} else {
		occ = valorsCarregatsXml.split('|#|');
		recarregaCondicio = false;
	} 
	
	estatCarregant = true;
	try {
		for(var i=0; i<occ.length; i++) {
			var dades = occ[i].split('@|@');
			var valors1 = dades[0];
			var valors2 = dades[1];
			var descDocument = dades[2];
			var esObligatoria = dades[3];
			var esVisible = dades[4];
			var esModificable = dades[5];
			var esColor = dades[6];
			var esPlegat = dades[7];
			var esEstil = dades[8];
			var condition = unescape(dades[9]);
			var visor = dades[10];
			var navDomini = dades[11];
			var valors3 = dades[12];
			
			var ident = valors1.split(':')[0];
			var codi = valors1.split(':')[1];
			if(g.getElementById("form:HIDDEN_NIA_OCULT_" + ident) && codi!=''){
                g.getElementById("form:HIDDEN_NIA_OCULT_" + ident).value = codi;
                var codi = '***';
            }
			var valor = valors2;

	        var aux = null;
	
			if( (g.getElementById("form:COMPONENTTYPEREQ_"+ident)) && (occ[i].indexOf("$REQ$") != -1 )) {
				visibilitatRequadre(ident, esVisible);
				colorRequadre(ident, esColor);
				modificabilitatRequadre(ident, esModificable);
				plegatRequadre(ident, esPlegat);
			} else if( (g.getElementById("form:COMPONENTTYPE_"+ident)) &&  (occ[i].indexOf("$REQ$") == -1 ) ) {
				visibilitat(ident, esVisible);
				navegaDomini(ident, navDomini);
	
		        try {
					eval("ATTR_"+ident+"=valors3;");
		        } catch(e) {
		        	alert('Falla ATTR_'+ident+'='+valor3);
		        	deleteNavigationPopUp();
		        }
		        
		        estil(ident, esEstil);
				color(ident, esColor);
				obligatorietat(ident, esObligatoria);
				carrega(ident, codi, valor,condition, recarregaCondicio);							
				visorhcc(ident, visor);
				
				//canviar modificabilitat de la variable si esta a cache
				var prefix = 'form:INPUT_';
				if(g.getElementById("form:COMPONENTTYPE_"+ident).value=='BOOLEAN') prefix = 'form:INPUT2_';
				g.getElementById(prefix+ident+'_MOD').value = (esModificable=='TRUE'?'S':'N');
				
				modificabilitat(ident, esModificable, true);
			}
		}
	}
	catch(e) { }
	
	estatCarregant = false;

	//esto es una chapuza, ver la funcion para mas detalles
	selectMandatoryOnchanges();
	
	// Aquesta funció carrega els valors preinformats de les variables que en tinguin.
	carregaValorsPreinformats();
	
	hideOverlayDiv();
}

/**
 * Reescriu els valors de valorsCarregatsXml amb els components de pantalla
 */
function concatValorsXml() {
	var retorn = "";
	var ident = "";
	var formularis = document.forms;
	var retornTotal = "";
	var clausActual = g.getClaus();
	for (var j=0; j<clausActual.length; j++) {
		var obj = g.getElementById(clausActual[j]);
		if(obj.id.indexOf("form:COMPONENTTYPE_") != -1) {
			ident = obj.id.substr(19);
			var objTarget = g.getElementById("form:COMPONENTTYPE_"+ident);
			retorn += recuperaValorsXml(ident);
		} else {
			if (obj.id.indexOf("form:COMPONENTTYPEREQ_") != -1) {
				ident = obj.id.substr(22);
				var objTarget = g.getElementById("form:COMPONENTTYPEREQ_"+ident);
				retornTotal += recuperaValorsXmlRequadre(ident);
			}
		}
	}
	retornTotal += retorn; // Per tornar en ordre els requadres i les variables.
	
	var reg_creg=g.getElementById("form:h_registerid");
    var nrs_cnrs=g.getElementById("form:h_levelid");
    var orn_corn="null";
    var orn_corn_arrel="null";
    
    if(g.getElementById("form:h_occurrence")) {
    	orn_corn=g.getElementById("form:h_occurrence").value;
    }
    
    if(g.getElementById("form:h_parentoccurrence")) {
    	orn_corn_arrel=g.getElementById("form:h_parentoccurrence").value;
    }
    
	return retornTotal;
}

function ValueActual(ident) {
	var resultat = '';
	var valors = ident.split("_");
	var varId = valors[1] + "_" + valors[2] + "_" + valors[3];
	var objComponent = g.getElementById("form:COMPONENTTYPE_" + varId);
	if(objComponent) { // Variable del nivell actual
		var obj = g.getElementById("form:INPUT_" + varId);
		if(objComponent == "SELECT") {
			resultat = obj.options[obj.selectedIndex].value;
		} else {
			resultat = obj.value;
		}
	}
	return resultat;
}

function AtributVariable(ident, atribut) {
	var attrXml = 'ATTR_' + ident;
	var attrValue = '';
	eval('attrValue = ' + attrXml);
	var doc = stringToXml(attrValue);
	var resultat = valorXpath(doc, '//' + atribut + '/text()'); 
	return resultat;
}

/**
* Validacion de rangos retorna un booleano que indica si se han pasado las validaciones o no y en función de 
* showAlert se muestra un alert o no. Dicho alert si se muestra indica un NAME_VAR: El valor X no se 
* encuentra entre los rangos [@param:desde,@param:hasta]
* @param idcomponent: 
* @param desde: rango desde sino está ==> no validar desde
* @param hasta: rango hasta, sino está ==> no validar hasta
* @param showAlert: show alert????
*/
function validateRank(idComponent, desde, hasta, showAlert ) {
	if(debug)
		alert('validateRank('+idComponent+', '+desde+', '+hasta+', '+showAlert +')');
		
  	//idComponent == REG_LEV_VAR
  	var idSpanComponent = 'form:LABEL_'+idComponent;
  	idComponent ='form:INPUT_'+idComponent;
  	
	var comp = g.getElementById(idComponent);//comp es el campo text que tiene el valor del number

	var actualValue = comp.value;
	var error = false;
	var errorMsg = '';
	
	var intro = '';//var que tendrá el nombre de la var numerica
	if(showAlert)
		intro = g.getElementById(idSpanComponent).innerHTML;

	if(actualValue!='') {//validaciones rangos
		if(!isNaN(actualValue)) {
			if(desde !=null && hasta != null) {
				if(desde > actualValue || actualValue > hasta) {
					error = true;
					errorMsg = intro+'El valor '+actualValue+' ha de trobar-se entre els rangs ['+desde+','+hasta+']'+cr;
				}
			}
			else {//o desde o hasta no están
				if(desde==null && hasta!=null) {//val hasta
					if(actualValue > hasta) {
						errorMsg = intro+'El valor '+actualValue+' ha de ser menor o igual que '+hasta+cr;
						error = true;
					}
				}
				if(hasta==null && desde!=null) {//val desde
					if(desde > actualValue) {
						errorMsg = intro+'El valor '+actualValue+' ha de ser mes gran o igual que '+desde+cr;
						error = true;
					}
				}
			}
			if(showAlert && error) {
				alert(errorMsg);
				deleteNavigationPopUp();
			}
		}//if(!isNan(actualValue))
	}//fif(actualValue!='')
	return errorMsg; 
}

function controlSizeMemoType(idComponent) {
    /*var comp = document.getElementById("form:INPUT_"+idComponent);
    var actualValue = comp.value;
    
    if(actualValue!='') {
        comp.value = actualValue.substring(0, 3998);
    }*/
}

function doConfirmValidaIDesa() {
	g.getElementById('popUp').style.visibility='hidden';
	var next = g.getElementById("form:nextAction").value;
	var sact = g.getElementById("form:saveActual").value;
	//sact = "Save";
	if(sact == 'Save' || next == 'browseQuery') {
		if(validaAndDiv()) {
			showOverlayDiv(g.getElementById('form:popUpActionMessage').value);
			return true;
		} 
	} else if(sact == 'NoSave' || next == 'removeChildOccurrence') {
		showOverlayDiv(g.getElementById('form:popUpActionMessage').value);
		return true;
	}
	hideOverlayDivWithNoPopUp('form:overlayDiv');
	return false;
}		


function doConfirmValidaINoDesa() {
	var next = g.getElementById("form:nextAction").value;
	var sact = g.getElementById("form:saveActual").value;
	//sact = "NoSave";
	if(next == 'addChildOccurrence' || next == 'addDomOccurrence' || next == 'editChildOccurrence' || next == 'editDomOccurrence' || next == 'viewChildOccurrence' || next == 'viewDomOccurrence' || next == 'browseQuery') {
		//Codi de valida necessari en el cas  que s'intenti donar d'alta una occurrencia filla sense desar 
		valorsCarregatsXml = concatValorsXml();
		g.getElementById("form:valorsAtributs").value = valorsCarregatsXml;
		
		g.getElementById("form:popUpActionMessage").value="Carregant...";
		
		g.getElementById('popUp').style.visibility='hidden';
		showOverlayDiv(g.getElementById('form:popUpActionMessage').value);
		return true;
	} else if(next == 'removeChildOccurrence') {
		valorsCarregatsXml = concatValorsXml();
		g.getElementById("form:valorsAtributs").value = valorsCarregatsXml;
		
		g.getElementById("form:popUpActionMessage").value="Esborrant...";
		if(sact == 'Save') {
			g.getElementById("form:saveActual").value='NoSave';	// El boto de No no ha de desar
			showOverlayDiv(g.getElementById('form:popUpActionMessage').value);
			return true;
		} else {
			doPopUp();
			hideOverlayDivWithNoPopUp('form:overlayDiv');
			return true;
		}
	}
	hideOverlayDivWithNoPopUp('form:overlayDiv');
	return false;
}	

function doCancel() {
	g.getElementById("form:h_nextregisterid").value="";
	g.getElementById("form:h_nextplevelid").value="";
	g.getElementById("form:h_nextlevelid").value="";
	g.getElementById("form:h_nextparentoccurrence").value="";
	g.getElementById("form:h_nextoccurrence").value="";
	doPopUp();
	hideOverlayDivWithNoPopUp('form:overlayDiv');
	return true;
}

function copyCurrentValuesForDeleteChild() {
    valorsCarregatsXml = concatValorsXml();
    g.getElementById("form:valorsAtributs").value = valorsCarregatsXml;
}

function openVisor(identificador) {
	var visorCipVar = g.getElementById("form:VISORHCC_CIP_" + identificador).value;
	var visorNiaVar = g.getElementById("form:VISORHCC_NIA_" + identificador).value;
	var visorCip = g.getElementById("form:VISORHCC_CIP");
	var visorNia = g.getElementById("form:VISORHCC_NIA");
	
	if(visorCip != null && visorNia != null ) {
		visorCip.value = visorCipVar;
		visorNia.value = visorNiaVar;
		var selectors = visorCipVar + '#' + visorNiaVar;
		
		var myAjaxObj= new VisorHcccAjax();
		myAjaxObj.prepare(url, method, mode);
		myAjaxObj.setForm("form");
		myAjaxObj.directCall("VisorHcccAjax", selectors);
	}

	return false;
}

function ocultDiv() {
    var div = g.getElementById("form:popUpAjuda");
    div.style.visibility="hidden";
    div.style.display="none";
    var divOcultar = g.getElementById("form:popUpAjudaOcultar");
    divOcultar.style.visibility="hidden";
    divOcultar.style.display="none";
}

function showContextualHelp(widthVar, heightVar, titleVar, identificador) {
    
    var div = g.getElementById("form:popUpAjuda");
    var divOcultar = g.getElementById("form:popUpAjudaOcultar");
    if(div.style.visibility=="hidden") {
        div.style.visibility="visible";
        div.style.display="block";
        divOcultar.style.visibility="visible";
        divOcultar.style.display="block";
    }/* else {
        div.style.visibility="hidden";
        div.style.display="none";
        divOcultar.style.visibility="hidden";
        divOcultar.style.display="none";
    }*/
    set_attrs_to_div(widthVar, heightVar, titleVar, identificador);
}

function set_attrs_to_div(widthVar, heightVar, titleVar, identificador) {
    //setejar message
    var message = g.getElementById("form:popUpAjudaMessage");
    var textAreaHelp = g.getElementById("form:HIDDEN_HELP_" + identificador);
    message.innerHTML = textAreaHelp.value;
    //setejar title
    var title = g.getElementById("form:popUpAjudaTitle");
    title.innerHTML=titleVar;
    //setejar width i height
    var div = g.getElementById("form:popUpAjuda");
    if(widthVar!='' && widthVar != null) {
        div.style.width=widthVar+"px";
    } else {
        div.style.width="300px";
    }
    if(heightVar!='' && heightVar != null) {
        div.style.height=heightVar+"px";
    } else {
        div.style.height="200px";
    }
    //situar el div sota el boto
    var obj = g.getElementById("form:IMAGE_HELP_" + identificador);
    var xy = getXY(obj);
    var left = xy['x']+obj.offsetWidth-div.offsetWidth;
    if(left < 0)  {
    	left = 0;
    }
    div.style.left=left+'px';
    div.style.top=xy['y']+'px';
    
    var divOcultar = g.getElementById("form:popUpAjudaOcultar");
    
    //solucionar overlapping explorer 6.0
    if (document.all) {
        divOcultar.innerHTML='<IFRAME src="javascript:false;" frameBorder="0" scrolling="no" id="iframe_hvrShm"/>';
        var iframeShim = document.getElementById("iframe_hvrShm");
        divOcultar.style.top = div.style.top;
        divOcultar.style.left = div.style.left;
        divOcultar.style.width = div.offsetWidth;
        divOcultar.style.height = div.offsetHeight;
        iframeShim.style.width = div.offsetWidth;
        iframeShim.style.height = div.offsetHeight;
    }
}

function replaceAll( text, busca, reemplaza ){
    while (text.toString().indexOf(busca) != -1){
        text = text.toString().replace(busca,reemplaza);
    }
    return text;
}

function getXY(obj) {
  var curleft = 0;
  var curtop = obj.height+1;
  if (obj.offsetParent) {
    do {
      curleft += obj.offsetLeft;
      curtop += obj.offsetTop;
    } while (obj = obj.offsetParent)
  } else if (obj.x) {
    curleft += obj.x;
    curtop += obj.y;
  }
  return {'x': curleft, 'y': curtop};
}

// Funció que es crida des de l'onmousedown del boto desar, que evita navegacions erronies quan s'interactua amb nivells fills.
function eliminaNextAction() {
	g.getElementById("form:nextAction").value="";
}
function nouValorDomini(idDomain, targetValue, idFormula) {
	g.getElementById('form:selectedDomainQuery').value = idDomain;
	g.getElementById('form:selectedDomainQueryValue').value = g.getElementById('form:'+targetValue).value;
	
	var myAjaxObj= new AjaxMessagesPopUp();
	var async = false;
	myAjaxObj.prepare(url, method, async);
	myAjaxObj.setForm("form");	
	
	var res = myAjaxObj.directCall(	'NEW',
									idDomain,
									'', 
									g.getElementById('form:h_currentuser').value, 
									g.getElementById('form:h_currentprofile').value, 
									g.getElementById('form:h_currentapplication').value);
	
	return myAjaxObj._returnResponse;
}

function editarValorDomini(idDomain, targetValue, idFormula) {
	g.getElementById('form:selectedDomainQuery').value = idDomain;
	if(g.getElementById('form:'+targetValue).value == null || g.getElementById('form:'+targetValue).value =="") {
		alert('Es requereix seleccionar prèviament un valor');
		return false;
	}
	g.getElementById('form:selectedDomainQueryValue').value = g.getElementById('form:'+targetValue).value;

	var myAjaxObj= new AjaxMessagesPopUp();
	var async = false;
	myAjaxObj.prepare(url, method, async);
	myAjaxObj.setForm("form");	
	
	var res = myAjaxObj.directCall(	'EDIT',
									idDomain,
									g.getElementById('form:'+targetValue).value, 
									g.getElementById('form:h_currentuser').value, 
									g.getElementById('form:h_currentprofile').value, 
									g.getElementById('form:h_currentapplication').value);
	return myAjaxObj._returnResponse;
}

function esAlta() {
	if(g.getElementById("form:h_occurrence")) {
		return (g.getElementById("form:h_occurrence").value == '');
	}
	return true;
}

function addDomOccurrence() {
	nextOcurrence('addDomOccurrence');
}

function editDomOccurrence() {
	nextOcurrence('editDomOccurrence');
}

function nextOcurrence(tipus) {
	var missatge = "Voleu desar els canvis a l'ocurrència actual abans de continuar?<br/><br/>Premi ";

	if(esAlta()) {
		g.getElementById("form:popUpConfirm").value="Confirmar";
		g.getElementById("form:popUpCancel").className='hidden';
		g.getElementById("form:popUpNothing").className="botonsText Btn2";
		
		if(tipus == 'addDomOccurrence')	missatge += "Confirmar per desar els canvis i editar la nova ocurrència<br/>";
		else							missatge += "Confirmar per desar els canvis i editar l'ocurrència associada.<br/>";
	} else {
		g.getElementById("form:popUpConfirm").value="Si";
		g.getElementById("form:popUpCancel").value="No";
		g.getElementById("form:popUpCancel").className="botonsText Btn2";
		g.getElementById("form:popUpNothing").className="botonsText Btn2";
		
		if(tipus == 'addDomOccurrence')	missatge += "Si per desar els canvis i editar la nova ocurrència associada<br/>Premi No per rebutjar els canvis i editar la nova ocurrèbncia associada.<br/>";
		else							missatge += "Si per desar els canvis i editar l'ocurrència associada      <br/>Premi No per rebutjar els canvis i editar l'ocurrència associada.<br/>";
	}
	missatge += "Premi Cancel·lar per tornar a la pantalla.<br/>";
 
	g.getElementById("form:popUpMessage").innerHTML=missatge;
	g.getElementById("popUp").style.width="420px";
	g.getElementById("form:popUpTitle").innerHTML="Desar abans de continuar?";
	g.getElementById("form:nextAction").value=tipus;
	
	if ( getChangeValue() ) {
		//acció d'editar una ocurrència filla sense desar la ocurrència pare
		g.getElementById("form:saveActual").value='Save';
		g.getElementById("form:overlayDiv").style.display = "block";
		g.getElementById("form:popUpActionMessage").value="Desant...";
		window.scroll(0,0);
		doPopUp();
	} else if(esAlta()){
		g.getElementById("form:saveActual").value='Save';
		g.getElementById("form:overlayDiv").style.display = "block";
		g.getElementById("form:popUpActionMessage").value="Carregant...";
		window.scroll(0,0);
		doPopUp();
	} else {
		g.getElementById("form:saveActual").value='NoSave';
		g.getElementById("form:popUpActionMessage").value="Carregant...";
		g.getElementById("form:overlayDiv").style.display = "block";
		g.getElementById("form:popUpConfirm").click();
	}
}
function go(i) {
	document.getElementById("form:idNav").value=i;
}

function validateMask(idComponent, mask, showAlert) {
   var valor = g.getElementById('form:INPUT_'+idComponent).value;       // Valor introduït
   var errorMsg = '';   
   if (valor!='') {
      var re = new RegExp('^'+mask+'$');
      if (!valor.match(re)) {
          var nomVar = g.getElementById('form:LABEL_'+idComponent).innerHTML;   // Nom de la variable 
      	 errorMsg = nomVar + 'Valor no corresponent amb la màscara '+mask;
      	 if (showAlert) { 
      	    alert (errorMsg);
      	 }
      }
  }
  return errorMsg;
}

//donat un desplegable select comprovem si nomes tenim una opcio i el desplegable es obligatori
//si es complei llavors seleccionem l'unica opcio i llancem onchange del component
function selectMandatory (target) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objTargetInput = g.getElementById("form:INPUT_SELECT_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
	var objTargetCond = g.getElementById("form:COND_" + target);
	
//	if(!esAlta()) return; //nomes es fa la validacio en cas de les altes
	
	if(objMand == null) return; //no es obligatori, ni per formula ni per configuracio
	
//	alert("objMand.value: "+objMand.value);
	if(objMand.value == "N") return; //no es obligatori en aquest moment
	
	//el desplegable es obligatori	
	//nomes tenim una opcio al desplegable
	if(objTarget.length == 2) {
		//no podem fer la validacio antibucles pq el valor del desplegable canvia encara que el selectedindex varii
//		if(objTarget.selectedIndex == 1 || (objTarget.type ==  "hidden")) return;    	
		objTarget.selectedIndex = 1; //seleccionem l'unica opcio que tenim
		//afegim el target a la llista per a executarlos en acabar la carrega de la pantalla
		if(estatCarregant && selectMandatoryTargets.indexOf(target)==-1) {
			selectMandatoryTargets += target+'|@|';
		}
		objTarget.onchange();		

	}	
}

//funcion chapuza para provocar los calcula en pantalla una vez se ha finalizado la carga
//mientras se carga la pantalla no funcionan los onchanges asi que nos los vamos guardando y los ejecutamos al final
//lo que se tendria que hacer seria ir al rsapkorn.obtenir_valors_occurrencia_xml y arreglarlo para que haga el calculo
//se tendria que tratar a las formulas de condicion como si fueran de calculo para que se hicieran en el orden correcto
//a causa de esta chapuza si hay una variable por defecto que depende de una de estas variables seguramente no se calcule
function selectMandatoryOnchanges() {
	var targets = selectMandatoryTargets.split('|@|');
	var target;
	var objTarget;
	
	for(var i=0; i<targets.length; i++) {
		target = targets[i];
		if(target != null && target != '') {
			objTarget = g.getElementById("form:INPUT_" + target);
//			alert("target: "+target);
			objTarget.onchange();
		}
	}
}

function carregaValorsPreinformats() {
    var hPreinfField = document.getElementById('form:h_PreinfField').value;
    
    var variables = hPreinfField.split("|@|");
    var variableActual;
    var clauValor;
    var clau;
    var valor;
    
	for(var i=0; i<variables.length; i++) {
	    variableActual = variables[i];
	    clauValor = variableActual.split("=");
	    clau = clauValor[0];
	    valor = clauValor[1];
	    
	    if (document.getElementById("form:INPUT_"+clau)){
	    	document.getElementById("form:INPUT_"+clau).value = valor.substr(0, valor.indexOf(':'));
	    }
    }
    
    for(var i=0; i<variables.length; i++) {
    	variableActual = variables[i];
	    clauValor = variableActual.split("=");
	    clau = clauValor[0];
	    
	    if (document.getElementById("form:INPUT_"+clau)){
	        if(typeof document.getElementById("form:INPUT_"+clau).onchange == "function"){ 
			    document.getElementById("form:INPUT_"+clau).onchange();
			}
	    }
    }
}

function accioBotNav(target, tipus, regId, levelId){
    document.getElementById("form:h_nextregisterid").value = regId;
    document.getElementById("form:h_nextlevelid").value = levelId;
    document.getElementById("form:h_nextplevelid").value = document.getElementById("form:h_levelid").value;
    document.getElementById("form:h_nextparentoccurrence").value = document.getElementById("form:h_occurrence").value;
    
    var botNavTarget = g.getElementById(target);
    document.getElementById("form:h_xmlField").value = botNavTarget.value;
    
    document.getElementById("form:popUpMessage").innerHTML="Voleu desar els canvis a l'ocurrència actual abans de continuar?<br/><br/>Premi Sí, per desar els canvis i navegar al resultat de la consulta.<br/>Premi No, per rebutjar els canvis i navegar al resultat de la consulta.<br/>Premi Cancel·lar, per tornar a la pantalla";
    document.getElementById("form:popUpConfirm").value="Sí";
    document.getElementById("form:popUpCancel").value="No";
    document.getElementById("popUp").style.width="420px";
    document.getElementById("form:popUpTitle").innerHTML="Desar abans de continuar?";
    document.getElementById("form:popUpNothing").className="botonsText Btn2";
    document.getElementById("form:nextAction").value=tipus;
    document.getElementById("form:popUpActionMessage").value="Carregant...";
    document.getElementById("form:overlayDiv").style.display = "block";
    
    var esAltaPare = (document.getElementById("form:h_occurrence").value == '');
    
    if (getChangeValue()) { // && !esAltaPare
        document.getElementById("form:saveActual").value='Save';
        document.getElementById("form:popUpActionMessage").value="Desant...";
        window.scroll(0,0);
        doPopUp();
    } else {
        if(esAltaPare) document.getElementById("form:saveActual").value="Save";
        else           document.getElementById("form:saveActual").value="NoSave";
        
        document.getElementById("form:popUpActionMessage").value="Carregant...";
        document.getElementById("form:popUpConfirm").click();
    }
}
