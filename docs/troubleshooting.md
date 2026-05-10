# Troubleshooting

## CMake cannot find Python3

Error often looks like: `Could NOT find Python3`.

Fixes:

1. Ensure Python is installed and available on `PATH`.
2. Confirm imports work:
   - `python3 -c "import numpy, matplotlib"`
   - `py -c "import numpy, matplotlib"` (Windows)
3. Reconfigure CMake from a clean build directory.

## CMake finds Python but fails on NumPy

Install NumPy in the same Python environment discovered by CMake:

- `python3 -m pip install numpy`
- `py -m pip install numpy`

If multiple Pythons are installed, point CMake explicitly:

```bash
cmake -S . -B build -DPython3_EXECUTABLE=/path/to/python3
```

## Program runs but no plot window appears

On headless or remote sessions, use save mode:

```bash
./build/ou_tutorial --save ou_tutorial.png --no-show
```

Set Matplotlib backend for headless runs when needed:

```bash
export MPLBACKEND=Agg
```

PowerShell:

```powershell
$env:MPLBACKEND = "Agg"
```

## Windows runtime error: `No module named encodings`

This can happen with embedded Python when the runtime cannot resolve its standard
library paths.

The executables now attempt to set `PYTHONHOME` and `PYTHONPATH` automatically
from the CMake-discovered Python interpreter. If the error still occurs, use the
manual override below.

Try launching from a shell where Python is already activated and set
`PYTHONHOME` to your Python install root before running the executable.

Example (PowerShell):

```powershell
$env:PYTHONHOME = "C:\\Users\\<you>\\anaconda3"
$env:PYTHONPATH = "$env:PYTHONHOME\\Lib;$env:PYTHONHOME\\DLLs"
.\build\Release\minimal_plot.exe --save minimal_plot.png --no-show
```

If this still fails, prefer running from a regular python.org installation or
using the Linux workflow for headless smoke validation.

## MinGW preset fails on compiler detection

The preset expects `gcc` and `g++` in `PATH`.

Verify:

```powershell
gcc --version
g++ --version
```

If not found, install MinGW and update `PATH`, or use the MSVC preset.
