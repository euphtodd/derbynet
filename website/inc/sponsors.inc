<?php
// sponsors.inc - Sponsor management for Pintwood Derby
// This file provides functions to load and display sponsor information

function load_sponsors() {
    // First check in the website inc directory
    $config_file = __DIR__ . '/sponsors.json';
    
    // Also check in the data directory if not found
    if (!file_exists($config_file)) {
        // For Docker/production
        $config_file = '/var/lib/derbynet/sponsors.json';
    }
    
    // For local development on Mac
    if (!file_exists($config_file)) {
        $config_file = '/Users/todd/derbynet-data/lib/sponsors.json';
    }
    
    if (file_exists($config_file)) {
        $json = file_get_contents($config_file);
        return json_decode($json, true);
    }
    
    // Default configuration with corrected paths
    return array(
        'sponsors' => array(
            'keg' => array(),
            'growler' => array(),
            'liter' => array(),
            'pint' => array()
        ),
        'config' => array(
            // This path will be used in the browser, so it needs to be a web-accessible path
            'sponsor_base_path' => 'images/sponsors/',  // Changed to use relative path
            'logo_sizes' => array(
                'keg' => '200px',
                'growler' => '150px',
                'liter' => '120px',
                'pint' => '100px'
            )
        )
    );
}

function get_sponsor_path($logo) {
    $sponsor_data = load_sponsors();
    $base_path = $sponsor_data['config']['sponsor_base_path'];
    
    // Check if it's a full path or relative
    if (strpos($logo, '/') === 0 || strpos($logo, 'http') === 0) {
        return $logo;
    }
    
    return $base_path . $logo;
}

function render_title_sponsor() {
    $sponsor_data = load_sponsors();
    $keg_sponsors = $sponsor_data['sponsors']['keg'];
    
    if (empty($keg_sponsors)) {
        return '';
    }
    
    $sponsor = $keg_sponsors[0]; // Get first (and typically only) title sponsor
    $logo_path = get_sponsor_path($sponsor['logo']);
    $size = $sponsor_data['config']['logo_sizes']['keg'];
    
    $html = '<div class="title-sponsor">';
    if (!empty($sponsor['url'])) {
        $html .= '<a href="' . htmlspecialchars($sponsor['url']) . '" target="_blank">';
    }
    $html .= '<img src="' . htmlspecialchars($logo_path) . '" ';
    $html .= 'alt="' . htmlspecialchars($sponsor['name']) . '" />';
    if (!empty($sponsor['url'])) {
        $html .= '</a>';
    }
    $html .= '</div>';
    
    return $html;
}

function render_footer_sponsors() {
    $sponsor_data = load_sponsors();
    $html = '<div class="sponsor-footer">';
    $html .= '<div class="sponsor-container">';
    
    // Render sponsors by tier (excluding keg/title sponsor)
    $tiers = array('growler', 'liter', 'pint');
    
    foreach ($tiers as $tier) {
        if (!empty($sponsor_data['sponsors'][$tier])) {
            $html .= '<div class="sponsor-tier sponsor-' . $tier . '">';
            
            foreach ($sponsor_data['sponsors'][$tier] as $sponsor) {
                $logo_path = get_sponsor_path($sponsor['logo']);
                $size = $sponsor_data['config']['logo_sizes'][$tier];
                
                $html .= '<div class="sponsor-item">';
                if (!empty($sponsor['url'])) {
                    $html .= '<a href="' . htmlspecialchars($sponsor['url']) . '" target="_blank">';
                }
                $html .= '<img src="' . htmlspecialchars($logo_path) . '" ';
                $html .= 'alt="' . htmlspecialchars($sponsor['name']) . '" ';
                $html .= 'style="max-height: ' . $size . ';" />';
                if (!empty($sponsor['url'])) {
                    $html .= '</a>';
                }
                $html .= '</div>';
            }
            
            $html .= '</div>';
        }
    }
    
    $html .= '</div>';
    $html .= '</div>';
    
    return $html;
}

function get_all_sponsor_logos_json() {
    $sponsor_data = load_sponsors();
    $all_logos = array();
    
    foreach ($sponsor_data['sponsors'] as $tier => $sponsors) {
        foreach ($sponsors as $sponsor) {
            $all_logos[] = array(
                'tier' => $tier,
                'name' => $sponsor['name'],
                'logo' => get_sponsor_path($sponsor['logo']),
                'url' => isset($sponsor['url']) ? $sponsor['url'] : '',
                'size' => $sponsor_data['config']['logo_sizes'][$tier]
            );
        }
    }
    
    return json_encode($all_logos);
}

function render_kiosk_sponsor_data() {
    $sponsor_data = load_sponsors();
    return '<script>var sponsorData = ' . get_all_sponsor_logos_json() . '; ' .
           'var rotationInterval = ' . $sponsor_data['config']['kiosk_rotation_interval'] . ';</script>';
}
?>
