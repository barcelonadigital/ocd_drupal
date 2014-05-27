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
 * Template file for theming the case menu.
 */
?>
        <nav class="menuizq">
          <ul>
            <!--
             -->
            <li><a href="<?php echo url('ohp/ohp_case_main'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>" class="<?php if (isset($is_active_menu_formularis)): print 'active'; endif; ?>"><?php print t('Tasques'); ?></a></li>
            <li><a href="<?php echo url('ohp/ohp_case_main'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>" class="<?php if (isset($is_active_menu_info_pacient)): print 'active'; endif; ?>"><?php print t('Informació pacient'); ?></a></li>
            <!--
            <li><html:link action="/caseHistoricAction?idCase=${caseBean.idCase}" styleClass="${historicClass}">Protocols anteriors</html:link></li>
             -->
          </ul>
        </nav>
