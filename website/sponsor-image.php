<?php
// sponsor-image.php - Serves sponsor images from derbynet-data directory
// Usage: sponsor-image.php?path=keg/sponsor-logo.png

// Support both Docker and local development paths
$allowed_base = '/var/lib/derbynet/sponsors/';
if (!is_dir($allowed_base)) {
    $allowed_base = '/Users/todd/derbynet-data/lib/sponsors/';
}

// Get the requested path
$path = isset($_GET['path']) ? $_GET['path'] : '';

// Security: prevent directory traversal
$path = str_replace('..', '', $path);
$path = ltrim($path, '/');

// Build full file path
$file_path = $allowed_base . $path;

// Check if file exists and is within allowed directory
$real_path = realpath($file_path);
if ($real_path === false || strpos($real_path, realpath($allowed_base)) !== 0) {
    header('HTTP/1.0 404 Not Found');
    exit('File not found');
}

// Check if file exists
if (!file_exists($real_path) || !is_file($real_path)) {
    header('HTTP/1.0 404 Not Found');
    exit('File not found');
}

// Get file extension and set content type
$ext = strtolower(pathinfo($real_path, PATHINFO_EXTENSION));
$content_types = array(
    'png' => 'image/png',
    'jpg' => 'image/jpeg',
    'jpeg' => 'image/jpeg',
    'gif' => 'image/gif',
    'svg' => 'image/svg+xml',
    'webp' => 'image/webp'
);

$content_type = isset($content_types[$ext]) ? $content_types[$ext] : 'application/octet-stream';

// Set headers
header('Content-Type: ' . $content_type);
header('Content-Length: ' . filesize($real_path));
header('Cache-Control: public, max-age=3600');

// Output the file
readfile($real_path);
?>
