# Dependencies

## Runtime and Build Dependencies

- C++20 compiler
- CMake 3.20+
- Python 3 with development headers
- NumPy
- Matplotlib

## Tested Matrix

The table below captures currently validated combinations.

| Area | Tested Value | Evidence |
| --- | --- | --- |
| CMake | 3.20+ | Project minimum in `CMakeLists.txt` and CI configure |
| C++ standard | C++20 | Project compile standard in `CMakeLists.txt` |
| Python (CI) | 3.11 | `.github/workflows/build.yml` (`actions/setup-python`) |
| Python (local validation) | 3.9.7 | Local configure output during implementation |
| NumPy | Installed via pip in CI | `.github/workflows/build.yml` |
| Matplotlib | Installed via pip in CI | `.github/workflows/build.yml` |
| Windows build | Visual Studio 2022 generator | CI + local build validation |
| Linux build | Ubuntu latest runner | CI build + headless smoke run |

## Embedded Plotting Stack

The project uses a header-only C++ wrapper:

1. `ou_tutorial` / `minimal_plot` (C++)
2. `third_party/matplotlibcpp.h` (`matplotlib-cpp`)
3. Python runtime
4. NumPy + Matplotlib Python packages

## Version Guidance

A practical compatibility target for this tutorial is:

- Python 3.9+
- NumPy 1.23+
- Matplotlib 3.6+

If your environment differs, validate with the minimal plot example first.

## Validation Commands

Use these commands as a quick compatibility check:

```bash
cmake -S . -B build
cmake --build build --config Release
```

Headless runtime check:

```bash
./build/minimal_plot --save minimal_plot.png --no-show
./build/ou_tutorial --save ou_tutorial.png --no-show
```
