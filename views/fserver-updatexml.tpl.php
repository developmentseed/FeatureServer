<?php print "<?xml version='1.0' encoding='utf-8'?>" ?>

<?php if (count($releases)): ?>
<project xmlns:dc="http://purl.org/dc/elements/1.1/">
  <title><?php print $project['title'] ?></title>
  <short_name><?php print $project['short_name'] ?></short_name>
  <api_version><?php print $project['api_version'] ?></api_version>

  <recommended_major><?php print $project['recommended_major'] ?></recommended_major>
  <supported_majors><?php print $project['supported_majors'] ?></supported_majors>
  <default_major><?php print $project['recommended_major'] ?></default_major>

  <project_status>1</project_status>

  <link><?php print $project['link'] ?></link>

  <terms>
    <term>
      <name>Projects</name>
      <value><?php print $project['type'] ?></value>
    </term>
  </terms>

  <releases>
    <?php foreach ($releases as $release): ?>

    <release>

      <name><?php print $release['name'] ?></name>
      <version><?php print $release['version'] ?></version>

      <version_major><?php print $release['version_major'] ?></version_major>
      <version_patch><?php print $release['version_patch'] ?></version_patch>
      <?php if (!empty($release['version_extra'])): ?><version_extra><?php print $release['version_extra'] ?></version_extra><?php endif; ?>

      <status>published</status>

      <release_link><?php print $release['release_link'] ?></release_link>
      <download_link><?php print $release['download_link'] ?></download_link>
      <date><?php print $release['date'] ?></date>
      <mdhash><?php print $release['mdhash'] ?></mdhash>
      <filesize><?php print $release['filesize'] ?></filesize>
      <?php if ($release['security']): ?><terms>
        <term>
          <name>Release type</name>
          <value>Security update</value>
        </term>
      </terms><?php endif; ?>

    </release>
    <?php endforeach; ?>

  </releases>
</project>
<?php else: ?>
<error><?php print t('The specified URL is not a valid project feed.') ?></error>
<?php endif; ?>
