# Contributing

Thanks for your interest in improving this tutorial.

## Development Requirements

- C++20 compiler
- CMake 3.20+
- Python 3 with development headers
- NumPy and Matplotlib

## Build

```powershell
cmake -S . -B build
cmake --build build --config Release
```

## Style Expectations

- Keep code readable and tutorial-friendly.
- Preserve strict warning cleanliness (`/W4` on MSVC, `-Wall -Wextra -Wpedantic` elsewhere).
- Prefer small, focused pull requests.

## Testing Expectations

Before opening a PR:

1. Build both executables.
2. Run `minimal_plot` with `--save` and `--no-show`.
3. Run `ou_tutorial` with `--save` and `--no-show`.

## Pull Request Guidance

- Explain what changed and why.
- Include relevant command output for build/run validation.
- Update docs when behavior or setup changes.
