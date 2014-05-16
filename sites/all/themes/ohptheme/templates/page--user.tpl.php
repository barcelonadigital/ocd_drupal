      <div class="container">
      <!--
      <div class="nav">
        <ul>
          <li><a href="#">English</a></li>
          <li><a href="#">Español</a></li>
        </ul>
      </div>
       -->
      <h1 class="logo-ocd"><?php print t('Open Health Practice');?></h1>
      <?php if (isset($messages)): ?>
        <div id="messages" class="gris1">
          <div class="container">
            <?php print $messages; ?>
          </div>
        </div>
      <?php endif; ?>
      <div class="caja">
        <?php print render($page['content']); ?>
      </div>
    </div>