<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<?php /* region--navigation.tpl.php */ ?>

<div style="font-size:20px;font-weight:bold;width:100%;background-color:yellow;text-align:center;color:red;"> DRAFT VERSION - NOT FOR OFFICIAL USE </div>


<?php if ($page['navigation']): ?>
  <?php print render($page['navigation']); ?>
<?php endif; ?>

<div class="main-container container">

  <?php /* region--header.tpl.php */ ?>
  <?php print render($page['header']); ?>
<?php /* if ($tabs): ?><?php print render($tabs); ?><?php endif; */ ?>
  <div class="row">

    <?php /* region--sidebar.tpl.php  ?>
    <?php if ($page['sidebar_first']): ?>
      <?php print render($page['sidebar_first']); ?>
    <?php endif; */?>

    <?php /* region--content.tpl.php */ ?>
    <div class="region region-content col-sm-12">
		<div id="printer">
		<?php
			$options = array();
			//Le titre est le nom du site
			$options['title'] = drupal_get_title();
			//Le sous titre le nom de la page
			//$options['subtitle'] ='Le glossaire librement réutilisable que chacun peut améliorer';
			//Description de la page (en fait le titre)
			//if($title!='') $options['comment'] = str_replace("'", "&#039;", $title);
// 			print wkhtmltopdf_tag(array('.node', '.region-content', '.content', '#content', '#recherche'), $options);
			$nodeType = '';
			if (!empty($page['content']['system_main']['nodes'])) {
				foreach (array_keys($page['content']['system_main']['nodes']) as $key) {
					if (!empty($page['content']['system_main']['nodes'][$key]['#bundle'])) {
						$nodeType = $page['content']['system_main']['nodes'][$key]['#bundle'];
					}
				}
			}
            print uwwtd_wkhtmltopdf_tag(array('.main-container'), $options, $nodeType);
		?>     
		</div>    
        <?php print render($page['content']); ?>

    </div>
    <?php /* region--sidebar.tpl.php */ ?>
    <?php if ($page['sidebar_second']): ?>
      <?php print render($page['sidebar_second']); ?>
    <?php endif; ?>

  </div>
</div>
<?php /* region--footer.tpl.php */ ?>
<?php print render($page['footer']); ?>