      <div class="dataform">
        <div class="smallfield">
            <?php
          // split the username and password so we can put the form links were we want (they are in the "user-login-links" div bellow)
          print drupal_render($form['name']);
          print drupal_render($form['pass']);
          ?>
        </div>
        <div class="smallfield">
            <?php
          // split the username and password so we can put the form links were we want (they are in the "user-login-links" div bellow)
          print drupal_render($form['name']);
          print drupal_render($form['pass']);
          ?>
        </div>
          <?php
              // render login button
          print drupal_render($form['form_build_id']);
          print drupal_render($form['form_id']);
          ?>
          <div class="actions">
            <input type="submit" id="buttonEnter" class="btn btn-large btn-primary" value="<?php print t('Entrar');?>">
          </div>
      </div>