/**
* Formulas generales
*/
var debug = '';	// debug='1' per a mostrar respostes

function color(target, resposta) {
	if(resposta == "INI") return;
	if (resposta == "null") {
    	resposta = "black";
	}
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	if(tipus) {
		if(tipus.value == 'SELECT') 			colorSelect(target, resposta);
		else if(tipus.value == 'AUTOSELECT')	colorAutoSelect(target, resposta);
		else if(tipus.value == 'VARCHAR')		colorVarchar(target, resposta);
		else if(tipus.value == 'LINK')			colorLink(target, resposta);
		else if(tipus.value == 'DATE')			colorDate(target, resposta);
		else if(tipus.value == 'NUMBER')		colorNumber(target, resposta);
		else if(tipus.value == 'BOOLEAN')		colorBoolean(target, resposta);
		else if(tipus.value == 'DOCUMENT')		colorDocument(target, resposta);
		else if(tipus.value == 'TEXTAREA')		colorTextArea(target, resposta);
		else if(tipus.value == 'COMENTARI') 	colorComentari(target, resposta);
		else if(tipus.value == 'BOTO') 			colorBoto(target, resposta);
		else if(tipus.value == 'BOTNAV')        colorBotNav(target, resposta);
	} else {
		var tipus2 = g.getElementById("form:COMPONENTTYPEREQ_" + target);
		if(tipus2.value == 'REQUADRE') {
			colorRequadre(target, resposta);
		}
	}
}

function estil(target, resposta) {
	if(resposta == "INI") return;
	//si l'estil seleccionant no existeix a la metataula 1040 que esta carregada al javascript de la pagina posem l'estil per defecte
	if (metStyle[resposta] == undefined) {
    	resposta = null;
	}
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	if(tipus) {
		if(tipus.value == 'COMENTARI') {
			estilComentari(target, resposta);
		}
	}
}

function setStyleModificable(idComponent, isModificable){

	var component = g.getElementById(idComponent);
	if(idComponent==='form:INPUT_2227_37144_113477'){
		component= component;
	}

	if(isModificable){
		if(searchStyle(component.className, 'EDITNoModificableNoObligatori')){
			component.className = 'EDITModificableNoObligatori';
			component.onfocus = "";
		}

		if(searchStyle(component.className, 'EDITObligatoriNoModificable')){
			component.className = 'EDITObligatoriModificable';
			component.onfocus = "";
		}
	} else {
		if(searchStyle(component.className, 'EDITObligatoriModificable')){
			component.className = 'EDITObligatoriNoModificable';
		}

		if(searchStyle(component.className, 'EDITModificableNoObligatori')){
			component.className = 'EDITNoModificableNoObligatori';
		}
	}
}

function isModificableByStyle(component)
{
	var isModificable = true;
	//obtenemos la modificabilitat del estado de la variable y no del estado de la pantalla
	//el estado de la modificabilidad de la variable se rige por su propia modificabilidad
	//en pantalla puede venir dado por la modificabilidad del registro

	if(component.value == "S") {
		return true;
	} else {
		return false;
	}
}


//EDITObligatoriModificable
//EDITObligatoriNoModificable
//EDITModificableNoObligatori
//EDITNoModificableNoObligatori

function setStyleObligatori(idComponent, isObligatori){

	var component = g.getElementById(idComponent);

	if(isObligatori){
		if(searchStyle(component.className, 'EDITNoModificableNoObligatori')){
			component.className = 'EDITObligatoriNoModificable';
		}
		if(searchStyle(component.className, 'EDITModificableNoObligatori')){
			component.className = 'EDITObligatoriModificable';
		}
	}
	else{
		if(searchStyle(component.className, 'EDITObligatoriModificable')){
			component.className = 'EDITModificableNoObligatori';
		}
		if(searchStyle(component.className, 'EDITObligatoriNoModificable')){
			component.className = 'EDITNoModificableNoObligatori';
		}
	}
}


function searchStyle(data, styleSearched){
	info = data.split(" ");
	var contador = 0;
	var encontrado = false;

	while((contador < (info.length)) && !encontrado)
    {
    	if(info[contador]==styleSearched){
			encontrado = true;
		}
		contador++;
	}
	return encontrado
}

/* Formulas de color
 */
function colorSelect(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	obj1.style.color=resposta;
}

function colorAutoSelect(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	var obj3 = g.getElementById("form:IMAGE_"+ target);
	var obj4 = g.getElementById("form:IMAGE2_"+ target);
	var obj5 = g.getElementById("form:INPUT2_"+ target);
	obj1.style.color=resposta;
	obj3.style.color=resposta;
	obj4.style.color=resposta;
	obj5.style.color=resposta;
}

function colorVarchar(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	obj1.style.color=resposta;
}

function colorLink(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	var obj2 = g.getElementById("form:LINK_"+ target);
	obj1.style.color=resposta;
	obj2.style.color=resposta;
}

function colorDate(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	obj1.style.color=resposta;
}


function colorNumber(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	obj1.style.color=resposta;
}

function colorBoolean(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	var obj2 = g.getElementById("form:INPUT2_"+ target);
	obj1.style.color=resposta;
	obj2.style.color=resposta;
}

function colorDocument(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	var obj3 = g.getElementById("form:CHECK_"+ target);
	obj1.style.color=resposta;
	obj3.style.color=resposta;
}

function colorTextArea(target, resposta) {
	var obj1 = g.getElementById("form:LABEL_"+ target);
	obj1.style.color=resposta;
}

function colorComentari(target, resposta) {
	var obj1 = g.getElementById("form:INPUT_COMPONENT_"+ target);
	obj1.style.color=resposta;
	obj1 = g.getElementById("form:INPUT_COMPONENT2_"+ target);
	obj1.style.color=resposta;
}

function colorBoto(target, resposta) {
	var obj1 = g.getElementById("form:BUTTON_"+ target);
	obj1.style.backgroundColor=resposta;
}

function colorBotNav(target, resposta) {
    var obj1 = g.getElementById("form:INPUT_"+ target);
    obj1.style.backgroundColor=resposta;
}

function estilComentari(target, resposta) {
	var obj1 = g.getElementById("form:INPUT_COMPONENT_"+ target);
	var obj2 = g.getElementById("form:INPUT_COMPONENT2_"+ target);
	if(resposta == null) {
		obj1.className='TAMessageVariable TxtAra';
		obj2.className='TAMessageVariable TxtAra';
	} else {
		//aixo es fa per a que la variable missatge agafi tot l'ample de la pantalla d'edicio d'ocurrencies
		obj1.className='TAMessageVariable TxtAra '+resposta;
		obj2.className='TAMessageVariable TxtAra '+resposta;		
	}	
}

function colorRequadre(target, resposta) {
	if (resposta == "INI") return;
	var obj1 = g.getElementById("form:REQ_" + target );
	var obj2 = g.getElementById("form:REQ_" + target + "_TITLE");
	obj2.style.color=resposta;
	obj1.style.borderColor=resposta;
}

// formules modificabilitat

function modificabilitat(target, resposta, isCarregaInicial) {
	//isCarregaInicial ens indica si estem mirant la modificabilitat desde la formula d'un requadre (true) o si
	//es modificabilitat propia de la formula de la variable (false)
	//quan esta a false es seteja al hiddn _mod de la variable el nou estat indicant per resposta
	if(resposta == "INI") return;
	if(resposta == null || resposta == '' || resposta == 'null') resposta = "TRUE";
	if(isCarregaInicial == null || resposta == '' || resposta == 'null') isCarregaInicial = false;

	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);

	var idreq;
	var modificareq;

	if(tipus) {
		if(tipus.value == 'SELECT')				modificabilitatSelect(target, resposta, isCarregaInicial);
		else if(tipus.value == 'AUTOSELECT')	modificabilitatAutoSelect(target, resposta, isCarregaInicial);
		else if(tipus.value == 'VARCHAR')		modificabilitatVarchar(target, resposta, isCarregaInicial);
		else if(tipus.value == 'LINK')			modificabilitatLink(target, resposta, isCarregaInicial);
		else if(tipus.value == 'DATE')			modificabilitatDate(target, resposta, isCarregaInicial);
		else if(tipus.value == 'NUMBER')		modificabilitatNumber(target, resposta, isCarregaInicial);
		else if(tipus.value == 'BOOLEAN')		modificabilitatBoolean(target, resposta, isCarregaInicial);
		else if(tipus.value == 'DOCUMENT')		modificabilitatDocument(target, resposta, isCarregaInicial);
		else if(tipus.value == 'TEXTAREA')		modificabilitatTextArea(target, resposta, isCarregaInicial);
		else if(tipus.value == 'BOTO'    )  	modificabilitatBoto(target, resposta, isCarregaInicial);
		else if(tipus.value == 'BOTNAV'    )    modificabilitatBotNav(target, resposta, isCarregaInicial);
		
	} else {
		var tipus2 = g.getElementById("form:COMPONENTTYPEREQ_" + target);
		if(tipus2.value == 'REQUADRE') {
			modificabilitatRequadre(target, resposta);
		}
	}
}

function modificabilitatSelect(target, resposta, isCarregaInicial) {

	var obj1 = g.getElementById("form:INPUT_" + target);//campo select
	var obj2 = g.getElementById("form:INPUT_SELECT_" + target);//campo texto
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
		cambiarVisibilidadSelect('form:SPAN_COMPONENT_P2'+target, 'form:SPAN_COMPONENT_P1'+target);
		setStyleModificable('form:INPUT_'+target, true);
		setStyleModificable('form:INPUT_SELECT_'+target, true);
	} else {
    	cambiarVisibilidadSelect('form:SPAN_COMPONENT_P1'+target, 'form:SPAN_COMPONENT_P2'+target);
    	setStyleModificable('form:INPUT_SELECT_'+target, false);
    	setStyleModificable('form:INPUT_'+target, false);
        obj2.readOnly=true;
    }
}

function cambiarVisibilidadSelect(idOcultar, idVisible)
{
  var ocultar = g.getElementById(idOcultar);
  var visible = g.getElementById(idVisible);

  ocultar.style.display = 'none';
  visible.style.display = 'inline';
}

function modificabilitatAutoSelect(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:INPUT_" + target);
	//var obj2 = g.getElementById("form:IMAGE_" + target);
	var obj3 = g.getElementById("form:IMAGE2_" + target);
	var modif = g.getElementById("form:HIDDEN_INPUT_MODIFICABLE_" + target);
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
        setStyleModificable('form:INPUT_'+target, true);
        obj1.readOnly=false;
        modif.value = 'modificable';
    } else {
    	setStyleModificable('form:INPUT_'+target, false);
        obj1.readOnly=true;
    	modif.value = 'nomodificable';
    }
}

function modificabilitatVarchar(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:INPUT_" + target);
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
		setStyleModificable('form:INPUT_'+target, true);
        obj1.readOnly=false;
    } else {
		setStyleModificable('form:INPUT_'+target, false);
		obj1.readOnly=true;
    }
}

function modificabilitatLink(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:LINK_" + target);
	var obj2 = g.getElementById("form:INPUT_" + target);
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
    	obj1.readOnly=false;
    } else {
    	obj1.readOnly=true;
    }
}

function modificabilitatDate(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:INPUT_" + target);
	var obj2 = g.getElementById("form:IMAGE_" + target);
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {

        obj2.disabled=false;
        setStyleModificable('form:INPUT_'+target, true);
        obj1.readOnly=false;
    } else {
    	obj2.disabled=true;
    	setStyleModificable('form:INPUT_'+target, false);
        obj1.readOnly=true;
    }
}

function modificabilitatNumber(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:INPUT_" + target);
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
        setStyleModificable('form:INPUT_'+target, true);
        obj1.readOnly=false;
    } else {
    	setStyleModificable('form:INPUT_'+target, false);
        obj1.readOnly=true;
    }
}

function modificabilitatBoolean(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:INPUT2_" + target);// contiene el combo
	var objMod = g.getElementById("form:INPUT2_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT2", target, resposta, isCarregaInicial)) {
		setStyleModificable('form:INPUT2_'+target, true);
		obj1.readOnly=false;
		obj1.disabled=false;
    } else {
    	setStyleModificable('form:INPUT2_'+target, false);
    	disabled=true;
    	obj1.readOnly=true;
    	obj1.disabled=true;
    }
}

function modificabilitatDocument(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:INPUT_" + target);
	var obj2 = g.getElementById("form:URL_" + target);
	var obj3 = g.getElementById("form:CHECK_" + target);
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var respostaBox = "";

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
        obj2.disabled = false;
        obj3.disabled=false;

        if(obj3.checked || obj1.value ==''){ //check || (hay link que mostrar ==> no hay fichero subido)
			//modificable y el check activo y no se ha subido ningun fichero todav?a
			obj2.disabled = false;
			obj1.disabled = false;
		} else{
			obj2.disabled = true;
			obj1.disabled = true;
		}
    } else {//no modificable
		obj1.disabled = true;
    	obj2.disabled = true;
    	obj3.disabled=true;
    }
}

function modificabilitatTextArea(target, resposta, isCarregaInicial) {
	var obj1 = g.getElementById("form:INPUT_" + target);
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
        setStyleModificable('form:INPUT_'+target, true);
        obj1.readOnly=false;
    } else {

    	setStyleModificable('form:INPUT_'+target, false);
        obj1.readOnly=true;
    }
}

function modificabilitatBoto(target, resposta, isCarregaInicial) {
	var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
	var obj1 = g.getElementById("form:BUTTON_" + target);
	

	if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
        obj1.disabled=false;
    } else {
        obj1.disabled=true;
    }
}
function modificabilitatBotNav(target, resposta, isCarregaInicial) {
    var objMod = g.getElementById("form:INPUT_" + target + "_MOD");
    var obj1 = g.getElementById("form:INPUT_" + target);
    
    if (isModificable("INPUT", target, resposta, isCarregaInicial)) {
        obj1.disabled=false;
    } else {
        obj1.disabled=true;
    }
}

function isModificable(input, target, resposta, isCarregaInicial){
	var objMod = g.getElementById("form:" + input + "_" + target + "_MOD");
	var respostaBox = "";

	//si es una funcio de la modificabilitat del requadre agafem
	//la modificabilitat de la variable
	if(objMod!=null) {
		if(isCarregaInicial){
			if(objMod.value == "F") {
				isCarregaInicial = false; //aqui estra la primera vegada
			} else if (objMod.value == "S") {
				resposta = "TRUE";
			} else {
				resposta = "FALSE";
			}
		}
		else{
			if(resposta == "TRUE") objMod.value = "S";
			else objMod.value = "N";
		}
	}

	//si es una funci� del requadre, aquesta funcio
	//ha modificat la modificabilitat del requadre.
	//Nomes hem de veure si aquest canvi ha influit
	//a la modificabilitat de la variable
	var objBox = g.getElementById("form:REQ_VAR_" + target);
	if(objBox!=null){
		var objBox2 = g.getElementById("form:" + objBox.value + "_MOD");
		if(objBox2!=null){
			if(objBox2.value == "S") respostaBox = "TRUE";
			else respostaBox = "FALSE";
		}
	}
	//el varchar ser� modificable si:
	// - la funci� es certa i no est� en un requadre
	// - la funci� es certa i si est� en un requadre, el requadre es modificable
	if (resposta == "TRUE"
			&& (respostaBox == "" || respostaBox == "TRUE")) {
		return true;
	}else{
		return false;
	}
}
/*  isFuncioRequadre no s'utilitza per� est� per no modificar OcurrenceInstance la generaci� de crides inicials
 */
function modificabilitatRequadre(target, resposta, isFuncioRequadre) {
	var obj1 = g.getElementById("form:REQ_" + target + "_MOD");
	if (resposta == "TRUE") {
		obj1.value='S';
    } else {
    	obj1.value='N';
    }
}


// formules obligatorietat


function obligatorietat(target, resposta) {
	if(resposta == "INI") return;
	if(resposta == null || resposta == '' || resposta == 'null') resposta = "FALSE";
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
	if( objMand && tipus) {
		if(tipus.value == 'SELECT')				obligatorietatSelect(target, resposta);
		else if(tipus.value == 'AUTOSELECT')	obligatorietatAutoSelect(target, resposta);
		else if(tipus.value == 'VARCHAR')		obligatorietatVarchar(target, resposta);
		else if(tipus.value == 'LINK')			obligatorietatLink(target, resposta);
		else if(tipus.value == 'DATE')			obligatorietatDate(target, resposta);
		else if(tipus.value == 'NUMBER') 		obligatorietatNumber(target, resposta);
		else if(tipus.value == 'BOOLEAN')		obligatorietatBoolean(target, resposta);
		else if(tipus.value == 'DOCUMENT')		obligatorietatDocument(target, resposta);
		else if(tipus.value == 'TEXTAREA') 		obligatorietatTextArea(target, resposta);
	}
}

function obligatorietatSelect(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objTargetInput = g.getElementById("form:INPUT_SELECT_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
    if (resposta == "TRUE") {
        objMand.value="S";
        setStyleObligatori('form:INPUT_'+target, true);
        setStyleObligatori('form:INPUT_SELECT_'+target, true);
        //a la funcio selectMandatoy tambe es valida que sigui obligatoria la variable pero s'utilitza a mes llocs
        //aqui ens estalviem unes quantes crides        
        selectMandatory(target);
    } else {
        objMand.value="N";
        setStyleObligatori('form:INPUT_'+target, false);
        setStyleObligatori('form:INPUT_SELECT_'+target, false);
    }
}

function obligatorietatAutoSelect(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
    if (resposta == "TRUE") {
        objMand.value="S";
        setStyleObligatori('form:INPUT_'+target, true);

    } else {
        objMand.value="N";
        setStyleObligatori('form:INPUT_'+target, false);
    }
}

function obligatorietatVarchar(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
    if (resposta == "TRUE") {
        objMand.value="S";
        setStyleObligatori('form:INPUT_'+target, true);
    } else {
    	setStyleObligatori('form:INPUT_'+target, false);

        objMand.value="N";
    }
}

function obligatorietatLink(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objTargetLink = g.getElementById("form:LINK_" + target);

	var objMand = g.getElementById("form:MANDATORY_" + target);
    if (resposta == "TRUE") {
        objMand.value="S";
    } else {
        objMand.value="N";
    }
}

function obligatorietatDate(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
    if (resposta == "TRUE") {
        objMand.value="S";
        setStyleObligatori('form:INPUT_'+target, true);
    } else {
        objMand.value="N";
        setStyleObligatori('form:INPUT_'+target, false);
    }
}

function obligatorietatNumber(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
    if (resposta == "TRUE") {
        objMand.value="S";
        setStyleObligatori('form:INPUT_'+target, true);
    } else {
        objMand.value="N";
        setStyleObligatori('form:INPUT_'+target, false);
    }
}

function obligatorietatBoolean(target, resposta) {
	var objTarget = g.getElementById("form:INPUT2_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);

    if (resposta == "TRUE" || resposta == "S") {
        objMand.value="S";
       	setStyleObligatori('form:INPUT2_'+target, true);

    } else {
        objMand.value="N";
        setStyleObligatori('form:INPUT2_'+target, false);
    }
}

function obligatorietatDocument(target, resposta) {
	var obj1 = g.getElementById("form:URL_" + target);
	var obj2 = g.getElementById("form:CHECK_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);

    if (resposta == "TRUE") {
        objMand.value="S";

		setStyleObligatori('form:URL_'+target, true);
		setStyleObligatori('form:CHECK_'+target+'_span', true);
    } else {
        objMand.value="N";

		setStyleObligatori('form:URL_'+target, false);
		setStyleObligatori('form:CHECK_'+target+'_span', false);
	}
}

function obligatorietatTextArea(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objMand = g.getElementById("form:MANDATORY_" + target);
    if (resposta == "TRUE") {
        objMand.value="S";

        setStyleObligatori('form:INPUT_'+target, true);
    } else {
        objMand.value="N";

		setStyleObligatori('form:INPUT_'+target, false);
    }
}


// formules defecte

function defecte(target, resposta) {
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	if(tipus) {
		if(tipus.value == 'SELECT')				defecteSelect(target, resposta);
		else if(tipus.value == 'AUTOSELECT')	defecteAutoSelect(target, resposta);
		else if(tipus.value == 'VARCHAR')		defecteVarchar(target, resposta);
		else if(tipus.value == 'LINK')			defecteLink(target, resposta);
		else if(tipus.value == 'DATE') 			defecteDate(target, resposta);
		else if(tipus.value == 'NUMBER')		defecteNumber(target, resposta);
		else if(tipus.value == 'BOOLEAN')		defecteBoolean(target, resposta);
		else if(tipus.value == 'DOCUMENT')		defecteDocument(target, resposta);
		else if(tipus.value == 'TEXTAREA') 		defecteTextArea(target, resposta);
		else if(tipus.value == 'COMENTARI') 	defecteComentari(target, resposta);
	}
}

function defecteSelect(target, resposta) {
	calculaSelect(target, resposta);
}

function defecteAutoSelect(target, resposta) {
	calculaAutoSelect(target, resposta);
}

function defecteVarchar(target, resposta) {
	calculaVarchar(target, resposta);
}

function defecteLink(target, resposta) {
	calculaLink(target, resposta)
}

function defecteDate(target, resposta) {
	calculaDate(target, resposta);
}

function defecteNumber(target, resposta) {
	calculaNumber(target, resposta)
}

function defecteBoolean(target, resposta) {
	calculaBoolean(target, resposta);
}

function defecteDocument(target, resposta) {
	calculaDocument(target, resposta);
}

function defecteTextArea(target, resposta) {
	calculaTextArea(target, resposta);
}

function defecteComentari(target, resposta) {
	calculaComentari(target, resposta);
}


// formules visibilitat

function visibilitat(target, resposta) {
	if(resposta == "INI") return;
	if(resposta == null || resposta == '' || resposta == 'null') resposta = "TRUE";
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	if(tipus) {
		if(tipus.value == 'SELECT')				visibilitatSelect(target, resposta);
		else if(tipus.value == 'AUTOSELECT')	visibilitatAutoSelect(target, resposta);
		else if(tipus.value == 'VARCHAR')		visibilitatVarchar(target, resposta);
		else if(tipus.value == 'LINK')			visibilitatLink(target, resposta);
		else if(tipus.value == 'DATE')			visibilitatDate(target, resposta);
		else if(tipus.value == 'NUMBER')		visibilitatNumber(target, resposta);
		else if(tipus.value == 'IMAGE')         visibilitatImage(target, resposta);
		else if(tipus.value == 'BOOLEAN')		visibilitatBoolean(target, resposta);
		else if(tipus.value == 'DOCUMENT')		visibilitatDocument(target, resposta);
		else if(tipus.value == 'TEXTAREA') 		visibilitatTextArea(target, resposta);
		else if(tipus.value == 'COMENTARI')		visibilitatComentari(target, resposta);
		else if(tipus.value == 'BOTO'     )		visibilitatBoto    (target, resposta);
		else if(tipus.value == 'BOTNAV')        visibilitatBotNav(target, resposta);
	} else {
		var tipus2 = g.getElementById("form:COMPONENTTYPEREQ_" + target);
		if(tipus2.value == 'REQUADRE')			visibilitatRequadre(target, resposta);
	}
}

function visibilitatSelect(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
    if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatAutoSelect(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatVarchar(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatLink(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatDate(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatImage(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
    var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
    
    if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
            objTarget.style.visibility='hidden';
            objTarget.style.display='';
        } else {
            objTarget.style.display='none';
            objTarget.style.visibility='';
        }
        objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
        objTarget.style.visibility='';
        objTarget.disabled=false;
    }
}

function visibilitatNumber(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatBoolean(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatDocument(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatTextArea(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatComentari(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatBoto(target, resposta) {
	var objTarget = g.getElementById("form:DIV_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
	if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

function visibilitatBotNav(target, resposta) {
    var objTarget = g.getElementById("form:DIV_" + target);
    var objCollapsed = g.getElementById("form:COLLAPSED_" + target);
    if (resposta != "TRUE") {
        if(objCollapsed && objCollapsed.value != 'S') {
            objTarget.style.visibility='hidden';
            objTarget.style.display='';
        } else {
            objTarget.style.display='none';
            objTarget.style.visibility='';
        }
        objTarget.disabled=true;
    } else {
        objTarget.style.display='block';
        objTarget.style.visibility='';
        objTarget.disabled=false;
    }
}

function visibilitatRequadre(target, resposta) {
	if (resposta == "INI") return;
	var objTarget = g.getElementById("form:DIVREQ_" + target);
	var objCollapsed = g.getElementById("form:COLLAPSEDREQ_" + target);
    if (resposta != "TRUE") {
    	if(objCollapsed && objCollapsed.value != 'S') {
    		objTarget.style.visibility='hidden';
    		objTarget.style.display='';
    	} else {
    		objTarget.style.display='none';
    		objTarget.style.visibility='';
    	}
    	objTarget.disabled=true;
    } else {
    	objTarget.style.display='block';
		objTarget.style.visibility='';
		objTarget.disabled=false;
    }
}

// Botons de navegacio a valor de domini
function navegaDomini(target, resposta) {
	if(resposta == "INI") return;
	if(resposta == null || resposta == '' || resposta == 'null') resposta = "TRUE";
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	if(tipus) {
		if(tipus.value == 'SELECT') {
			navegaDominiSelect(target, resposta);
		} else if(tipus.value == 'AUTOSELECT') {
			navegaDominiAutoSelect(target, resposta);
		} else if(tipus.value == 'COMENTARI') {
			//
		}
	} 
}

function navegaDominiSelect(target, resposta) {
	var objTarget = g.getElementById("form:DQ_" + target);
	if(objTarget) {
	    if (resposta == "TRUE") {
	        objTarget.style.display='block';
	        //objTarget.disabled=false;
	    } else {
	        objTarget.style.display='none';
	        //objTarget.disabled=true;
	    }
	}
}

function navegaDominiAutoSelect(target, resposta) {
	var objTarget = g.getElementById("form:DQ_" + target);
	if(objTarget) {
	    if (resposta == "TRUE") {
	        objTarget.style.display='block';
	        //objTarget.disabled=false;
	    } else {
	        objTarget.style.display='none';
	        //objTarget.disabled=true;
	    }
	}
}

function plegatRequadre(target, resposta) {
	if (resposta == "INI") return;
	var objTarget = g.getElementById("form:REQ_FOLD_" + target);
	var imgTarget = g.getElementById("form:IMG_FOLD_" + target);
	var reqTarget = g.getElementById("form:REQ_" + target);
    if (resposta == "TRUE") {
        objTarget.style.display='none';
        reqTarget.style.height=19;
        imgTarget.src='/rsa/images/desplegar_requadre.gif';
        imgTarget.title='Desplegar el requadre';
    } else {
        objTarget.style.display='block';
        reqTarget.style.height=null;
        imgTarget.src='/rsa/images/plegar_requadre.gif';
        imgTarget.title='Plegar el requadre';
    }
}

function collapse_req(id) {
	var capa = g.getElementById('form:REQ_FOLD_'+id);
	var image = g.getElementById('form:IMG_FOLD_'+id);
	var plegar = (capa.style.display=='block' ? 'TRUE' : 'FALSE');
	plegatRequadre(id,  plegar);
}


// formules calcula

function calcula(target, resposta) {
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	if(tipus) {
		if(resposta == null || resposta == 'null') resposta = "";
		if(tipus.value == 'SELECT')				calculaSelect(target, resposta);
		else if(tipus.value == 'AUTOSELECT')	calculaAutoSelect(target, resposta);
		else if(tipus.value == 'VARCHAR')		calculaVarchar(target, resposta);
		else if(tipus.value == 'LINK') 			calculaLink(target, resposta);
		else if(tipus.value == 'DATE')			calculaDate(target, resposta);
		else if(tipus.value == 'NUMBER')		calculaNumber(target, resposta);
		else if(tipus.value == 'BOOLEAN')		calculaBoolean(target, resposta);
		else if(tipus.value == 'DOCUMENT')		calculaDocument(target, resposta);
		else if(tipus.value == 'TEXTAREA') 		calculaTextArea(target, resposta);
		else if(tipus.value == 'COMENTARI')		calculaComentari(target, resposta);
		else if(tipus.value == 'IMAGE')         calculaImage(target, resposta);
		else if(tipus.value == 'BOTNAV')        calculaBotNav(target, resposta);
	}
}

function calculaBotNav(target, resposta) {
	var botNavTarget = g.getElementById("form:INPUT_" + target);
    var botNavTarget2 = g.getElementById("form:INPUT2_" + target);
    var registre = g.getElementById("form:h_registerid");
    var nivell = g.getElementById("form:h_levelid");
    
    botNavTarget2.value = resposta;
    onMouseDownEvent = "accioBotNav('form:INPUT2_"+target+"','browseQuery',"+registre.value+","+nivell.value+"); return false;";
    botNavTarget.setOnMouseDown = onMouseDownEvent;
}

function calculaImage(target, resposta) {
    var imgTarget = g.getElementById("form:INPUT_" + target);
    var imgTarget2 = g.getElementById("form:INPUT2_" + target);
    var reg_creg = g.getElementById("form:h_registerid");
    var baseURL = g.getElementById('form:h_baseURL').value;
    imgTarget2.value = resposta;
    
    if(resposta == null || resposta == '') {
    	imgTarget.src = "/rsa/images/empty.gif";
    } else {
    	imgTarget.src = baseURL+"fileDownload/?CASE=Image&idReg="+reg_creg.value+"&idRep="+resposta;
    }
}

function calculaSelect(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var cambiar = true;
	var idDataType =  g.getElementById("form:DATATYPE_" + target);

	if(idDataType ) {
		if(idDataType.value.indexOf("BOOLEAN") == -1) {     // No es bool
			valor = resposta;
		} else {    // No es bool
			if(resposta == "true" || resposta == "TRUE"  || resposta == "S") {
				valor = "S";
			} else {
				valor = "N";
			}
		}
	} else {    // Desplegable normal
		valor = resposta;
	}
    var indice_ant = objTarget.selectedIndex;
    objTarget.value=valor;
    var trobat = false;
    for (var i = 0; i< objTarget.options.length && (trobat == false); i++) {
        if (objTarget.options[i].value == valor) {
            objTarget.selectedIndex = i;
            trobat = true;
            if (indice_ant == i) cambiar = false;
        }
	}
	if(trobat==false) objTarget.selectedIndex = 0;	// Situa el primer element en cas de que no tingui valor correcte
	//call to onchange event handler
	if ((objTarget.type!="hidden") && (cambiar)){
		objTarget.onchange();
	}
}

function calculaAutoSelect(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var cambiar = true;
    var valor_ant = objTarget.value;
    objTarget.value=resposta;
    if (valor_ant == resposta) cambiar = false;
    if ((objTarget.type!="hidden") && (cambiar)) {
		objTarget.onchange();
	}
}

function calculaVarchar(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var cambiar = true;
    var valor_ant = objTarget.value;
    objTarget.value=resposta;
    if (valor_ant == resposta) cambiar = false;
    if ((objTarget.type!="hidden") && (cambiar)){
		objTarget.onchange();
	}
}

function calculaLink(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var cambiar = true;
	objTarget.value = resposta;
	if ((objTarget.type!="hidden") && (cambiar)){
		objTarget.onchange();
	}
}

function calculaDate(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var cambiar = true;
    var valor_ant = objTarget.value;
    objTarget.value=resposta;
    if (valor_ant == resposta) cambiar = false;
    if ((objTarget.type!="hidden") && (cambiar)) {
		objTarget.onchange();
	}
}

function calculaNumber(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var cambiar = true;
    var valor_ant = objTarget.value;
    objTarget.value=resposta;
    if (valor_ant == resposta) cambiar = false;
    if ((objTarget.type!="hidden") && (cambiar)){
		objTarget.onchange();
	}
}

function calculaBoolean(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objTarget2 = g.getElementById("form:INPUT2_" + target);
	var cambiar = true;
	var checked_ant = objTarget2.checked;
    if (resposta == "true" || resposta == "TRUE"  || resposta == "S") {
        objTarget2.checked = true;
        objTarget.value="S";
        if (checked_ant == true) cambiar = false;
    } else {
        objTarget2.checked = false;
        objTarget.value="N";
        if (checked_ant == false) cambiar = false;
    }
	if ((objTarget.type!="hidden") && (cambiar)){
		objTarget.onchange();
	}
}

function calculaDocument(target, resposta) {
	
}

function calculaTextArea(target, resposta) {
    var objTarget = g.getElementById("form:INPUT_" + target);
	var cambiar = true;
	var valor_ant = objTarget.value;

	objTarget.value=resposta;
    if (valor_ant == resposta) cambiar = false;
	//call to onchange event handler
	if ((objTarget.type!="hidden") && (cambiar)){
		objTarget.onchange();
	}
}

function calculaComentari(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objTargetComponent = g.getElementById("form:INPUT_COMPONENT_" + target);
	var cambiar = true;
	var valor_ant = objTarget.value;
	
	objTarget.value=resposta;
	objTargetComponent.innerText=resposta;
	objTargetComponent.innerHTML=resposta;
	
    if (valor_ant == resposta) cambiar = false;
	//call to onchange event handler
	if ((objTarget.type!="hidden") && (cambiar)){
		objTarget.onchange();
	}
}

// Formules de valors condicionats
function condiciona(target, resposta,recarregaCondicio) {
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	var objTarget = g.getElementById("form:COND_" + target);
	if(recarregaCondicio == undefined || recarregaCondicio == null) recarregaCondicio = true;
	if(tipus && objTarget) {
		if(resposta == null || resposta == 'null') resposta = "";
		if(tipus.value == 'SELECT') {
			condicionaSelect(target, resposta, recarregaCondicio);
		} else if(tipus.value == 'AUTOSELECT') {
			condicionaAutoSelect(target, resposta,recarregaCondicio);
		}
	}
}

function condicionaSelect(target, resposta, recarregaCondicio) {
	var objTarget = g.getElementById("form:COND_" + target);
	var cambiar = true;
    var valor_ant = objTarget.value;
    objTarget.value=resposta;
    if (valor_ant == resposta) cambiar = false;
    if(recarregaCondicio == undefined || recarregaCondicio == null) recarregaCondicio = true;
    if ((objTarget.type!="hidden") && (cambiar) && recarregaCondicio ){
		objTarget.onchange();
		selectMandatory(target);		
	}
}

function condicionaAutoSelect(target, resposta, recarregaCondicio ) {
	var objTarget = g.getElementById("form:COND_" + target);
	var cambiar = true;
    var valor_ant = objTarget.value;
    objTarget.value=resposta;
    if (valor_ant == resposta) cambiar = false;
    if(recarregaCondicio == undefined || recarregaCondicio == null) recarregaCondicio = true;
    if ((objTarget.type!="hidden") && (cambiar) && recarregaCondicio ){
		objTarget.onchange();
	}
}

function visorhcc(target, resposta) {
	if(resposta == "INI") resposta = "FALSE";
	if(resposta == null || resposta == '' || resposta == 'null') resposta = "FALSE";
	var objecte = g.getElementById("form:INPUT_" + target);
	var objTarget = g.getElementById("form:VISORHCC_" + target);
	var objView   = g.getElementById("form:VISORHCC_VIEW_" + target);
	var visorCip  = g.getElementById("form:VISORHCC_CIP");	// Component que es dibuixa si te rol


	if(objView) {
		if (resposta == "TRUE") {
			objView.value = "S";
		} else {
			objView.value = "N";
		}
	}

	if(objecte && objecte.value != null && objecte.value != "") {
		if(objTarget) {
		    if (resposta == "TRUE" && visorCip != null) {	// La fem visible nom�s si te el rol
		    	objTarget.visible=true;
		    	objTarget.style.display='block';
		        objTarget.disabled=false;
		    } else {
		    	objTarget.visible=false;
		        objTarget.style.display='none';
		        objTarget.disabled=true;
		    }
		}
	} else {
		if(objTarget) {
			objTarget.visible=false;
	        objTarget.style.display='none';
	        objTarget.disabled=true;
        }
	}
}

function viewVisor(target) {
	var objView = g.getElementById("form:VISORHCC_VIEW_" + target);
	var objVisor = g.getElementById("form:VISORHCC_" + target);
	var objecte = g.getElementById("form:INPUT_" + target).value;
	var objCip = g.getElementById("form:INPUT2_" + target).innerHTML;
	var visorObjectCip = g.getElementById("form:VISORHCC_CIP");	// Objectes que nom�s es dibuixen si l'usuari te configurat a la metataula l'acc�s al visor HCC 

	if(objVisor) {	// Comprovem si existeixen els components que nom�s es generen si l'usuari te permis per veure el visor
		if(objecte != null && objecte != "") {
			g.getElementById("form:VISORHCC_CIP_" + target).value = objCip.substring(objCip.indexOf("(")+1,objCip.indexOf(")"));
			g.getElementById("form:VISORHCC_NIA_" + target).value = objecte;
			if(objView && objView.value == "S"  && visorObjectCip != null) {	// Nom�s mostrem si te rol
				objVisor.visible=true;
				objVisor.style.display='block';
				objVisor.disabled=false;
			} else {
				objVisor.visible=false;
				objVisor.style.display='none';
				objVisor.disabled=true;
			}
		} else {
			objVisor.visible=false;
			objVisor.style.display='none';
			objVisor.disabled=true;
        }
	}
}

// formules validesa

function validesa(target, resposta, missatge) {
	var objTarget = g.getElementById("form:LABEL_" + target).innerHTML;
	var text = '';
	if(resposta == "TRUE") {
		text = "";
	} else {
		text = objTarget + " " + missatge + "\n";
	}
	return text;
}

function convierte(respAtratar, tipo) {

	var resposta = '';
	if (tipo == 'BOOLEAN') {
		if (respAtratar == true || respAtratar == "TRUE" || respAtratar == "S") resposta = 'TRUE';
		else resposta = 'FALSE';
	} else {
		resposta = respAtratar;
	}

	return resposta;
}

function isPseudo(idVar) {
	if("999910" == idVar || 
	   "999920" == idVar ||
	   "999930" == idVar ||
	   "999940" == idVar ||
	   "999950" == idVar ||
	   "999960" == idVar ||
	   "999970" == idVar ||
	   "999980" == idVar ||
	   "999990" == idVar) {
		return true;
	}
	return false;
}

function formulaAjax(formulaid, actualLevelVariables, actualVariable) {
	// Parametros
	var myAjaxObj= new RecalculaAjax();
	myAjaxObj.prepare(url, method, false);
	myAjaxObj.setForm("form");

    var actualLevelValues = null;
    var actualVariableValue = null;

	if(actualLevelVariables != null) {
	    var ids = actualLevelVariables.split(":");
	    actualLevelValues = "";

        for(var i = 0; i< ids.length; i++ ) {
			var actual = ids[i];
        	var ident = actual.split("_");
        	if(!isPseudo(ident[2])) {
               
                var attrActual = 'ATTR_' + actual;
                eval("var attrValue = " + attrActual +";");

				var newValue = '<value reg_creg="' + ident[0] + '" nrs_cnrs="' + ident[1] + '" vnr_cvnr="' + ident[2] +'">';
				try {
					attrValue = delXmlHead(attrValue.replace("<value>", newValue));
				} catch (e) {
					//alert('Catch: attrValue:' +attrValue+ ' newValue: '+newValue + ' e:'+e);
				}
				actualLevelValues += attrValue;
        	}
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

    if (actualVariable != null) {
    	var attrActual = actualVariable.replace('form:INPUT_','ATTR_');
        eval("var attrValue = " + attrActual +";");
		var ident = actualVariable.split("_");
		var newValue = '<value reg_creg="' + ident[0] + '" nrs_cnrs="' + ident[1] + '" vnr_cvnr="' + ident[2] + '">';
		attrValue = delXmlHead(attrValue.replace("<value>", newValue));
		actualVariableValue = attrValue;
    }

	var res = myAjaxObj.directCall('', formulaid, actualLevelValues, actualVariableValue);
	return myAjaxObj._returnResponse;
}

function isADropDown(target){
	try{
		return (g.getElementById(target).options != null)
	}
	catch(e){
		return false;
	}
}

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

/**Dado un campo de tipo input se le pone el tam?ano en funci?n del contenido.
 * Ojo si el estilo del contenido tiene un size no 'standart puede no caber '
 */
function resizeInput(componente)
{
	var texto = componente.value;
	componente.size = texto.length+3;
}

/**
 * Carrega els components a pantalla a partir de la variable
 */
// Carrega els components a pantalla a partir de la variable valorsCarregatsXml

function carregaSelect(target, codi, condition, recarregaCondicio ) {

	var objTarget = g.getElementById("form:INPUT_" + target);//select
	var idDataType =  g.getElementById("form:DATATYPE_" + target);
	var obTargetInput = g.getElementById("form:INPUT_SELECT_" + target);//input que simula el select
	var cond =  g.getElementById("form:COND_" + target);

	// Es podria utilitzar condicionaSelect() pero com te el control de canvi, inicialmente no faria onchange
	condiciona(target, condition, (condition==null||condition=='')?false:true);

	if(idDataType.value.indexOf("BOOLEAN") != -1) {     // SI es bool
		if(codi == "true" || codi == "TRUE"  || codi == "S") {
			codi = "S";
		} else if(codi.indexOf("ERROR") != -1 || codi == "N" || codi == "false" || codi == "FALSE") {
			codi = "N";
		} else {
			codi = "";
		}
	}
	objTarget.value=codi;
    var trobat = false;

    for (var i = 0; i< objTarget.options.length && (!trobat); i++) {
        if (objTarget.options[i].value == codi) {
            objTarget.selectedIndex = i;
            trobat = true;
            //copiar la info del select en un input
            obTargetInput.value = objTarget.options[objTarget.selectedIndex].text;
            resizeInput(obTargetInput);//redimensaionar el componente text
        }
	}
	
	if(!trobat) objTarget.selectedIndex = 0;	// Situa el primer element en cas de que no tingui valor correcte

	// Carrega atribut de desplegable en cas de que no estigui carregant -> Ja tenim atribut de Servidor.
	// -> Soluciona problema d'incoher�ncia de atributs en cas de que el despleagable s'hagi condicionar de forma "encadenada"
	if(trobat && !estatCarregant) {
		myOnChangeFunction(objTarget);
	}	
	selectMandatory(target);
	
}

function carregaAutoSelect(target, codi, descripcio,condition, recarregaCondicio ) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objTarget2 = g.getElementById("form:INPUT2_" + target);
	var cond = g.getElementById("form:COND_" + target);
    objTarget.value=codi;
	if(objTarget2) {
		if(descripcio == null || descripcio == "") descripcio = "Carregar descripció";
		objTarget2.innerHTML = descripcio.replace(">","&gt;").replace("<","&lt;");
	}
	// Es podria utilitzar condicionaAutoselect() pero com te el control de canvi, inicialmente no faria onchange
	condiciona(target, condition,recarregaCondicio);

	viewVisor(target);
}

function carregaVarchar(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
    objTarget.value=resposta;
}

function carregaLink(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	objTarget.value = resposta;
}

function carregaDate(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
    objTarget.value=resposta;
}

function carregaNumber(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
    objTarget.value=resposta;
}

function carregaBoolean(target, resposta) {
	var objTarget = g.getElementById("form:INPUT_" + target);
    var objTarget2 = g.getElementById('form:INPUT2_'+target);
    if(objTarget2 ) {
	    if (resposta == "true" || resposta == "TRUE"  || resposta == "S") {
	    	objTarget.value = "S";
	        objTarget2.checked = true;
	    } else {
	    	objTarget.value = "N";
	        objTarget2.checked = false;
	    }
    } else {    //Desplegable
		carregaSelect(target, resposta, null, false);
    }
}

function carregaImage(target, resposta) {
    calculaImage(target,resposta);
}

function carregaBotNav(target, resposta) {
    var botNavTarget = g.getElementById("form:INPUT_" + target);
    var botNavTarget2 = g.getElementById("form:INPUT2_" + target);
    var registre = g.getElementById("form:h_registerid");
    var nivell = g.getElementById("form:h_levelid");
    
    botNavTarget2.value = resposta;
    onMouseDownEvent = "accioBotNav('form:INPUT2_"+target+"','browseQuery',"+registre.value+","+nivell.value+"); return false;";
    botNavTarget.setOnMouseDown = onMouseDownEvent;
}

function carregaDocument(target, codi, descripcio) {
	var objTarget = g.getElementById("form:INPUT_" + target);
	var objCheck = 	g.getElementById("form:CHECK_"+target);
	var objButton = g.getElementById("form:LINK_"+target);	// el button
	var objLink = g.getElementById('form:LINK1_'+target);	// el hyperlink
	var objUrl = g.getElementById('form:URL_'+target);
	var objDivCheck = g.getElementById('form:DIV_CHECK_'+target);
	

	var fileId = (codi == null || codi == ''? "NO_VALUE" : codi);
	var valor = (descripcio == null || descripcio == ''? "NO_VALUE" : descripcio);



	objButton.style.display = 'none'; // no es mostra per� es crida
	if(fileId == "NO_VALUE") {
		if(objDivCheck){
			objDivCheck.className='DivOculto';
		}
		objUrl.disabled=false;
		objLink.innerHTML = '';
		objLink.style.display = 'none';
		objTarget.value = '';
	} else {
		objTarget.value = fileId;
		objCheck.checked = false;
		
		if (descripcio.indexOf('@#@') != -1) {
			var elems = descripcio.split('@#@');
			objLink.value = elems[1];
			objLink.innerHTML = elems[1];
			if (elems[0] == "true") {	
				objCheck.checked = true;
				objUrl.value = elems[2];
			}
		} else {
			objLink.value = valor;
			objLink.innerHTML = valor;
			objLink.onclick = function() { objButton.click(); return null; }
		}
			
		// CanviDocument
		if(objTarget.value=='') {
			if(objDivCheck){
				objDivCheck.className='DivOculto';
			}
	        objUrl.disabled=false;
	    } else {
		    if(objDivCheck){
		    	objDivCheck.className='';
		    }
	        objUrl.disabled=true;
	    }
	    
	}
}

function carregaTextArea(target, resposta) {
    var objTarget = g.getElementById("form:INPUT_" + target);
	objTarget.value=escapeRetorn(resposta);
}

function carregaVariableComentari(target, resposta, descripcio,condition, recarregaCondicio) {
	var objTargetComponent = g.getElementById("form:INPUT_COMPONENT_" + target);
	var objTarget = g.getElementById("form:INPUT_" + target);
	objTargetComponent.innerText = objTarget.value;
	objTargetComponent.innerHTML = objTarget.value;
	
	if(objTarget.type != 'textarea') {	// Te llista de valors o es boolea
		objTarget.value = resposta;
		objTargetComponent.innerText = resposta;
		objTargetComponent.innerHTML=resposta;
		objTarget = g.getElementById("form:INPUT2_" + target);
		objTargetComponent = g.getElementById("form:INPUT_COMPONENT2_" + target);
	}

	objTarget.readOnly = "readOnly";

	if(descripcio == null || descripcio == "") objTarget.value=escapeRetorn(resposta);
	else objTarget.value=escapeRetorn(descripcio);
	
	if(descripcio == null || descripcio == "") {
		objTargetComponent.innerText=escapeRetorn(resposta);
		objTargetComponent.innerHTML=escapeRetorn(resposta);
	} else {
		objTargetComponent.innerText=escapeRetorn(descripcio);
		objTargetComponent.innerHTML=escapeRetorn(descripcio);
	}
	
//	var isDisplayNone = false;
//	var objReq;
//	var objReqVar = document.getElementById('form:REQ_VAR_'+target);
//	if(objReqVar != null) {
//		objReq = document.getElementById('form:DIV'+objReqVar.value);
//		if (objReq.style.display == 'none') isDisplayNone = true;
//	}
//	// ampliem el textarea de comentari al maxim
//	if(isDisplayNone) objReq.style.display = 'block';
//	while(objTarget.scrollHeight > objTarget.clientHeight) {
//		objTarget.rows += 1;
//	}
//	if(isDisplayNone) objReq.style.display = 'none';
}

function carrega(target, resposta, descripcio,condition, recarregaCondicio) {
	var tipus = g.getElementById("form:COMPONENTTYPE_" + target);
	if(resposta == '' ) resposta = descripcio;
	if(tipus) {
		if(tipus.value == 'SELECT')				carregaSelect(target, resposta, condition, recarregaCondicio);
		else if(tipus.value == 'AUTOSELECT')	carregaAutoSelect(target, resposta, descripcio,condition, recarregaCondicio);
		else if(tipus.value == 'VARCHAR')		carregaVarchar(target, resposta);
		else if(tipus.value == 'LINK')			carregaLink(target, resposta);
		else if(tipus.value == 'DATE')			carregaDate(target, resposta);
		else if(tipus.value == 'NUMBER')		carregaNumber(target, resposta);
		else if(tipus.value == 'BOOLEAN') 		carregaBoolean(target, resposta);
		else if(tipus.value == 'DOCUMENT')		carregaDocument(target, resposta, descripcio);
		else if(tipus.value == 'TEXTAREA')		carregaTextArea(target, resposta);
		else if(tipus.value == 'COMENTARI')		carregaVariableComentari(target, resposta, descripcio,condition, recarregaCondicio);
		else if(tipus.value == 'IMAGE')         carregaImage(target, resposta);
		else if(tipus.value == 'BOTNAV')        carregaBotNav(target, resposta);
		else if(tipus.value == 'REQUADRE') {
			//carregaRequadre(target, resposta, descripcio);
		}
	}
}

// Construeix per a cada component que hi ha a pantalla en el moment de fer submit
// el valor per a concatenar a la variable valorsCarregatsXml

function recuperaValorsXml(ident) {
	var tipus = g.getElementById("form:COMPONENTTYPE_" + ident);
	var valorRetornat = '';
	if(tipus) {
		if(tipus.value == 'SELECT')				valorRetornat = recuperaValorsXmlSelect(ident);
		else if(tipus.value == 'AUTOSELECT')	valorRetornat = recuperaValorsXmlAutoSelect(ident);
		else if(tipus.value == 'IMAGE') {
			carregaAtributSimple("ATTR_"+ident,g.getElementById("form:INPUT2_"+ident).value);
			valorRetornat = recuperaValorsXmlImage(ident);
		} else if(tipus.value == 'BOTNAV') {
            carregaAtributSimple("ATTR_"+ident,g.getElementById("form:INPUT2_"+ident).value);
            valorRetornat = recuperaValorsXmlBotNav(ident);
		} else if(tipus.value == 'VARCHAR') {
			carregaAtributSimple("ATTR_"+ident,g.getElementById("form:INPUT_"+ident).value);
			valorRetornat = recuperaValorsXmlVarchar(ident);
		} else if(tipus.value == 'LINK')		valorRetornat = recuperaValorsXmlLink(ident);
		else if(tipus.value == 'DATE')			valorRetornat = recuperaValorsXmlDate(ident);
		else if(tipus.value == 'NUMBER')		valorRetornat = recuperaValorsXmlNumber(ident);
		else if(tipus.value == 'BOOLEAN')		valorRetornat = recuperaValorsXmlBoolean(ident);
		else if(tipus.value == 'DOCUMENT')		valorRetornat = recuperaValorsXmlDocument(ident);
		else if(tipus.value == 'TEXTAREA') {
			carregaAtributSimple("ATTR_"+ident,g.getElementById("form:INPUT_"+ident).value);
			valorRetornat = recuperaValorsXmlTextArea(ident);
		} else if(tipus.value == 'COMENTARI') {

			var objTarget = g.getElementById("form:INPUT_" + ident);
			if(objTarget.type == 'textarea') {
				carregaAtributSimple("ATTR_"+ident,g.getElementById("form:INPUT_"+ident).value);
			}
			valorRetornat = recuperaValorsXmlComentari(ident);
		}
	}
	return valorRetornat;
}


function recuperaValorsXmlSelect(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = '';
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");
	var cond = g.getElementById("form:COND_"+ident);

	// Si l'objecte es null es perqu� est� deshabilitat o s'ha esborrat
	if(obj == null)	 {
		obj = g.getElementById("form:INPUT_SELECT_"+ident);
	}
	
	if(obj) {
		try {
			codi = obj.options[obj.selectedIndex].value;
			descripcio = obj.options[obj.selectedIndex].text;
			if(descripcio == "- Sense determinar -") descripcio = "";
		} catch(e) {
			codi = '';
			descripcio = '';
		}

		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}

		var objDomQVisible = g.getElementById("form:DQ_"+ident);
		if(objDomQVisible) {
			if(objDomQVisible.style.display == "none") {
				txtDomini = "FALSE";
			} else {
				txtDomini = "TRUE";
			}
		}

		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}

		if(objLabel.style.color){
			txtColor = objLabel.style.color;
		}
		if(cond) {
			condition = escape(cond.value);
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlAutoSelect(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = '';
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");
	var cond = g.getElementById("form:COND_"+ident);
	var objView = g.getElementById("form:VISORHCC_VIEW_" + ident);
	if(obj) {
		var autoDesc = g.getElementById("form:INPUT2_"+ident);
		codi = obj.value.replace("&gt;",">").replace("&lt;","<");
		if (g.getElementById("form:HIDDEN_NIA_OCULT_" + ident)){
			codi = g.getElementById("form:HIDDEN_NIA_OCULT_"+ident).value.replace("&gt;",">").replace("&lt;","<");
		}
		descripcio = autoDesc.innerHTML.replace("&gt;",">").replace("&lt;","<");
		if(descripcio == "Sense determinar") descripcio = "";
		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}

		var objDomQVisible = g.getElementById("form:DQ_"+ident);
		if(objDomQVisible) {
			if(objDomQVisible.style.display == "none") {
				txtDomini = "FALSE";
			} else {
				txtDomini = "TRUE";
			}
		}

		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}

		if(objLabel.style.color){
			txtColor = objLabel.style.color;
		}
		if(cond) {
			condition = escape(cond.value);
		}

		if(objView) {
			if(objView.value == "S") {
				visor = "TRUE";
			}else {
				visor = "FALSE";
			}
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlBotNav(ident){
	var codi = "";
    var descripcio = '';
    var idDocument = 'N';
    var txtObligatoria = "FALSE";
    var txtVisible = '';
    var txtModificable = '';
    var txtColor = '';
    var txtXml = '';
    var condition = '';
    var visor = '';
    var txtDomini = '';

    var objBotNav = g.getElementById("form:INPUT_"+ident);
    var botNavTarget2 = g.getElementById("form:INPUT2_"+ident);
    var objObligatori = g.getElementById("form:MANDATORY_"+ident);
    var objVisible = g.getElementById("form:DIV_"+ident);
    var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");
    var objLabel = g.getElementById("form:LABEL_"+ident);
    var cond = g.getElementById("form:COND_"+ident);
    
    if(objBotNav) {
    	if(botNavTarget2) {
	        descripcio = botNavTarget2.value;
	    }
	    
        if(objObligatori) {
            txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
        }
        
        if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
            txtVisible = "FALSE";
        } else {
            txtVisible = "TRUE";
        }
        
        if(objMod && isModificableByStyle(objMod)){
            txtModificable = "TRUE";
        } else{
            txtModificable = "FALSE";
        }
        
        if(objBotNav.style.backgroundColor){
            txtColor = objBotNav.style.backgroundColor;
        }
        
        if(cond) {
            condition = escape(cond.value);
        }
        
    }
    txtXml = addIdToXmlValue(ident);
    
    var txtEstil = '';
    var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
    return ret;
}

function recuperaValorsXmlImage(ident){
	var codi = "";
    var descripcio = '';
    var idDocument = 'N';
    var txtObligatoria = "FALSE";
    var txtVisible = '';
    var txtModificable = '';
    var txtColor = '';
    var txtXml = '';
    var condition = '';
    var visor = '';
    var txtDomini = '';

    var imgTarget2 = g.getElementById("form:INPUT2_"+ident);
    if(imgTarget2) {
        descripcio = imgTarget2.value;
    }
    txtXml = addIdToXmlValue(ident);
    var txtEstil = '';
    var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
    return ret;
}

function recuperaValorsXmlVarchar(ident) {
	var codi = "";
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");

	if(obj) {
		descripcio = obj.value;
		if(descripcio == "Sense determinar") descripcio = "";
		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}
		//guardem l'estat autentic de les variables
		//d'aquesta manera no guardem una variable com no modificable si la modificabilitat ve marcada pel requadre
		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}

		if(objLabel.style.color){
			txtColor = objLabel.style.color;
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlLink(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objTarget2 = g.getElementById("form:LABEL_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");

	if(obj) {
		descripcio = obj.value;
		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}

		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}
		if(objTarget2.style.color) {
			txtColor = objTarget2.style.color;
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlDate(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");

	if(obj) {
		descripcio = obj.value;
		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}
		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}
		if(objLabel.style.color){
			txtColor = objLabel.style.color;
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlNumber(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");

	if(obj) {
		descripcio = obj.value;
		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}

		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}

		if(objLabel.style.color){
			txtColor = objLabel.style.color;
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlBoolean(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = '';
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objTarget2 = g.getElementById('form:INPUT2_'+ident);
	var objTarget3 = g.getElementById('form:LABEL_'+ident);
	var objMod = g.getElementById("form:INPUT2_"+ident+"_MOD");

	if(obj) {
		if (objTarget2) {
			if (objTarget2.checked) {
				codi = "S";
				descripcio = "Si";
			} else {
				codi = "N";
				descripcio = "No";
			}
			carregaAtributCheck("ATTR_"+ident, codi);

			var objObligatori = g.getElementById("form:MANDATORY_"+ident);
			if(objObligatori) {
				txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
			}
			var objVisible = g.getElementById("form:DIV_"+ident);
			if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
				txtVisible = "FALSE";
			} else {
				txtVisible = "TRUE";
			}

			if(objMod && isModificableByStyle(objMod)){
					txtModificable = "TRUE";
				} else{
					txtModificable = "FALSE";
				}

			if(objTarget3.style.color) {
				txtColor = objTarget3.style.color;
			}
		} else { // desplegable;
			return recuperaValorsXmlSelect(ident);
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlDocument(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = '$DOCUMENT$';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objTarget = g.getElementById("form:INPUT_"+ident);
	var objCheck = g.getElementById('form:CHECK_' + ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");

	if(objTarget) {
		var codiFitxer1 = g.getElementById('form:INPUT_' + ident).value;
		var codiFitxer2 = g.getElementById('form:URL_' + ident).value;
		var codiFitxer3 = g.getElementById('form:LINK_' + ident).innerHTML;

		codi = (codiFitxer1 =='' ? "NO_VALUE":codiFitxer1);
		descripcio =  objCheck.checked
					+ '@#@'
					+ (codiFitxer3 =='' ? "NO_VALUE":codiFitxer3)
					+ '@#@'
					+ (codiFitxer2 =='' ? "NO_VALUE":codiFitxer2);


		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}

		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}

		if(objLabel.style.color) {
			txtColor = objLabel.style.color;
		}
	}
	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlTextArea(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");

	if(obj) {
		descripcio = unEscapeRetorn(obj.value);
		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}
		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}

		if(objLabel) {
			if(objLabel.style.color){
				txtColor = objLabel.style.color;
			}
		}
	}

	txtXml = addIdToXmlValue(ident);
	var txtEstil = '';
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	
	return ret;
}

function recuperaValorsXmlComentari(ident) {
	var codi = '';
	var descripcio = '';
	var idDocument = 'N';
	var txtObligatoria = "FALSE";
	var txtVisible = '';
	var txtModificable = '';
	var txtColor = '';
	var txtEstil = '';
	var txtXml = '';
	var condition = ''; // No pot tenir condicio
	var visor = '';
	var txtDomini = '';

	var obj = g.getElementById("form:INPUT_"+ident);
	var objLabel = g.getElementById("form:LABEL_"+ident);
	var objTarget = g.getElementById("form:INPUT2_"+ident);
	var objMod = g.getElementById("form:INPUT_"+ident+"_MOD");
	var objComponent = g.getElementById("form:INPUT_COMPONENT_"+ident);

	if(obj) {
		if(obj.type == 'textarea') { //No te llista de valors ni es boolea
			codi = '';
			descripcio = unEscapeRetorn(obj.value);
		} else {	// Pot tenir llista de valors o ser boolea
			codi = unEscapeRetorn(obj.value);
			descripcio = unEscapeRetorn(objTarget.value);
		}
		var objObligatori = g.getElementById("form:MANDATORY_"+ident);
		if(objObligatori) {
			txtObligatoria = (objObligatori.value == "S" ? "TRUE" : "FALSE");
		}
		var objVisible = g.getElementById("form:DIV_"+ident);
		if(objVisible.style.display == "none" || objVisible.style.visibility == 'hidden') {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}
		if(objMod && isModificableByStyle(objMod)){
			txtModificable = "TRUE";
		} else{
			txtModificable = "FALSE";
		}

		if(objComponent) {
			if(objComponent.style.color){
				txtColor = objComponent.style.color;
			}
			//la chapucilla de la semana. Tenemos tres estilos y los dos primeros son solo para el estilo propio de las variables mensaje. 
			//El que nos interesa es el tercero
			txtEstil = objComponent.className.split(' ')[2];
		}
	}

	txtXml = addIdToXmlValue(ident);
	if(obj && obj.type=='textarea') {

	}
	var ret = ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@REQ@|@" + txtEstil + "@|@" + condition + "@|@" + visor + "@|@"  + txtDomini + "@|@" + txtXml  + "|#|";
	return ret;
}

function recuperaValorsXmlRequadre(ident) {
	var codi = '$REQ$';
	var descripcio = '$REQ$';
	var idDocument = 'N';
	var txtObligatoria = "INI";
	var txtVisible = '';
	var txtModificable = 'INI';
	var txtColor = '';
	var txtPlegat='INI';
	var txtXml = '$REQ$';

	var obj = g.getElementById("form:REQ_"+ident);
	var objMod = g.getElementById("form:REQ_"+ident+"_MOD");
	var objPlegat = g.getElementById('form:REQ_FOLD_'+ident);

	if(obj) {
		var objVisible = g.getElementById("form:DIVREQ_"+ident);
		if(objVisible.style.display == "none") {
			txtVisible = "FALSE";
		} else {
			txtVisible = "TRUE";
		}
		if(obj.style.borderColor) {
			txtColor = obj.style.borderColor;
		}
		if(objMod != null) {
			if(objMod.value == "S") txtModificable = "TRUE";
			else txtModificable = "FALSE";
		}
		if(objPlegat != null) {
			if(objPlegat.style.display=='none') txtPlegat="TRUE";
			else 								txtPlegat="FALSE";
		}
	}
	return ident + ":" + codi + "@|@" + descripcio + "@|@" + idDocument + "@|@" + txtObligatoria + "@|@" + txtVisible  + "@|@" + txtModificable + "@|@" + txtColor + "@|@" + txtPlegat  + "|#|";
}

function parseaInt(valor) {
	if(valor == null || valor == '') return 0;
	if(!isNaN(valor)) {
		return valor;
	}
	return 0;
}

function parseaFloat(valor) {
	var resultat = 0;
	valor = valor.toString().replace(',','.');
	if(valor == null || valor == '') return 0;
	if(!isNaN(valor)) {
		resultat = parseFloat(valor);
	} 
	return	resultat;
}

function escapeRetorn(valor) {
	return valor.replace(/&#13;/g,'\r').replace(/&#10;/g,'\n');
}

function unEscapeRetorn(valor) {
	return valor.replace(/\r/g,"&#13;").replace(/\n/g,'&#10;');
}
