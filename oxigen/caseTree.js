function selectFile(ident) {
    document.getElementById('form:LINK_'+ident).target="";
    document.getElementById('form:selectedfile').value = document.getElementById('form:INPUT_'+ident).value;
}

function outputsAvailable() {
    //sempre comprovem que hi hagi alguna sortida predefinida per permetre la seleccio dels valors del < select >
    var output=document.getElementById('form:registerOutputs');
    if (output.length==1 && output.options[0].text!=null && output.options[0].text.indexOf('No hi ha sortides predefinides')>=0) {
         output.disabled=true;
         document.getElementById('form:selectOutputConfirm').disabled=true;
    }
}

//Mostra i oculta la capa del popUpErrorImportReport
function doPopUpErrorImportReport(){
  var elemento = document.getElementById("popUpErrorImportReport");    
  if (elemento.style.visibility == "visible") {
  	//ocultem div
  	elemento.style.visibility="hidden";
	//habilitem botons i links
	enableButtons();
	enableLinks();
  }
  else {
	//mostrem div
   	elemento.style.visibility="visible";
	//inhabilitem botons i links
	disableButtons();
	disableLinks();
  }
}

//Mostra i oculta la capa del popUpImportReport
function doPopUpImportReport(){
  var elemento = document.getElementById("popUpImportReport");    
  if (elemento.style.visibility == "visible") {
  	//ocultem div
  	elemento.style.visibility="hidden";
	//habilitem botons i links
	enableButtons();
	enableLinks();
  }
  else {
	//mostrem div
   	elemento.style.visibility="visible";
	//inhabilitem botons i links
	disableButtons();
	disableLinks();
  }
}
function go(i) {
	document.getElementById("form:idNav").value=i;
}


function doAdd(levelId, pLevelId, pOccId) {
	if(levelId==='37144'){
		document.getElementById("form").action='http://localhost/buildkit/oxigen/200Prescripciodetractament.htm';
	}else if(levelId==='37163'){
		document.getElementById("form").action='http://localhost/buildkit/oxigen/210VariablesdeTractament.htm';
	}else if(levelId==='37186'){
		document.getElementById("form").action='http://localhost/buildkit/oxigen/230Baixadelaprescripcio.htm';
	}
	
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:parentLevelId").value=pLevelId;
	document.getElementById("form:occurrenceId").value='';
	document.getElementById("form:parentOccurrenceId").value=pOccId;
	document.getElementById("form:editionMode").value='S';
	document.getElementById("form:addOccurrenceHB").click();
	//alert('doEdit:'+pOccId);
}

function doEdit(levelId, occId, pOccId, accio) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:parentOccurrenceId").value=pOccId;
	document.getElementById("form:editionMode").value=accio;
	document.getElementById("form:editOccurrenceHB").click();
	//alert('doEdit:'+occId);
}

function doDelete(levelId, occId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:nextAction").value='deleteOccurrence';
	document.getElementById("form:popUpMessage").innerHTML='Segur que voleu esborrar la ocurr\u00e8ncia?';
	//alert('doDelete:'+occId);
	scroll(0,0);
	document.getElementById("form:popUpActionMessage").value = 'Eliminant...';
	doPopUp();
	parent.scroll(0,0);
}

function doDeactive(levelId, occId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:nextAction").value='deactivateOccurrence';
	document.getElementById("form:popUpActionMessage").value = 'Desant els canvis...';
	document.getElementById("form:popUpDeactivateReasonText").value='';
	//alert('doDeactive:'+occId);
	scroll(0,0);
	doPopUpDeactivateReason();
	parent.scroll(0,0);
}

function doActive(levelId, occId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:nextAction").value='activateOccurrence';
	document.getElementById("form:popUpActionMessage").value = 'Desant els canvis...';
	document.getElementById("form:popUpDeactivateReasonText").value='';
	//alert('doActive:'+occId);
	document.getElementById("form:activateOccurrenceHB").click();
}

function doPrint(levelId, occId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	scroll(0,0);
	doSelectOutput();
	//alert('doPrint:'+occId);
}

function doDuplicate(levelId, occId, pLevelId, pOccId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:parentLevelId").value=pLevelId;
	document.getElementById("form:parentOccurrenceId").value=pOccId;
	document.getElementById("form:editionMode").value='S';
	document.getElementById("form:copyOccurrenceHB").click();
}

function doCopy(levelId, occId) {
	document.getElementById("form:copiedLevelId").value=levelId;
	document.getElementById("form:copiedOccurrenceId").value=occId;
	document.getElementById("form:copyOccInSessionHB").click();
	alert("S'ha copiat l'ocurr\u00e8ncia i les seves filles. Premi [Enganxar] sobre el nivell desitjat.");
}

function doPaste(parentOccurrenceId) {
	var reply;
	
	if(parentOccurrenceId == ""){
		//nivell arrel
		reply = confirm("Es crear\u00e0 un nou cas amb les dades de l'\u00faltima ocurr\u00e8ncia " + 
				"copiada i les seves filles.\nRecordi que un cop finalitzat es continuar\u00e0 " + 
				"mostrant el cas actual i no el nou.\n\nAquesta acci\u00f3 pot tenir una duraci\u00f3 " +
				"de m\u00e9s d'un MINUT.\nSegur que voleu continuar amb l'acci\u00f3?");
	}else{
		//no es el nivell arrel
		reply = confirm("S'enganxar\u00e0 en aquest nivell l'\u00faltima ocurr\u00e8ncia copiada i " + 
				"les seves filles.\n\nAquesta acci\u00f3 pot tenir una duraci\u00f3 de m\u00e9s d'un MINUT.\n" +
				"Segur que voleu continuar amb l'acci\u00f3?");
	}

	if(reply == true){
		document.getElementById("form:pastedParentOccurrenceId").value = parentOccurrenceId;
		document.getElementById("form:pasteOccFromSessionHB").click();
	}
}

function doUndo(levelId, occId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:editionMode").value='S';
	document.getElementById("form:undoOccurrenceHB").click();
	//alert('doUndo:'+occId);
}

function doRestore(levelId, pLevelId, pOccId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:parentLevelId").value=pLevelId;
	document.getElementById("form:parentOccurrenceId").value=pOccId;
	document.getElementById("form:editionMode").value='S';
	document.getElementById("form:restoreOccurrenceHB").click();
	//alert('doRestore:'+pOccId);
}


function doAdj(levelId, occId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:nextAction").value='reportOccurrence';
	document.getElementById("form:popUpMessage").innerHTML='Segur que voleu adjuntar el report de la ocurr�ncia?';
	document.getElementById("form:popUpActionMessage").value = 'Adjuntant report de la ocurr�ncia...';
	scroll(0,0);
	doPopUp();
	parent.scroll(0,0);
	
}

function doSign(levelId, occId) {
	document.getElementById("form:levelId").value=levelId;
	document.getElementById("form:occurrenceId").value=occId;
	document.getElementById("form:nextAction").value='signOccurrence';
	document.getElementById('form:popUpMessage').innerHTML='Segur que voleu signar la ocurr\u00e8ncia amb el vostre tel\u00e8fon m\u00f2bil?';
	document.getElementById("form:popUpActionMessage").value = 'Signant ocurr�ncia...';
	scroll(0,0);
	doPopUp();
	parent.scroll(0,0);
	
}

function collapse(id,p_more_end) {
	var ico = document.getElementById(id.substr(1));
	var obj = document.getElementById(id);
	//var dis = obj.style.display;
	if(obj.style.display == 'none') {
		obj.style.display = 'block';
		ico.src='/rsa/images/handle_collapse_' + p_more_end +'.gif';
	} else {
		obj.style.display = 'none';
		ico.src='/rsa/images/handle_expand_' + p_more_end +'.gif';
	}
}
