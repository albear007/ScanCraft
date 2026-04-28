# ScanCraft

A Qt6 desktop application for a 3D intranasal cavity scanner. Built at WashU McKelvey School of Engineering with Metaphase and Apta Pharma.

A motorized rig on a Raspberry Pi sweeps four cameras around the target via a stepper motor and an I²C camera multiplexer (`ScanCraft/scripts/metaboard.py`). Captures are fed into a COLMAP photogrammetry pipeline; reconstructed meshes are rendered live in the GUI via VTK.

## Stack

- **Qt6** (Widgets, Gui) — desktop GUI
- **VTK** (CommonCore, GUISupportQt, IOGeometry, IOPLY) — 3D mesh display
- **COLMAP** — structure-from-motion reconstruction
- **Raspberry Pi** + stepper motor + I²C camera multiplexer — image acquisition
- C++20, CMake (presets), VCPKG

## Build

```bash
git clone https://github.com/albear007/ScanCraft.git
cd ScanCraft
cmake --preset <ninja-multi|clang-multi|cl-multi|win64>
cmake --build --preset <preset>-release
```

VCPKG bootstraps Qt6 and VTK on first configure. COLMAP must be installed and discoverable on `PATH` (or via `VCPKG_ROOT/installed/<triplet>/bin`).

## Layout

- `ScanCraft/src/` — Qt + VTK GUI, photogrammetry pipeline controller
- `ScanCraft/scripts/metaboard.py` — RPi motor and camera control
- `CMakePresets.json` — cross-platform build presets

## License

MIT.
