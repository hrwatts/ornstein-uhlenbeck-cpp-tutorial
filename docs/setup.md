# Setup

This guide covers a minimal environment setup for Windows, Linux, and macOS.

## Common Requirements

- CMake 3.20+
- A C++20 compiler
- Python 3 (with development headers)
- NumPy
- Matplotlib

## Windows (PowerShell)

Python and packages:

```powershell
py -m pip install --upgrade pip
py -m pip install numpy matplotlib
```

Configure and build:

```powershell
cmake --preset msvc
cmake --build --preset build-msvc-release
```

## Linux (Ubuntu)

Install toolchain and Python headers:

```bash
sudo apt update
sudo apt install -y build-essential cmake python3 python3-dev python3-pip
python3 -m pip install --user --upgrade pip
python3 -m pip install --user numpy matplotlib
```

Configure and build:

```bash
cmake -S . -B build
cmake --build build -j
```

## macOS (Homebrew)

Install tooling:

```bash
brew install cmake python
python3 -m pip install --upgrade pip
python3 -m pip install numpy matplotlib
```

Configure and build:

```bash
cmake -S . -B build
cmake --build build -j
```

## Verify Python Environment

Run this check before CMake configuration if build discovery fails:

```bash
python3 -c "import numpy, matplotlib; print('ok')"
```

On Windows:

```powershell
py -c "import numpy, matplotlib; print('ok')"
```
