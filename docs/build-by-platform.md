# Build By Platform

## Windows (MSVC Preset)

```powershell
cmake --preset msvc
cmake --build --preset build-msvc-release
```

Executables are usually in `build/msvc/Release/`.

## Windows (MinGW Preset)

```powershell
cmake --preset mingw
cmake --build --preset build-mingw-release
```

The MinGW preset expects `gcc` and `g++` on `PATH`.

## Linux

```bash
cmake -S . -B build
cmake --build build -j
```

## macOS

```bash
cmake -S . -B build
cmake --build build -j
```

## Headless Smoke Run

For non-interactive environments, disable the GUI window and save output:

```bash
./build/ou_tutorial --save ou_tutorial.png --no-show
./build/minimal_plot --save minimal_plot.png --no-show
```
