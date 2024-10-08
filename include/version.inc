<?php
/* The format is:
 * array(
 *     "major release number" => array(
 *         "release" => array(
 *             "source/windows" => array(
 *                 "filename" => "filename.tar.bz2",
 *                 "name"     => "package name",
 *                 "sha256"   => "shasum -256",
 *                 "date"     => "this files release date",
 *                 "note"     => "this file was updated 29feb due to broken phar files..",
 *             ),
 *             "announcement" => "bool, release announcement exists in releases/?",
 *         ),
 *     ),
 * );
 */
$RELEASES = (function () {
    $data = [];

    /* PHP 8.3 Release */
    $data['8.3'] = [
        'version' => '8.3.11',
        'date' => '29 Aug 2024',
        'tags' => [], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz' => 'b93a69af83a1302543789408194bd1ae9829e116e784d578778200f20f1b72d40',
            'tar.bz2' => '6640e2455080a89adc41d4e57bb04f8c2bfb7eec627fe199af973bff34d7f0ee',
            'tar.xz' => 'b862b098a08ab9bf4b36ed12c7d0d9f65353656b36fb0e3c5344093aceb35802',
        ]
    ];

    /* PHP 8.2 Release */
    $data['8.2'] = [
        'version' => '8.2.23',
        'date' => '29 Aug 2024',
        'tags' => [], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz' => 'f5cb5f0e063bcc632c60a8f26af63b19d5f924f1fc54b4471d88cfaa865d6917',
            'tar.bz2' => 'f7c90cda7a3c1de01f3bfb7b469d52dec9eba2f3b83320836004f9c2eecae26b',
            'tar.xz' => '81c5ae6ba44e262a076349ee54a2e468638a4571085d80bff37f6fd308e1d8d5',
        ]
    ];

    /* PHP 8.1 Release */
    $data['8.1'] = [
        'version' => '8.1.29',
        'date' => '06 Jun 2024',
        'tags' => ['security'], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz' => '8b2609bf1d3173aa38269a9af21532c65f730aadd3051f9aae011eea9e246de5',
            'tar.bz2' => '87a60313263f2f533f180e719272ca5e47cd9884d4ec3c93720198eaffae0827',
            'tar.xz' => '288884af60581d4284baba2ace9ca6d646f72facbd3e3c2dd2acc7fe6f903536',
        ]
    ];

    $ret = [];
    foreach ($data as $release) {
        $version = $release['version'];
        [$major] = explode('.', $version, 2);

        $info = [
            'announcement' => $release['announcement'] ?? true,
            'tags' => $release['tags'],
            'date' => $release['date'],
            'source' => [],
        ];
        foreach ($release['sha256'] as $format => $hash) {
            $info['source'][] = [
                'filename' => "php-{$version}.{$format}",
                'name' => "PHP {$version} ({$format})",
                'sha256' => $hash,
                'date' => $release['date'],
            ];
        }
        $ret[$major][$version] = $info;
    }
    return $ret;
})();

// Get latest release version and info.
function release_get_latest() {
    global $RELEASES;

    $version = '0.0.0';
    $current = null;
    foreach ($RELEASES as $versions) {
        foreach ($versions as $ver => $info) {
            if (version_compare($ver, $version) > 0) {
                $version = $ver;
                $current = $info;
            }
        }
    }

    return [$version, $current];
}
