# Tutorial

## Overview

The repository demonstrates how to:

1. Define an Ornstein-Uhlenbeck process.
2. Approximate it with Euler-Maruyama time stepping.
3. Simulate multiple paths with Gaussian noise.
4. Plot those paths from C++ through `matplotlib-cpp`.

## The Process

The Ornstein-Uhlenbeck process satisfies

`dY_t = theta * (mu - Y_t) dt + sigma dW_t`

This is a standard mean-reverting stochastic differential equation. In finance, the same form is commonly used in the Vasicek interest-rate model.

## Discretization

For a step size `dt`, Euler-Maruyama updates the state as

`Y_{n+1} = Y_n + theta * (mu - Y_n) * dt + sigma * sqrt(dt) * Z_n`

where each `Z_n` is an independent standard normal draw.

The implementation in `src/main.cpp` uses this update directly.

## Parameters Used In The Example

- `path_count = 100`
- `step_count = 1000`
- `t_start = 0.0`
- `t_end = 10.0`
- `y0 = 0.0`
- `theta = 0.5`
- `mu = 0.0`
- `sigma = 0.05`

These values produce a visible but stable mean-reverting plot.

## Build Notes

`matplotlib-cpp` is a header-only C++ wrapper around Python's Matplotlib API. That means the repository needs:

- Python headers and libraries
- NumPy headers
- a working Matplotlib installation

The provided `CMakeLists.txt` uses `find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)` and links against the discovered Python targets.

## Toolchain Notes

The repository does not hardcode compiler installation paths. Toolchains are expected to be selected through CMake discovery, CMake presets, or a local `CMakeUserPresets.json` file.

For example:

- `msvc` uses the Visual Studio generator.
- `mingw` uses the MinGW Makefiles generator and expects `gcc` and `g++` on `PATH`.

If a local MinGW installation has moved, update the local shell environment or a local `CMakeUserPresets.json` file rather than committing an absolute path into the repository.

## Suggested Reading Order

For a first pass through the repository:

1. Read `README.md`.
2. Open `src/main.cpp`.
3. Build and run `minimal_plot` to verify plotting.
4. Run `ou_tutorial` and inspect the generated figure.

## Public-Facing Layout

The repository is organized to keep the tutorial materials prominent:

- `README.md` is the landing page.
- `docs/` contains the short conceptual walkthrough.
- `src/` contains the main example.
- `examples/` contains one small environment check.
- generated binaries and IDE state are excluded from version control.
