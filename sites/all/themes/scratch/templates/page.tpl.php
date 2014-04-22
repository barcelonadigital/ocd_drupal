<div class="black-header">
  <div class="scratch-user-menu">
    <?php if ($logged_in): ?>
      <?php print render($page['user_menu']); ?>
    <?php else: ?>
      <ul>
        <li class="menu"><a href="<?php base_path(); ?>user/login">Log In</a></li>
      </ul>
    <?php endif; ?>
  </div>
</div>
<div class="scratch-header clearfix">
  <div class="logo-div">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
    <?php endif; ?>
  </div>
  <div class="scratch-main-menu">
    <?php print render($page['main_menu']); ?>
  </div>
</div>
<div class="scratch-content-container-div clearfix">
  <?php if ($messages): ?>
    <div id="messages">
      <div class="section clearfix">
        <?php print $messages; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($breadcrumb): ?>
    <div id="breadcrumb"><?php print $breadcrumb; ?></div>
  <?php endif; ?>

  <h1><?php print $title; ?></h1>

  <?php print render($page['content']); ?>
</div>
<div class="scratch-footer">
  <hr />
  <div class="scratch-footer-text">
    &copy; 2013 scratch. All rights reserved.
  </div>
</div>