# TODO

## Platform Support

- [ ] **Windows x86_64** — VST3 + Standalone formats
  - The CMake build system is already cross-platform; JUCE handles the Windows target
  - Needs: Windows CI (GitHub Actions `windows-latest`), MSVC or Clang-cl toolchain
  - Needs: code-signing with an Authenticode certificate for SmartScreen compatibility
  - AU is macOS-only and will not be ported

## Plugin Formats

- [ ] **LV2** — the standard open plugin format for Linux DAWs
  - LV2 is the modern successor to LADSPA (LADSPA v1 is legacy; LV2 is what current
    hosts use: Ardour, Carla, Reaper on Linux, Qtractor)
  - JUCE 8 has built-in LV2 support — adding `LV2` to `FORMATS` in `juce_add_plugin`
    is the main change; a `.lv2` bundle with TTL metadata is generated automatically
  - Target install path: `~/.lv2/` (user) or `/usr/lib/lv2/` (system)
  - Depends on Linux platform support being added first (see above)

## Mobile Platforms (longer term)

- [ ] **iOS / iPadOS** — AUv3 instrument plugin + standalone app
  - AUv3 is the only supported plugin format on iOS; it runs in-process inside a host
    (GarageBand, AUM, Cubasis, Audiobus)
  - JUCE supports iOS targets; requires Xcode, an Apple Developer account, and an
    iOS-specific UI layout (touch targets, no right-click, adaptive screen sizes)
  - Build target: `Vibe404Synth_AUv3` (add `AUv3` to `FORMATS` in `juce_add_plugin`)
  - Standalone target becomes a full iPhone/iPad app distributable via the App Store
  - UI will need a touch-friendly redesign (larger knobs, gesture-based control)

- [ ] **Android** — standalone instrument app
  - No standard plugin format on Android (AAX/VST/LV2 are not supported by Android DAWs
    in the same way); primary target is a standalone synthesizer app
  - JUCE supports Android via the Android NDK; requires Android Studio and NDK setup
  - MIDI input via Android MIDI API (API level 23+) or USB-MIDI
  - Audio via AAudio (low-latency, API level 26+) — JUCE selects this automatically
  - Distributable via Google Play Store

## Other Ideas

- [ ] Preset browser (save / load named patches)
- [ ] Full MPE support (per-note pitch bend, pressure, slide beyond legacy MIDI mode)
- [ ] Resizable UI (JUCE `setResizable` + proportional layout)
- [ ] MIDI learn for knobs and buttons
