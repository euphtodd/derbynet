# Post-Event Notes — Pintwood Derby 2026
**Event**: Monon District Pintwood Derby
**Date**: February 21, 2026
**Venue**: Liter House, Indianapolis, IN
**Code snapshot**: git tag `race-2026-02-21`

---

## Infrastructure Summary

- **Hosting**: DigitalOcean droplet (Ubuntu 24.04, $6/mo plan, 1GB RAM / 1 CPU)
- **Stack**: Docker + `jeffpiazza/derbynet_server` image, Nginx reverse proxy, Let's Encrypt SSL
- **Domain**: `derby.indypintwoodderby.com` (A record → droplet IP, managed via Firebase/Google Domains)
- **Database**: SQLite (inside the container at `/opt/derbynet/data/lib/`)

---

## ⚠️ Before Destroying the Droplet

Download race data first:
```bash
scp -r root@YOUR_DROPLET_IP:/opt/derbynet/data/lib/ ~/Desktop/pintwood-derby-2026-results/
```
Then log into the web UI, export final standings and award reports as PDFs/CSVs.

---

## Credentials (change these for next year)

The following credentials were used for the 2026 event and are committed to `testing/default.passwords`:
- **RaceCoordinator**: `doyourbest`
- **RaceCrew**: `pwdcrew2026`
- **Photo**: `flashbulb`

These should be rotated before the next event. They are in a public(ish) repo — consider moving them out of version control entirely or to a separate private file.

---

## Customization Files (in `/local/`)

All Pintwood-specific customizations live in `website/` (integrated into the DerbyNet install) and are documented in `local/README - PWD.md`. Key files:

| File | Purpose |
|------|---------|
| `pintwood-theme.css` | Dark theme styles |
| `theme-selector.inc` | Applies theme to configured pages |
| `header.inc` / `footer.inc` | Pintwood branding |
| `sponsors.inc` | Sponsor display functions |
| `sponsors.json` | Sponsor config (also lives at `/var/lib/derbynet/` on server) |
| `pintwood-config.json` | Event config |
| `sponsors.kiosk.php` | Rotating sponsor kiosk page |

Sponsor logos (PNG files) live **only on the server** at `/opt/derbynet/data/lib/sponsors/`. Back these up too if you want to reuse them.

---

## What Worked Well

- Dark theme with Pintwood branding looked great on kiosk displays
- Sponsor kiosk (rotating full-screen display) worked well for TVs at the venue
- QR code page allowed spectators to easily pull up results on phones
- DigitalOcean droplet was reliable; no downtime on race day
- Mobile layout was usable for coordinators walking the track

---

## Known Issues / Things to Improve for Next Year

See GitHub issues filed after the event. High-level:

1. **Sponsor management is manual** — logos must be uploaded to the server by hand; no admin UI
2. **Database backup is manual** — no automated export or snapshot
3. **Passwords in the repo** — `testing/default.passwords` has real event credentials; should be gitignored or use a separate secrets file
4. **SSL cert renewal** — Let's Encrypt cert will expire in ~90 days; if droplet is destroyed, this is moot, but document for next year
5. **No automated deployment** — all deployment is manual `scp` + SSH; a simple deploy script would help

---

## Deployment Steps for 2027

See `local/DEPLOYMENT-GUIDE.md` — it's comprehensive. Key sequence:
1. Spin up fresh DigitalOcean droplet (Ubuntu 24.04)
2. Install Docker + Docker Compose
3. `scp` website files and sponsor logos to server
4. Set up Nginx reverse proxy + certbot SSL
5. Update DNS A record for `derby.indypintwoodderby.com`
6. Test all public pages before race day

Estimated setup time: ~1-2 hours.

---

## Upstream DerbyNet

This repo forks [jeffpiazza/derbynet](https://github.com/jeffpiazza/derbynet). The Pintwood customizations are layered on top. Before next year, consider rebasing on the latest upstream to pick up bug fixes:

```bash
git fetch upstream
git rebase upstream/master
# resolve any conflicts in customized files
```
