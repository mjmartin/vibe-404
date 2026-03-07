# Installing Vibe404

Vibe404 is distributed as:

| Format | File | Compatible DAWs |
|--------|------|-----------------|
| **VST3** | `Vibe404.vst3` | Ableton Live, Bitwig Studio, Reaper, Cubase, Studio One |
| **Audio Unit (AU)** | `Vibe404.component` | Logic Pro, GarageBand, MainStage |
| **Standalone** | `Vibe404.app` | No DAW required |

Build the plugin first — see [BUILD.md](BUILD.md).

---

## macOS

### VST3

Copy the bundle to the system VST3 folder:

```bash
cp -r build-release/plugin/Vibe404Synth_artefacts/Release/VST3/Vibe404.vst3 \
      ~/Library/Audio/Plug-Ins/VST3/
```

Most DAWs detect new VST3 plugins automatically on next launch. If yours does not, trigger
a manual rescan (see DAW-specific notes below).

### Audio Unit (AU)

Copy the component bundle to the AU Components folder:

```bash
cp -r build-release/plugin/Vibe404Synth_artefacts/Release/AU/Vibe404.component \
      ~/Library/Audio/Plug-Ins/Components/
```

Validate the AU after copying:

```bash
auval -v aumu Vi04 Vibe
```

A passing result ends with `* * PASS * *`. If it fails, re-copy and try again.

### Standalone

No installation needed. Double-click `Vibe404.app` to launch. For easy access, drag it
to your Applications folder or Dock.

```bash
# Optional: copy to Applications
cp -r build-release/plugin/Vibe404Synth_artefacts/Release/Standalone/Vibe404.app \
      /Applications/
```

---

## DAW-Specific Notes

### Logic Pro

Logic uses AU format (not VST3).

1. Copy `Vibe404.component` as above
2. Open Logic Pro
3. Go to **Logic Pro → Settings → Plug-in Manager**
4. Click **Reset & Rescan Selection** (or scan all)
5. Find Vibe404 under **Audio Units › Vibe › Vibe404**

If Logic quarantines the plugin on first use, click **Open** in the security dialog, or
pre-approve it:

```bash
xattr -dr com.apple.quarantine ~/Library/Audio/Plug-Ins/Components/Vibe404.component
```

### Ableton Live

Ableton uses VST3 format on macOS.

1. Copy `Vibe404.vst3` as above
2. Open Ableton Live
3. Go to **Live → Settings → Plug-Ins**
4. Ensure `~/Library/Audio/Plug-Ins/VST3` is listed under VST3 plug-in custom folder
5. Click **Rescan**
6. Vibe404 appears under **Instruments** in the browser

### Reaper

Reaper uses VST3 format on macOS.

1. Copy `Vibe404.vst3` as above
2. Open Reaper
3. Go to **Options → Preferences → Plug-ins → VST**
4. Click **Re-scan / find new plug-ins**
5. Insert Vibe404 via the FX browser

### Bitwig Studio

Bitwig uses VST3 format on macOS.

1. Copy `Vibe404.vst3` as above
2. Open Bitwig
3. Go to **Dashboard → Settings → Locations**
4. Ensure the VST3 folder is listed, then click **Rescan plug-ins**
5. Vibe404 appears in the Instruments browser

### Cubase / Nuendo

1. Copy `Vibe404.vst3` as above
2. Cubase rescans VST3 automatically on next launch
3. Find Vibe404 under **VST Instruments**

---

## Uninstalling

To remove Vibe404, delete the relevant files:

```bash
# VST3
rm -rf ~/Library/Audio/Plug-Ins/VST3/Vibe404.vst3

# Audio Unit
rm -rf ~/Library/Audio/Plug-Ins/Components/Vibe404.component

# Standalone (if copied to Applications)
rm -rf /Applications/Vibe404.app
```

After removing the AU, Logic will stop showing the plugin automatically on next launch.

---

## Windows

Build the plugin first — see the Windows section of [BUILD.md](BUILD.md).

### VST3

Copy the bundle to the standard VST3 folder (requires administrator privileges):

```cmd
xcopy /E /I build-release\plugin\Vibe404Synth_artefacts\Release\VST3\Vibe404.vst3 ^
      "%COMMONPROGRAMFILES%\VST3\Vibe404.vst3\"
```

Most DAWs scan this location automatically on next launch. If yours does not, trigger a
manual rescan from the DAW's plug-in settings.

### Standalone

No installation required. Copy `Vibe404.exe` to any convenient location and run it directly.

```cmd
copy build-release\plugin\Vibe404Synth_artefacts\Release\Standalone\Vibe404.exe ^
     "%PROGRAMFILES%\Vibe404\Vibe404.exe"
```

### DAW-Specific Notes (Windows)

**Ableton Live**
1. Copy `Vibe404.vst3` as above
2. Open Ableton Live → **Options → Preferences → Plug-Ins**
3. Ensure `C:\Program Files\Common Files\VST3` is listed under VST3 plug-in folder
4. Click **Rescan**; Vibe404 appears under **Instruments**

**Reaper**
1. Copy `Vibe404.vst3` as above
2. Open Reaper → **Options → Preferences → Plug-ins → VST**
3. Click **Re-scan / find new plug-ins**
4. Insert Vibe404 via the FX browser

**Bitwig Studio**
1. Copy `Vibe404.vst3` as above
2. Open Bitwig → **Dashboard → Settings → Locations**
3. Ensure the VST3 folder is listed, then click **Rescan plug-ins**
4. Vibe404 appears in the Instruments browser

**Cubase / Nuendo**
1. Copy `Vibe404.vst3` as above
2. Cubase rescans VST3 automatically on next launch
3. Find Vibe404 under **VST Instruments**

### Uninstalling (Windows)

```cmd
rmdir /S /Q "%COMMONPROGRAMFILES%\VST3\Vibe404.vst3"
```
