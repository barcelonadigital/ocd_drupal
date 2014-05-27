<?php

/**
 * Author: Jordi Roda, Ernest Pastor, Filip Velickovski, Magí Lluch-Ariet
 * Barcelona Digital Technology Centre, 2014
 *
 * Open Health Practice is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Open Health Practice is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Template file for theming the case form hints modals.
 */
?>
    <!-- Lightbox-->
    <div id="helpGasometriaModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal loadsession hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Close'); ?></button>
        <h3>Informació</h3>
      </div>
      <div class="modal-body">
          <h6>Procediment de la Gasometria arterial</h6>
          <p><strong>Descripció:</strong> Obtenció d’una mostra de sang arterial mitjançant punció d’una arteria radial o braquial (per aquest ordre) amb finalitat diagnòstica.</p>
          <p><strong>Preparació del pacient abans del procediment:</strong></p>
          <p>Informar al pacient que se li va a realitzar i explicar-li com pot col·laborar.</p>
          <p>Si es tracta d’una gasometria basal, sense oxigen, el pacient ha d’estar al menys 20 minuts abans, en repòs sense oxigen. En el cas que porti oxigen (a la FiO2 que correspongui), assegurar que el pacient porta l’oxigenoteràpia prescrita durant al menys 20 minuts i que està en repòs.</p>
          <p>Per evitar el dolor de la punció i com a conseqüència provocar que el pacient hiperventili, situació que pot alterar els resultats gasomètrics, es recomana l’administració d’anestèsic (mepivacaína clorhidrat o lidocaïna 1%) sense vasoconstricció, via subcutània, infiltrant 0,2 ml d’anestèsic amb una agulla fina (d’insulina 0,36 mm) propera a la zona on es farà la punció arterial, fent un petit massatge després de la retirada de la xeringa i deixant que passin 1-2 minuts, perquè faci efecte.</p>
          <p><strong>Procediment:</strong></p>
          <p><strong>Material necessari:</strong> Xeringa de gasometria (si no, xeringa de 3 cossos de 2ml + agulla 21-23G + Heparina Na 1% + tap per la mostra arterial), anestèsic local (mepivacaína clorhidrat o lidocaïna 1%), xeringa d’insulina, gases, alcohol 70%, guants no estèrils, coixí o tovallola enrotllada, pinça hemostàsia, apòsit, etiqueta identificativa del pacient.</p>
          <p>Seqüència de acció:</p>
          <p>El lloc de elecció son per aquest ordre la arteria radial y la arteria humeral.</p>
          <p><span style="text-decoration:underline;">Punció arterial radial:</span></p>
          <p>
              <img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/gasometria1.jpg" align="left">
              <img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/gasometria2.jpg" align="left">Quant la via de elecció es la arteria radial (zona del canal carpià), es realitzarà el Test d’Allen modificat, per comprovar la permeabilitat de la circulació col•lateral de la ma. (<a href="http://www.nejm.org/doi/full/10.1056/NEJMicm1001091" target="_blank">http://www.nejm.org/doi/full/10.1056/NEJMicm1001091)</a></p>
          <p>Test d’Allen modificat: consisteix en que el pacient obri i tanqui la ma varies vegades, al mateix temps que la infermera pressiona simultàniament amb els dits índex i mig  la arteria radial i cubital de la ma explorada. La palma de la ma i els dits de la ma es tornen pàl•lids. Es deixa de pressionar la arteria cubital i s’observa el retorn del flux de sang a la ma adquirint un color vermell en menys de 10 segons, el que constitueix test d’Allen positiu. La arteria radial es pot puncionar.</p>
          <p><img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/gasometria3.jpg" align="left">Rentat de mans i col•locació de guants no estèrils.</p>
          <p>Posicionarem l’avantbraç en extensió sobre una superfície plana. El canell ha de estar en flexió dorsal i a sota del canell es col•locarà una tovallola enrotllada.</p>
          <p><img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/gasometria4.jpg" align="left">Desinfectarem la zona de la pell amb alcohol i mantindrem un parell de minuts el seu efecte.</p>
          <p>Aplicarem anestèsic local.</p>
          <p>Si es una xeringa especifica per gasometria col•locarem l’èmbol en la posició de 2ml. En un altre cas heparinitzarem la xeringa i l’agulla amb 0,5ml d’Heparina Na al 1% desplaçant l’èmbol varies vegades per impregnar las parets de la xeringa de heparina.</p>
          <p><img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/gasometria5.jpg" align="left">Rebutjant la resta.</p>
          <p>Localitzem el lloc exacte mitjançant la palpació de la artèria radial amb els dits de la ma. Amb l’altre ma s’ introdueix l’agulla amb el bisell cap amunt, avançant lentament amb l’agulla en direcció proximal (cap el tronc), en un angle de 45º. Indicar al pacient que respiri amb normalitat i que no es mogui.</p>
          <p><img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/gasometria6.jpg" align="left">En el cas de xeringa especifica de gasometria, esperar sense mobilitzar l’agulla a obtenir els 2ml de sang arterial. En un altre cas aspirar suaument fins obtenir 2ml de sang arterial.</p>
          <p>Purgar la xeringa amb la mostra de sang arterial, perquè no quedi cap bombolla d’aire.</p>
          <p>Tirar l’ agulla al contenidor y col•locar el tap a la xeringa.</p>
          <p><img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/gasometria7.jpg" align="left">Realitzar compressió digital durant 5 minuts. S’allargarà a 10-15 min. En el cas de que el pacient tingui problemes de coagulació o prengui medicació anticoagulant (acenocumarol).</p>
          <p>Identificar la mostra amb l’etiqueta identificativa. Retirar la compressió i col•locarem un apòsit.</p>
          <p><span style="text-decoration:underline;">Punció arterial humeral:</span></p>
          <ul>
              <li>Localitzarem el lloc exacte mitjançant la palpació de la arteria humeral amb els dits de la mà.</li>
              <li>L’ inclinació de l’agulla serà de 60º dirigint la punció en direcció proximal (cap el tronc).</li>
              <li>El temps de compressió serà de 7 a 10 min. que s’allargarà a 15-20 min. En el cas que el pacient tingui problemes de coagulació o tingui pautats anticoagulants.</li>
          </ul>
          <p><strong>Descripció de problemes e intervencions relacionats amb el procediment</strong></p>
          <p>Hematoma: Assegurar una bona compressió, valorant las condiciones del pacient; si te alteració de la coagulació, o bé està en tractament anticoagulant, assegurarem el temps de compressió en aquests casos.</p>
          <p>Aspectes a remarcar:</p>
          <ul>
              <li>Si la prova d’Allen modificada es negativa, s’ha de buscar un altre arteria per a la punció.</li>
              <li>Utilitzar sempre anestesia per realitzar el procediment, a fi d’evitar alteracions de la PO2/PCO2, per hiperventilació secundaria al dolor de la punció.</li>
              <li>Respectar el temps que necessita l’anestèsic per tenir efecte.</li>
          </ul>
          <p><strong>Bibliografia/ evidencia científica / Recomanacions de societats científiques</strong></p>
          <p>Normativa SEPAR sobre gasometria arterial. Agustí GN, A, Burgos F, Casna P, Perpiñá M, Rodriguez Roisin R, Sánchez AL, Sobradillo V, Togores B. Arch Bronconeumol 1998; 34: 142-153. (<a href="http://issuu.com/separ/docs/normativa_006" target="_blank">http://issuu.com/separ/docs/normativa_006</a>)</p>
      </div>
    </div>
    <div id="helpPulsioModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal loadsession hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Close'); ?></button>
        <h3>Informació</h3>
      </div>
      <div class="modal-body">
          <h6>Procediment de la medició puntual de pulsioximetria</h6>
          <ol>
            <li>Comprovar que el pulsioxímetre tingui piles abans de començar la medició. (Es comprova mirant en el dibuix en forma de pila que hi ha en el pulsioxímetre. Si falten piles, s’encén i s’apaga).</li>
            <li>Comprovar que la qualitat de la senyal es òptima (amplitud de la onda de pols) en cas contrari pot produir valors erronis.</li>
            <li>El pacient ha d’estar assegut o incorporat al llit i tranquil.</li>
            <li>Comprovar que les ungles de les mans estan netes i sense esmalt.</li>
            <li>La medició de la pulsioximetria ha de realitzar-se (si no s’indica el contrari) en las següents condicions:</li>
            <li>Basal (sense oxigen)</li>
            <li>Ha de quedar registrat en quines condicions s’ha realitzat la medició al costat del resultat.
                <br>Exemple: Cànules nasals 2 litres/mi (SatO<sub>2</sub> 95%);  Basal (SatO<sub>2</sub> 96%)
            </li>
            <li>Col·locar el didal tal como mostra la figura y posar en marxa el pulsioxímetre.
                <br><img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/pulsioximetria.png"></li>
            <li>Esperar a que la xifra dels resultats es mantingui tal como mostra la figura.</li>
            <li>Després de la medició, retirar el pulsioxímetre i guardar amb l’embolcall corresponent.</li>
          </ol>
      </div>
    </div>
    <div id="helpEspiroModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal loadsession hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Close'); ?></button>
        <h3>Informació</h3>
      </div>
      <div class="modal-body">
          <h6>Procediment de la Espirometria Forçada</h6>
          <p>Realitzar per personal ensinistrat. <strong>UNA PROVA REALITZADA INCORRECTAMENT ES UN RESULTAT NO FIABLE</strong></p>
          <ol>
            <li>Informar al pacient</li>
            <li><strong>EVITAR L’ADMINISTRACIÓ DE BRONCODILATADORS Y REGISTRAR EN CAS DE  QUE ELS HAGI PRES</strong> (6 hores els d’acció curta; 12 hores els d’acció llarga, 24 hores els anticolinèrgics d’acció llarga)</li>
            <li>Pes i talla</li>
            <li>Pacient assegut sense creuar les cames</li>
            <li>Col·locar pinça nasal</li>
            <li>Realitzar <strong>UN MINIM DE TRES MANIOBRES I UN MAXIM DE VUIT MANIOBRES</strong> amb inici brusc e intentar que <strong>DUES DE ELLES ESTIGUIN LLIURES D’ERRORS</strong> i que las diferencies de la <strong>FVC y FEV1 siguin inferiors al 5% o 150 ml</strong> (100 si la FVC és inferior a un litre): El temps de duració de cada maniobra no serà inferior a 4 segons (preferiblement 6 segons).</li>
          </ol>
      </div>
    </div>
    <div id="helpTabaqModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal loadsession hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Close'); ?></button>
        <h3>Informació</h3>
      </div>
      <div class="modal-body">
          <h6>Càlcul paq/any</h6>
          <p><strong>Paq/any</strong></p>
          <p>Número de cigarretes que fuma al dia multiplicat pel número d'anys que porta fumant, i dividit entre 20.</p>
          <p>Exemple:</p>
          <p>1 paquet al dia durant 20 anys = 20 cigarretes al dia X 20 anys /20 = 20 paquets/any</p>
          <p><strong>Altres definicions</strong></p>
          <p>Exfumador: Almenys 6 mesos continuats sense fumar.</p>
          <p>Fumador: Fumador diari de qualsevol quantitat de cigarrets durant l'últim mes. Persona que respon afirmativament a la pregunta ¿fuma vosté?</p>
      </div>
    </div>
    <div id="helpImcModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal loadsession hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Close'); ?></button>
        <h3>Informació</h3>
      </div>
      <div class="modal-body">
          <h6>Càlcul IMC</h6>
          <p>IMC = Pes (kg) / Alçada<sup>2</sup> (m).</p>
      </div>
    </div>
    <div id="helpPulsioNoctModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal loadsession hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Close'); ?></button>
        <h3>Informació</h3>
      </div>
      <div class="modal-body">
          <h6>Procediment pulsioximetria nocturna</h6>
          <p>Els estudis del son com la pulsioximetria nocturna nomes estan indicats si es sospita de la coexistència de la síndrome d’ apnea del son o si hi ha poliglobúlia i/o signes d’insuficiència cardíaca dreta.</p>
          <p><strong>Oxigenoteràpia durant el son:</strong></p>
          <p>En pacients amb pO<sub>2</sub> > 60mmHg, es pot plantejar la indicació d’oxigenoteràpia únicament durant el son si presenten durant mes del 30% del temps de son una SatO<sub>2</sub> < 90% o en pacients amb hipoxemia diürna y criteris de OCD, l’augment nocturn del flux d’oxigen evita dessaturacions freqüents i perllongades.</p>
          <p>Normes per la realització d’una pulsioximetria nocturna per el pacient:</p>
          <ol>
            <li>Comprovar que les ungles estiguin netes i seques (sense esmalts)</li>
            <li>A l’hora d’anar a dormir, s’ha de col•locar l’oxímetre en el canell tal i como es veu en el dibuix. Col•locar el sensor  (didal) i fixar-lo amb la malla que se li ha proporcionat de forma que quedi ben subjecte y no molesti.</li>
            <li>Prémer el botó blau de POWER per posar-lo en marxa.</li>
            <li>A la pantalla apareixerà l’any, el mes, el dia i l’hora.</li>
            <li>Apareixeran els valors (el que correspon a la saturació d’oxigen i al pols). En aquest moment l’aparell ja funciona.</li>
            <li>Vostè pot dormir tranquil·lament. En cas que es desperti i necessiti anar al WC, no es necessari que desconnecti ni apagui l’aparell.</li>
            <li>Pel mati quant es desperti, haurà de tornar a polsar el botó blau de POWER per finalitzar l’estudi. Desconnecti l’aparell amb compte i guardi’l a l’estoig.</li>
          </ol>
      </div>
    </div>
    <div id="helpAdequacioModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal loadsession hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Close'); ?></button>
        <h3>Informació</h3>
      </div>
      <div class="modal-body">
          <h6>Guies clíniques</h6>
          <p><span style="text-decoration:underline;">Adequació:</span></p>
          <img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'ohptheme'); ?>/img-contenido/adequacio.jpg">
          <ol>
            <li>Malaltia en situació evolutiva avançada.</li>
            <li>Tractament associat correcte.</li>
            <li>Control de l’hàbit tabàquic.</li>
            <li>Situació clínica estable.</li>
            <li>PaO<sub>2</sub> de ≤ 55 mmHg respirant aire ambient o PaO<sub>2</sub> entre 56-59 mmHg amb evidencia d’hipertensió pulmonar, cor pulmonale o policitèmia</li>
            <li>MPOC (escassa evidencia en altres malalties)</li>
            <li>La sensació d’ ofec amb l’exercici en pacients amb MPOC que no tenen hipoxemia en repòs no ha de ser utilitzat com criteri per prescriure oxigenoteràpia crònica domiciliària</li>
            <li>Flux d’oxigen suficient per mantenir una PaO<sub>2</sub> superior a 60mmHg (Sat O<sub>2</sub> aproximada de 93%). Flux d’oxigen, la dosis mes comuna sol oscil·lar entre 1 y 2 l/min administrats mitjançant ulleres basals. Per tal d’evitar els efectes nocius del exercici i del son sobre els valors de la PaO<sub>2</sub> i assegurar-nos de mantenir aquets en un rang suficient, la dosi considerada idònia pot ser incrementada en ambdues circumstàncies.</li>
            <li>Es desitjable valorar l’increment de manera objectiva en cada individu (pulsioximentria nocturna, walking test).</li>
            <li>OCD amb altres circumstancies:</li>
          </ol>
          <table>
            <tr>
              <th>Patologia</th>
              <th>Evidències</th>
            </tr>
            <tr>
              <td>Fibrosi quística</td>
              <td>Possible benefici de l’oxigen portàtil si existeix hipoxemia</td>
            </tr>
            <tr>
              <td>Bronquiectasis</td>
              <td>Si hipoxemia</td>
            </tr>
            <tr>
              <td>Fibrosi pulmonar</td>
              <td>Sense beneficis demostrats</td>
            </tr>
            <tr>
              <td>Seqüeles de la tuberculosi</td>
              <td>Si hipoxemia i si el flux prescrit la corregeix</td>
            </tr>
            <tr>
              <td>Cifoscoliosi</td>
              <td>Complement de la ventilació (?)</td>
            </tr>
            <tr>
              <td>Càncer</td>
              <td>No beneficis si no hi ha hipoxemia</td>
            </tr>
            <tr>
              <td>Malalties neuromusculars avançades</td>
              <td>Pocs beneficis</td>
            </tr>
            <tr>
              <td>Cefalea en cúmuls</td>
              <td>Possible benefici de O<sub>2</sub> al 100% al inici de la crisi</td>
            </tr>
            <tr>
              <td>Insuficiència cardíaca</td>
              <td>Sense beneficis demostrats</td>
            </tr>
          </table>
          <br>
          <p><strong>Comentaris addicionals</strong></p>
          <p>Alguns MPOC presenten episodis d’hipoxemia durant el son, mantenint valors de PaO2 normals en estat de vigilia. Aquesta condició pot coexistir amb la síndrome d’apnea durant el son y requereixen la pràctica de registres polisomnogràfics.</p>
          <p>L’administració d’oxigen durant el son, constitueix tan sols una de las mesures terapèutiques utilitzades en algunes circumstancies. El seu ús ha estat inclús controvertit (alleujament de l’hipoxemia, augment de la duració de las pauses de l’apnea)</p>
          <p>En alguns MPOC, sense episodis d’apnea, l’hipoxemia empitjora durant el son. Considerar l’indicació d’oxigen durant aquests episodis, sempre que es puguin objectivar descensos de la PaO2 por sota de 55 mmHg i existeixin signes de repercussió de l’hipoxia a nivell orgànic. L’indicació no s’ hauria de considerar definitiva.</p>
          <p><strong>Bibliografia/ evidencia científica / Recomanacions de societats científiques</strong></p>
          <p>The Global Strategy for Diagnosis, Management and Prevention of COPD (<a href="http://www.goldcopd.com" target="_blank">www.goldcopd.com</a>)</p>
          <p>Indicación y empleo de la oxigenoterapia continua domiciliaria (OCD) (<a href="http://www.separ.es" target="_blank">www.separ.es</a>)</p>
          <p>Fletcher EC, et al. T. Nocturnal oxyhemoglobin desaturation in COPD patients with arterial oxygen tensions above 60 mmHg. Chest 1987; 92: 604-608 (<a href="http://journal.publications.chestnet.org/article.aspx?articleid=1060518" target="_blank">http://journal.publications.chestnet.org/article.aspx?articleid=1060518</a>)</p>
          <p>Effect of palliative oxygen versus room air in relief of breathlessness in patients with refractory dyspnoea: a double-blind, randomized controlled trial. Amy P Abernelthy, et al. Lancet 2010: 784--93 (<a href="http://www.thelancet.com/journals/lancet/article/PIIS0140-6736(10)61115-4/fulltext" target="_blank">http://www.thelancet.com/journals/lancet/article/PIIS0140-6736(10)61115-4/fulltext</a>)</p>
          <p>A randomized trial of domiciliary, ambulatory oxygen in patients with COPD and dyspnoea but without resting hypoxaemia. Rosemary P Moore, et al. Thorax 2011; 66: 32 e 37 (<a href="http://thorax.bmj.com/content/66/1/32.abstract" target="_blank">http://thorax.bmj.com/content/66/1/32.abstract</a>)</p>
          <p><span style="text-decoration:underline;">Compliment:</span></p>
          <p>15 hores al dia (inclosa la nit) com a minim millora el pronostic del pacient amb MPOC amb insuficiencia respiratoria.</p>
      </div>
    </div>
