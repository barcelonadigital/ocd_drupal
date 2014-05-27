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
 * Template file for theming the case search page.
 */
?>
    <div class="gris1">
      <div class="container">
        <!-- Encabezado-->
        <div class="encabezado bordebajo">
          <header>
            <h1><?php print t('Usuaris'); ?> <strong>— <?php print t('Pacients'); ?></strong></h1>
          </header>
        </div>
        <!-- Encabezado fin-->
      </div>
      <div class="menuizqlayout">
        <div class="container">
          <div class="content">
            <h2 class="clinician"><?php print t('Cercar pacient'); ?></h2>
            <a href="#info1" role="button" data-toggle="modal" class="info_popup"><?php print t('Info'); ?></a>
            <?php print $search_box; ?>
          </div>
        </div>
      </div>
      <!-- Contenido fin-->
    </div>
    <!-- Lightboxes-->
    <div id="info1" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal detail hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Tancar'); ?></button>
        <h3><?php print t('Cercar pacient'); ?></h3>
      </div>
      <div class="modal-body">
        <h4><?php print t('Sobre quins camps es realitza la cerca?'); ?></h4>
        <p><?php print t('Pels identificadors <strong>CIP</strong> i <strong>NHC</strong> dels pacients emmagatzemats al <strong>HIS</strong>.'); ?></p>
      </div>
    </div>
