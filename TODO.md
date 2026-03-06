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

## Other Ideas

- [ ] Preset browser (save / load named patches)
- [ ] Full MPE support (per-note pitch bend, pressure, slide beyond legacy MIDI mode)
- [ ] Resizable UI (JUCE `setResizable` + proportional layout)
- [ ] MIDI learn for knobs and buttons
