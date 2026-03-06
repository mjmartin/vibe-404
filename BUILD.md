# Building Vibe404

Vibe404 uses [CMake](https://cmake.org) and [JUCE 8](https://juce.com). JUCE is downloaded
automatically on first configure — no manual SDK installation required.

---

## Prerequisites

| Tool | Minimum | Install |
|------|---------|---------|
| Xcode Command Line Tools | Xcode 15 / AppleClang 15 | `xcode-select --install` |
| CMake | 3.22 | `brew install cmake` |
| Ninja | any | `brew install ninja` |
| Git | any | included with Xcode CLT |

> **First configure** clones JUCE 8.0.12 (~300 MB) into `build/_deps/`. This is a one-time
> download cached locally; subsequent configures are instant.

---

## Quick Start (recommended — using CMake Presets)

CMake Presets provide named, reproducible build configurations. No need to memorise flags.

### Release build — universal binary (arm64 + x86_64)

```bash
cmake --preset macos-release
cmake --build --preset build-macos-release
```

Artefacts land in `build-release/plugin/Vibe404Synth_artefacts/Release/`.

### Debug build — universal binary

```bash
cmake --preset macos-debug
cmake --build --preset build-macos-debug
```

Artefacts land in `build/plugin/Vibe404Synth_artefacts/Debug/`.

### Fast iteration — Apple Silicon only (arm64, skips cross-compilation)

```bash
cmake --preset macos-arm64-debug
cmake --build --preset build-macos-arm64-debug
```

### Intel / Rosetta testing — x86_64 only

```bash
cmake --preset macos-x86-debug
cmake --build --preset build-macos-x86-debug
```

List all available presets:

```bash
cmake --list-presets
```

---

## Manual Configure (without presets)

If you prefer not to use presets:

```bash
# Universal Release
cmake -S . -B build-release \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
      -DCMAKE_OSX_DEPLOYMENT_TARGET=11.0

cmake --build build-release --parallel
```

```bash
# Debug, native architecture only
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

---

## Build Targets

You can build individual formats instead of everything:

```bash
# Using presets (configure first, then target a specific format)
cmake --build --preset build-macos-release --target Vibe404Synth_VST3
cmake --build --preset build-macos-release --target Vibe404Synth_AU
cmake --build --preset build-macos-release --target Vibe404Synth_Standalone
```

| Target | Output |
|--------|--------|
| `Vibe404Synth_VST3` | `Vibe404.vst3` — for Ableton, Bitwig, Reaper, Cubase |
| `Vibe404Synth_AU` | `Vibe404.component` — for Logic Pro, GarageBand, MainStage |
| `Vibe404Synth_Standalone` | `Vibe404.app` — runs without a DAW |

---

## Artefact Locations

| Config | Path |
|--------|------|
| Release | `build-release/plugin/Vibe404Synth_artefacts/Release/` |
| Debug | `build/plugin/Vibe404Synth_artefacts/Debug/` |

Each config directory contains `VST3/`, `AU/`, and `Standalone/` subdirectories.

---

## Universal Binary

The `macos-release` and `macos-debug` presets set `CMAKE_OSX_ARCHITECTURES="arm64;x86_64"`,
producing a [universal binary](https://developer.apple.com/documentation/apple-silicon/building-a-universal-macos-binary)
that runs natively on both Apple Silicon and Intel Macs.

To verify after building:

```bash
lipo -info build-release/plugin/Vibe404Synth_artefacts/Release/VST3/Vibe404.vst3/Contents/MacOS/Vibe404
# Expected: Architectures in the fat file: ... are: x86_64 arm64
```

---

## Debug vs Release

| | Debug | Release |
|-|-------|---------|
| Compile time | Fast | Slower (LTO enabled) |
| Runtime performance | Unoptimised | Fully optimised |
| Recommended for | Development | Distribution |

---

## Windows

> **Coming soon.** Windows (x86_64, VST3 + Standalone) support is planned. The CMake build
> system is already cross-platform; Windows-specific presets and instructions will be added
> in a future release.

---

## Troubleshooting

**`ninja: command not found`** — install Ninja (`brew install ninja`) or switch to a
different generator by adding `-G "Unix Makefiles"` to the configure command.

**`CMake Error: CMAKE_C_COMPILE_OBJECT is not set`** — ensure `LANGUAGES C CXX` is present
in the root `CMakeLists.txt`. JUCE's graphics module bundles a C99 library and requires a C
compiler even for a C++ project.

**JUCE download fails** — check internet connectivity. The FetchContent step clones from
`github.com/juce-framework/JUCE`. If behind a proxy, set `HTTPS_PROXY` before configuring.

**AU not showing in Logic after install** — see [INSTALL.md](INSTALL.md) for rescan
instructions.
