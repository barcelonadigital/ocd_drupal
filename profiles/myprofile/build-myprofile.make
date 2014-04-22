; Include Drupal core and any core patches from Build Kit
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/drupal-org-core.make
api = 2
core = 7.x

projects[drupal][type] = core
projects[drupal][version] = 7.22
;projects[drupal][patch][995156] = http://drupal.org/files/issues/995156-5_portable_taxonomy_permissions.patch

; Add myprofile to the full Drupal distro build
projects[myprofile][type] = profile
projects[myprofile][download][type] = git
projects[myprofile][download][url] = https://github.com/jordifhios/myprofile.git
