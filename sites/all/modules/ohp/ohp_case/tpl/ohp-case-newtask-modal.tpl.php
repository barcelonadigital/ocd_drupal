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
 * Template file for theming the new task modal.
 */
?>
    <!-- Lightbox-->
    <script>
    function assignarProtocolParam(paramActivitat) {
      var admissionId = '<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>';
      var caseId = '<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>';
      var params = { id_admission:admissionId, id_case:caseId, id_activity:paramActivitat };
  	  var str = jQuery.param( params );
  	  window.location='<?php echo url('ohp/ohp_task_insert'); ?>?'+str;
    }
    </script>
    <div id="alertModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal alert hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close">Tancar</button>
        <h3>Avís</h3>
      </div>
      <div class="modal-body">
        <p>Si us plau, seleccioni la avaluació que vol realitzar:</p>
      </div>
      <div class="modal-footer">
        <div class="btn-block">
                <button onclick="assignarProtocolParam('#TASK:N253')" class="btn btn-warning custom-btn btn-large">Prescripció d'OCD</button>
                <button onclick="assignarProtocolParam('#TASK:N261')" class="btn btn-warning custom-btn btn-large">Visita de seguiment</button>
        </div>
      </div>
    </div>
