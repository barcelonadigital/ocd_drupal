<?php

function ohptheme_pager($tags = array(), $limit = 10, $element = 0, $parameters = array()) {
    global $pager_page_array, $pager_total;
    $page_init = 0;
    $page_prev = $pager_page_array[$element] - 1;
    $page_curr = $pager_page_array[$element] + 1;
    $page_next = $pager_page_array[$element] + 1;
    $page_last = $pager_total[$element] - 1;
    # get querystrings (except q="" and page="")
    $cgi = $_SERVER['REQUEST_METHOD'] == 'GET' ? $_GET : $_POST;
    $query = '';
    foreach ($cgi as $key => $val) {
        if ($key != 'page' && $key != 'q') {
            $query .= '&'. $key .'='. $val;
        }
    }
    $query = substr($query, 1);
    if ($pager_total[$element] > 1) {
        $output = '<div class="pagination"><div class="navigation">';
        $visibility = "";
        if ($pager_page_array[$element]==0) {
          $visibility = "visibility:hidden;";
        }
        $output.= '<a href="?page='.$page_init.'&'.$query.'" style="'.$visibility.'">Primer</a>';
        $output.= '<a href="?page='.$page_prev.'&'.$query.'" style="'.$visibility.'" class="btn btn-large btn-info prev">Anterior</a>';
        $visibility = "";
        if ($page_curr==$pager_total[$element]) {
          $visibility = "visibility:hidden;";
        }
        $output.= '<a href="?page='.$page_next.'&'.$query.'" style="'.$visibility.'" class="btn btn-large btn-info next">Següent</a>';
        $output.= '<a href="?page='.$page_last.'&'.$query.'" style="'.$visibility.'">Últim</a>';
        $output.= '</div><div class="status">'.t('Mostrant pàgina ');
        $output.= $page_curr.' '.t(' de ').' '.$pager_total[$element];
        $output.= '</div></div>';
        return $output;
    }
}

function ohptheme_preprocess_html(&$variables) {
  $variables['classes_array'][] = $variables['logged_in'] ? '' : 'login';
}

function ohptheme_theme(&$existing, $type, $theme, $path) {
  $items = array();
  // create custom user-login.tpl.php
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'ohptheme') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
      'ohptheme_preprocess_user_login'
    ),
  );
  $items['user'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'ohptheme') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
      'ohptheme_preprocess_user_login'
    ),
  );
  return $items;
}
