# Kiosk Pages Testing Checklist

## Testing Session: {{ DATE }}

Your local DerbyNet is running at: **http://localhost**

---

## Understanding Kiosk Pages

Kiosk pages are designed to be displayed on dedicated screens for spectators during the race. They should:
- Have the Pintwood theme applied (header with sponsors, dark background)
- Auto-update in real-time during racing
- Be suitable for large display screens
- Not require login or interaction

---

## 1. On Deck Kiosk

Shows the upcoming racers for the next heat.

### Test URL:
```
http://localhost/ondeck.php
```

### Or via kiosk router (if configured):
```
http://localhost/kiosk.php?page=kiosks/ondeck.kiosk
```

### Checklist:
- [ ] Pintwood header displays (logo + title sponsors)
- [ ] Dark theme applied
- [ ] Shows upcoming racers (if race is scheduled)
- [ ] Lane assignments visible
- [ ] Racer photos display (if configured)
- [ ] Page title "Racers On Deck" in header
- [ ] Footer with sponsors displays
- [ ] Suitable for kiosk display (large text, good contrast)

**Notes:**
```
[Add observations here]
```

**Screenshot:** (if needed)

---

## 2. Now Racing Kiosk

Shows the current heat being raced with live results.

### Test URL:
```
http://localhost/kiosk.php?page=kiosks/now-racing.kiosk
```

### Checklist:
- [ ] Pintwood header displays
- [ ] Dark theme applied
- [ ] Shows current heat information
- [ ] Lane numbers visible
- [ ] Racer names display
- [ ] Car numbers display
- [ ] Results appear after heat completes
- [ ] Place indicators show (1st, 2nd, 3rd, etc.)
- [ ] Lane colors display correctly (if configured)
- [ ] Page updates in real-time

**Notes:**
```
[Add observations here]
```

**Screenshot:** (if needed)

---

## 3. Award Presentations Kiosk

Shows award winners during award ceremony.

### Test URL:
```
http://localhost/kiosk.php?page=kiosks/award-presentations.kiosk
```

### Control Dashboard:
```
http://localhost/awards-presentation.php
```

### Checklist:
- [ ] Pintwood header displays
- [ ] Dark theme applied (if configured)
- [ ] Award name displays clearly
- [ ] Winner name displays
- [ ] Car number displays
- [ ] Racer photo displays (if available)
- [ ] Car photo displays (if available)
- [ ] Confetti animation works (optional)
- [ ] Footer displays
- [ ] Controlled from awards-presentation.php dashboard

**Notes:**
```
[Add observations here]
```

**Testing Steps:**
1. Open awards-presentation.php (requires coordinator login)
2. Select an award from the list
3. Check the reveal toggle
4. View the kiosk display on second screen/window

---

## 4. QR Code Kiosk

Displays a QR code for spectators to access results on their phones.

### Test URL:
```
http://localhost/kiosk.php?page=kiosks/qrcode.kiosk
```

### Configure from:
```
http://localhost/kiosk-dashboard.php
```

### Checklist:
- [ ] Pintwood header displays
- [ ] Dark theme applied
- [ ] QR code displays (if configured)
- [ ] QR code is large and scannable
- [ ] Title displays correctly
- [ ] Footer displays
- [ ] QR code can be scanned with phone
- [ ] QR code links to correct URL

**Notes:**
```
[Add observations here]
```

**To Configure QR Code:**
1. Go to kiosk-dashboard.php
2. Assign a kiosk to QR Code display
3. Set the URL (e.g., http://YOUR_IP/racer-results.php)
4. Set the title text

---

## 5. Sponsor Rotation Kiosk

Full-screen rotating sponsor display.

### Test URL:
```
http://localhost/sponsors.kiosk.php
```

### Checklist:
- [ ] Fullscreen display (no header, just sponsors)
- [ ] Dark background
- [ ] All sponsors display in rotation
- [ ] Title sponsors (Keg tier) display
- [ ] Growler tier sponsors display (if any)
- [ ] Liter tier sponsors display (if any)
- [ ] Pint tier sponsors display (if any)
- [ ] Sponsor name displays
- [ ] Sponsor tier label displays ("Title Sponsor", etc.)
- [ ] Logos are clear and properly sized
- [ ] Rotation timing is appropriate (5 seconds default)
- [ ] ESC key exits back to index (optional)
- [ ] No cursor visible (kiosk mode)

**Current Sponsors:**
- Keg: Half Liter BBQ, Cityscape Residential
- Growler: (none)
- Liter: (none)
- Pint: (none)

**Notes:**
```
[Add observations here]
```

---

## 6. Main Kiosk Router

Tests the kiosk.php router functionality.

### Test URL:
```
http://localhost/kiosk.php
```

### Checklist:
- [ ] Page loads without error
- [ ] Redirects to assigned kiosk page (if configured)
- [ ] Can manually load pages via ?page= parameter
- [ ] Kiosk registration works

**Notes:**
```
[Add observations here]
```

---

## Cross-Kiosk Features Testing

### Theme Consistency:
- [ ] All kiosks use same Pintwood header design
- [ ] All kiosks use same dark color scheme
- [ ] Sponsor logos consistent across pages
- [ ] Footer consistent where applicable

### Real-Time Updates:
- [ ] On Deck updates when next heat is scheduled
- [ ] Now Racing updates during active heat
- [ ] Awards updates when controlled from dashboard
- [ ] All updates happen without page refresh

### Browser Compatibility:
- [ ] Chrome/Chromium
- [ ] Safari
- [ ] Firefox (if available)

---

## Multi-Display Setup Testing

If you have multiple screens or windows available:

### Test Scenario:
1. **Screen 1:** Now Racing kiosk
2. **Screen 2:** On Deck kiosk
3. **Screen 3:** QR Code or Sponsors
4. **Laptop:** Coordinator dashboard

### Checklist:
- [ ] All kiosks update simultaneously
- [ ] No lag or delay between displays
- [ ] Network connection stable
- [ ] All displays readable from distance

**Notes:**
```
[Setup details and observations]
```

---

## Issues Found

### Critical (Must fix):
```
1.
2.
3.
```

### Medium (Should fix):
```
1.
2.
3.
```

### Low (Nice to have):
```
1.
2.
3.
```

---

## Summary

**Date Tested:** ____________

**Kiosk Pages Working:** ___ / 6

**Theme Applied Correctly:** YES / NO

**Real-Time Updates Working:** YES / NO / UNTESTED

**Ready for Race Day:** YES / NO

**Next Steps:**
```
1.
2.
3.
```

---

## Quick Reference

**Kiosk URLs:**
- On Deck: http://localhost/ondeck.php
- Now Racing: http://localhost/kiosk.php?page=kiosks/now-racing.kiosk
- Awards: http://localhost/kiosk.php?page=kiosks/award-presentations.kiosk
- QR Code: http://localhost/kiosk.php?page=kiosks/qrcode.kiosk
- Sponsors: http://localhost/sponsors.kiosk.php

**Admin URLs:**
- Kiosk Dashboard: http://localhost/kiosk-dashboard.php
- Awards Control: http://localhost/awards-presentation.php
- Coordinator: http://localhost/coordinator.php

**Find Mac IP for Phone Testing:**
```bash
ipconfig getifaddr en0
```

**Check Docker:**
```bash
docker ps
docker logs dreamy_kepler
```
