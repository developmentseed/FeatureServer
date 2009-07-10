<?php print "<?xml version='1.0' encoding='utf-8'?>" ?>

<?php if (count($releases)): ?>
<project xmlns:dc="http://purl.org/dc/elements/1.1/">
  <title><?php print $project['title'] ?></title>
  <short_name><?php print $project['short_name'] ?></short_name>
  <api_version><?php print $project['api_version'] ?></api_version>

  <recommended_major><?php print $project['major'] ?></recommended_major>
  <supported_majors><?php print $project['major'] ?></supported_majors>
  <default_major><?php print $project['major'] ?></default_major>

  <project_status>1</project_status>

  <link><?php print $project['link'] ?></link>

  <releases>
    <?php foreach ($releases as $release): ?>
    <release>
      <name><?php print $release['name'] ?></name>
      <version><?php print $release['version'] ?></version>
      <tag></tag>
      <version_major><?php print $release['version_major'] ?></version_major>
      <version_patch><?php print $release['version_patch'] ?></version_patch>
      <version_extra><?php print $release['version_extra'] ?></version_extra>

      <status>published</status>

      <release_link><?php print $release['release_link'] ?></release_link>
      <download_link><?php print $release['download_link'] ?></download_link>
      <date><?php print $release['date'] ?></date>
      <mdhash><?php print $release['mdhash'] ?></mdhash>
      <filesize><?php print $release['filesize'] ?></filesize>
    </release>
    <?php endforeach; ?>
  </releases>
</project>
<?php else: ?>
<error><?php print t('The specified URL is not a valid project feed.') ?></error>
<?php endif; ?>
