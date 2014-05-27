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
 * Template file for theming the case header for form pages.
 */
?>
    <div class="cabeceraperfil">
      <div class="container">
        <div id="contentnophotoslim" class="content">
          <small><?php echo t('Pacient'); ?></small>
          <h2><?php  print $fullname; ?></h2>
          <?php if (isset($ident_patient)): ?>
              <?php print $ident_patient; ?>
          <?php endif; ?>
          <div class="contactinfo">
            <div class="dropdown">
              <a href="#" data-toggle="dropdown" class="btn-large dropdown-toggle">
              <?php echo t('Dades de contacte'); ?><span class="caret"></span>
              </a>
              <div class="dropdown-menu">
                <?php print render($dropdown_list); ?>
              </div>
            </div>
          </div>
          <!--
          <div class="contactinfo">
            &nbsp;&nbsp;&nbsp;&nbsp;<a href="#protocolsModal" role="button" data-toggle="modal">Històric protocols</a>
          </div>
          -->
        </div>
      </div>
    </div>
