api = 2
core = 7.x

; Include Drupal core and any core patches.
includes[] = drupal-org-core.make

; Download the BuildKit install profile
projects[buildkit][type] = profile
projects[buildkit][download][type] = git
projects[buildkit][download][url] = http://git.drupal.org/project/buildkit.git
projects[buildkit][download][branch] = 7.x-2.0-beta4
