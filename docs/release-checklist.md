# Release Checklist

Use this checklist before public announcements, blog submissions, or repository
showcase posts.

## Legal And Compliance

- [ ] `LICENSE` is present and correct.
- [ ] Third-party attribution is up to date in `ATTRIBUTION.md`.
- [ ] Vendored dependency license terms are still valid for current versions.

## Build And Runtime Validation

- [ ] CI is green on all configured platforms.
- [ ] `ou_tutorial` builds and runs in headless mode.
- [ ] `minimal_plot` builds and runs in headless mode.
- [ ] Plot images are generated during smoke checks.

## Documentation Quality

- [ ] `README.md` reflects current scope, requirements, and commands.
- [ ] `docs/setup.md` works on Windows/Linux/macOS.
- [ ] `docs/troubleshooting.md` includes known runtime failures and fixes.
- [ ] `docs/dependencies.md` version guidance matches tested environments.

## Repository Hygiene

- [ ] `.gitignore` excludes platform build outputs and local IDE state.
- [ ] `CHANGELOG.md` includes current release notes.
- [ ] `CONTRIBUTING.md` reflects current contribution and validation steps.

## Editorial Readiness

- [ ] README includes clear audience and scope.
- [ ] Example output expectation is described.
- [ ] Release date and version are clear and consistent.
