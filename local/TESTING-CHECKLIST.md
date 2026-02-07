# Pintwood Derby Testing Checklist

## Testing Session: {{ DATE }}

Your local DerbyNet is running at: **http://localhost**

---

## Part 1: Themed Public Pages

These pages should have the Pintwood Derby dark theme applied.

### ✅ Already Themed (from recent commits)

#### 1. Index Page - `http://localhost/`
- [ ] Pintwood header displays (logo + "Monon District Pintwood Derby")
- [ ] Both title sponsors display in header (Half Liter BBQ + Cityscape Residential)
- [ ] Dark theme applied (dark background, citrine/sapphire colors)
- [ ] Page title "Welcome" shows in header
- [ ] Footer with sponsors displays at bottom (if any non-title sponsors)
- [ ] Buttons hidden when not logged in (per config)
- [ ] Mobile responsive (test by resizing browser)

**Notes:**
```
[Add any issues or observations here]
```

---

#### 2. Login Page - `http://localhost/login.php`
- [ ] Pintwood header displays
- [ ] Both title sponsors display
- [ ] Dark theme applied
- [ ] Login form is visible and styled
- [ ] "Login" page title shows in header
- [ ] Footer displays
- [ ] Form inputs readable with dark theme

**Notes:**
```
[Add any issues or observations here]
```

---

#### 3. Racer Results - `http://localhost/racer-results.php`
- [ ] Pintwood header displays
- [ ] Both title sponsors display
- [ ] Dark theme applied
- [ ] Results display readable with dark background
- [ ] Footer displays
- [ ] Text contrast is good (readable)

**Notes:**
```
[Add any issues or observations here]
```

---

#### 4. Slideshow - `http://localhost/slideshow.php`
- [ ] Pintwood header displays
- [ ] Both title sponsors display
- [ ] Dark theme applied
- [ ] Slideshow controls visible
- [ ] Footer displays
- [ ] Suitable for display on big screen

**Notes:**
```
[Add any issues or observations here]
```

---

### ⚠️ Not Yet Themed (need to apply)

#### 5. Main Kiosk - `http://localhost/kiosk.php`
- [ ] Check if theme is applied
- [ ] If not, needs modification

**Current Status:** NEEDS THEME

---

#### 6. Sponsor Kiosk - `http://localhost/sponsors.kiosk.php`
- [ ] Full screen sponsor rotation
- [ ] All sponsors display with correct tier labels
- [ ] Rotation works (5 second intervals)
- [ ] ESC key exits (if applicable)
- [ ] Logos scale properly

**Current Status:** CHECK IF EXISTS

---

#### 7. On Deck - `http://localhost/ondeck.php`
- [ ] Check if theme is applied
- [ ] Shows upcoming racers
- [ ] Readable on kiosk display

**Current Status:** NEEDS THEME

---

#### 8. Now Racing - `http://localhost/now-racing.php`
- [ ] Check if theme is applied
- [ ] Shows current heat
- [ ] Updates in real-time (if racing)
- [ ] Suitable for spectator display

**Current Status:** NEEDS THEME

---

#### 9. Awards - `http://localhost/awards.php`
- [ ] Check if theme is applied
- [ ] Award display formatting
- [ ] Suitable for ceremony display

**Current Status:** NEEDS THEME

---

## Part 2: Admin/Coordinator Pages

These should NOT have the dark theme (should use default DerbyNet style).

### Coordinator Dashboard - `http://localhost/coordinator.php`
- [ ] Default DerbyNet theme (NOT Pintwood dark theme)
- [ ] All coordinator functions accessible
- [ ] Can navigate to sub-pages
- [ ] Timer controls visible (if timer connected)

**Login with:** [Check /Users/todd/derbynet/testing/default.passwords]

**Notes:**
```
[Add any issues or observations here]
```

---

### Checkin Page - `http://localhost/checkin.php`
- [ ] Default theme (not Pintwood)
- [ ] Can search for racers
- [ ] Checkin buttons work
- [ ] Photo upload works (if testing)

**Notes:**
```
[Add any issues or observations here]
```

---

### Results Entry - `http://localhost/coordinator.php` → Race Controls
- [ ] Default theme
- [ ] Can enter race results
- [ ] Timer integration (if testing with hardware)
- [ ] Results save properly

**Notes:**
```
[Add any issues or observations here]
```

---

### Settings/Setup - `http://localhost/settings.php`
- [ ] Default theme
- [ ] Can modify settings
- [ ] Database configuration accessible
- [ ] Role management works

**Notes:**
```
[Add any issues or observations here]
```

---

## Part 3: Sponsor Display Testing

### Title Sponsors (Header)
- [ ] Half Liter BBQ logo displays
- [ ] Cityscape Residential logo displays
- [ ] Both logos properly sized (6rem)
- [ ] Logos side-by-side with gap
- [ ] Logos visible on all themed pages

**Logo URLs to test:**
- `http://localhost/sponsor-image.php?path=keg/half-liter.png`
- `http://localhost/sponsor-image.php?path=keg/CityScape-logo.png`

**Notes:**
```
[Add any issues or observations here]
```

---

### Footer Sponsors
- [ ] Footer appears on all themed pages
- [ ] Fixed to bottom of page
- [ ] Growler tier logos display (if any)
- [ ] Liter tier logos display (if any)
- [ ] Pint tier logos display (if any)
- [ ] Horizontal layout with proper spacing

**Current sponsors in footer:** NONE (all tiers empty)

**Notes:**
```
[Add any issues or observations here]
```

---

## Part 4: Mobile/Responsive Testing

Test on phone or by resizing browser window to ~400px width.

### Mobile View
- [ ] Header adapts to narrow screen
- [ ] Logos stack or shrink appropriately
- [ ] Text remains readable
- [ ] Buttons/links are touch-friendly
- [ ] Footer doesn't overlap content
- [ ] Navigation works on mobile

**Test URLs on phone:**
- Main: `http://YOUR_MAC_IP/`
- Results: `http://YOUR_MAC_IP/racer-results.php`

**Find your Mac IP:**
```bash
ipconfig getifaddr en0
```

**Notes:**
```
[Add any issues or observations here]
```

---

## Part 5: Cross-Browser Testing

Test in multiple browsers to ensure compatibility.

### Chrome/Chromium
- [ ] All themed pages display correctly
- [ ] Sponsors load
- [ ] Dark theme renders properly

### Safari
- [ ] All themed pages display correctly
- [ ] Sponsors load
- [ ] Dark theme renders properly

### Firefox (if available)
- [ ] All themed pages display correctly
- [ ] Sponsors load
- [ ] Dark theme renders properly

**Notes:**
```
[Add any issues or observations here]
```

---

## Part 6: Performance Testing

### Page Load Times
- [ ] Index loads quickly (< 2 seconds)
- [ ] Images load without delay
- [ ] No browser console errors
- [ ] Sponsor images serve quickly

**Check browser console:**
1. Open Developer Tools (F12)
2. Go to Console tab
3. Look for errors (red text)
4. Look for warnings (yellow text)

**Console Errors Found:**
```
[List any errors here]
```

---

## Issues Found

### Critical (Must fix before deployment)
```
1.
2.
3.
```

### Medium (Should fix)
```
1.
2.
3.
```

### Low (Nice to have)
```
1.
2.
3.
```

---

## Summary

**Date Tested:** ____________

**Pages Working Correctly:** ___ / 9

**Admin Functions Working:** ___ / 4

**Sponsor Display:** ✅ ⚠️ ❌ (circle one)

**Mobile Responsive:** ✅ ⚠️ ❌ (circle one)

**Ready for Deployment:** YES / NO

**Next Steps:**
```
1.
2.
3.
```

---

## Quick Reference

**Local Site:** http://localhost
**Find Mac IP:** `ipconfig getifaddr en0`
**Check Docker:** `docker ps`
**View Logs:** `docker logs dreamy_kepler`
**Restart Docker:** `docker restart dreamy_kepler`

**Default Login:** Check `/Users/todd/derbynet/testing/default.passwords`

**Sponsor Config:** `/Users/todd/derbynet-data/lib/sponsors.json`
**Theme Config:** `/Users/todd/derbynet-data/lib/pintwood-config.json`
