# GBC-emulator

A Game Boy Color emulator written in C++23.

## Building

Requires a C++23-capable compiler (GCC 13+, Clang 17+, MSVC 2022, or a recent Xcode), [Ninja](https://ninja-build.org/), and [vcpkg](https://github.com/microsoft/vcpkg).

One-time setup, if you don't already have vcpkg:

```sh
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

Then build with `make`:

```sh
make            # configure + build (debug)
make test       # build, then run the test suite
make run        # build, then launch gbcemu
```

Other targets: `make asan` (Debug + AddressSanitizer/UBSan), `make tidy` (Debug + clang-tidy, needs clang), `make format` / `make format-check`, `make clean` / `make distclean`. Run `make help` for the full list.

By default the `Makefile` points `VCPKG_ROOT` at `./vcpkg`. If your vcpkg checkout lives elsewhere, export `VCPKG_ROOT` yourself before running `make`.

### Without make

The `Makefile` is a thin wrapper around CMake presets; you can use those directly:

```sh
export VCPKG_ROOT=/path/to/vcpkg
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

Presets: `debug`, `release`, `asan`, `tidy`.

## Project layout

```
src/
  main.cpp
  cpu/         # SM83 CPU core
  memory/      # Memory bus / address decoding
  ppu/         # Picture processing unit
  cartridge/   # ROM loading, mappers
tests/         # Catch2 unit tests, mirrors src/ layout
```

Headers live next to their `.cpp` file (no separate `include/` tree). New source files must be added explicitly to the `add_executable`/`add_library` calls in `CMakeLists.txt` — there's no globbing.

## Tooling

- **CMake + Ninja** — build system, driven via `CMakePresets.json`. `Makefile` wraps the presets for a `make`/`make clean` workflow.
- **vcpkg** (manifest mode, `vcpkg.json`) — dependency management (SDL2, Catch2).
- **clang-format** / **clang-tidy** — formatting (Allman braces) and static analysis, configured in `.clang-format` / `.clang-tidy`.
- **Sanitizers** — ASan/UBSan/TSan toggled via CMake options (`GBCEMU_ENABLE_ASAN`, etc.), wired up in `cmake/Sanitizers.cmake`.
- **Catch2** — unit tests under `tests/`.
- **GitHub Actions** — CI runs formatting/tidy checks and a build+test matrix across compilers and platforms.
