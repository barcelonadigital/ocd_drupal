    <div class="custom-cabecera">
      <div class="container">
        <header>
          <a class="brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
        </header>
        <nav>
          <ul class="nav">
            <li class="user">
              <a href="#" data-toggle="dropdown">
	              <img src="<?php global $base_path; print $base_path.path_to_theme(); ?>/img/ico-clinician-m.png" alt="${sessionScope.userFullName}">
	              <strong><?php if (isset($_SESSION['user_full_name'])): print $_SESSION['user_full_name']; endif; ?></strong>
	              <span><?php if (isset($_SESSION['user_center'])): print $_SESSION['user_center']; endif; ?></span>
              </a>
              <div class="dropdown-menu">
                <ul>
                  <!--
                  <li><html:link action="/logoutAction"><bean:message key="label.myAccount"/></html:link></li>
                  -->
                  <li><a href="/logoutAction"><?php print t('Logout'); ?></a></li>
                </ul>
              </div>
            </li>
          </ul>
        </nav>
      </div>
    </div>
    <!-- Cabecera (final)-->
    <!-- Menú principal-->

    <nav data-spy="affix" data-offset-top="106" class="custom-menuprincipal">
      <div class="container">
        <ul class="nav">
          <li><a href="#" data-toggle="dropdown" class="users">
              <strong><?php print t('Usuaris'); ?></strong><span><?php print t('Pacients, ...'); ?></span></a>
            <div class="dropdown-menu">

              <?php if (isset($_SESSION['case_bean'])): ?>
              <div class="user_data">
                <div><strong><?php print t('Pacient actual'); ?></strong></div>
                <div class="user"><?php print $_SESSION['case_bean']->fullname; ?></div>
                <ul>
	              <li><a action="/caseTaskDetailsAction?idCase=${caseBean.idCase}&idAdmission=${admissionBean.idAdmission}" styleClass="${formularisClass}"><?php print t('Tasques'); ?></a></li>
	              <li><a action="/caseDetailsAction?idCase=${caseBean.idCase}&idAdmission=${admissionBean.idAdmission}" styleClass="${infoPacientClass}"><?php print t('Informació pacient'); ?></a></li>
                </ul>
              </div>
              <div class="newpacient"><a styleClass="brand" action="/caseSearchPg"><?php print t('Seleccionar un <br>altre pacient'); ?></a></div>
              <?php endif; ?>
              <?php if (!isset($_SESSION['case_bean'])): ?>
              <div class="newpacient"><a styleClass="brand" action="/caseSearchPg"><?php print t('Seleccionar <br>pacient'); ?></a></div>
              <?php endif; ?>
            </div>
          </li>
          <li><a href="#" data-toggle="dropdown" class="tasks">
              <strong><?php print t('Tasques'); ?></strong><span><?php print t('Pendents, ...'); ?></span></a>
            <div class="dropdown-menu">

              <div class="task_links">
                <ul>
                <li><a action="/tasksAssignedAction"><?php print t('Pendents'); ?></a></li>
                <!--
                <logic:present name="caseBean">
			    <logic:present name="actionsTransfer">
			    <logic:iterate name="actionsTransfer" id="actionItem" type="org.bdigital.ocd.model.form.ActionAf" >
					<li><html:link action="/caseTaskInsertAction?idAdmission=${admissionBean.idAdmission}&idCase=${caseBean.idCase}" paramId="idActivity" paramName="actionItem" paramProperty="ref" onclick="return confirm('Es finalitzarà (DISCHARGE) el protocol actiu actualment. Desitja continuar?');"><bean:write name="actionItem" property="name"/></html:link></li>
				</logic:iterate>
				</logic:present>
			    <logic:present name="actions">
			    <logic:iterate name="actions" id="actionItem" type="org.bdigital.ocd.model.form.ActionAf" >
					<li><html:link action="/caseTaskInsertAction?idAdmission=${admissionBean.idAdmission}&idCase=${caseBean.idCase}" paramId="idActivity" paramName="actionItem" paramProperty="ref"><bean:write name="actionItem" property="name"/></html:link></li>
				</logic:iterate>
				</logic:present>
				</logic:present>
				-->
                </ul>
              </div>
            </div>
          </li>
          <li><a href="#" data-toggle="dropdown" class="report">
              <strong><bean:message key="menu.reports"/></strong><span><bean:message key="menu.reports.desc"/></span></a>
            <div class="dropdown-menu">

              <div class="links">
                <ul>
                  <li><a href="#"><?php print t('Link'); ?> 1</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 2</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 3</a></li>
                </ul>
              </div>
            </div>
          </li>
          <li><a href="#" data-toggle="dropdown" class="community">
              <!-- botón--><strong><bean:message key="menu.community"/></strong><span><bean:message key="menu.community.desc"/></span></a>
            <div class="dropdown-menu">
              <!-- dropdown menu-->
              <div class="links">
                <ul>
                  <li><a href="#"><?php print t('Link'); ?> 1</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 2</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 3</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 4</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 5</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 6</a></li>
                </ul>
              </div>
            </div>
          </li>
          <li><a href="#" data-toggle="dropdown" class="more">
              <strong><bean:message key="menu.more"/></strong><span><bean:message key="menu.more.desc"/></span></a>
            <div class="dropdown-menu">

              <div class="links">
                <ul>
                  <li><a href="#"><?php print t('Link'); ?> 1</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 2</a></li>
                  <li><a href="#"><?php print t('Link'); ?> 3</a></li>
                </ul>
              </div>
            </div>
          </li>
        </ul>
      </div>
    </nav>
    <div class="modal hide" id="pleaseWaitDialog" data-backdrop="static" data-keyboard="false"><div class="modal-header"><h1><?php print t('Processant'); ?>...</h1></div><div class="modal-body"><div class="progress progress-striped active"><div class="bar" style="width: 100%;"></div></div></div></div>
    <?php print render($page['content']); ?>
    <div class="footer">
      <div class="container"><?php print t('© BDigital & Linkcare 2014'); ?></div>
    </div>