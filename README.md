# 3DS C++ Template (devkitPro + CMake) For Linux

Minimal template for building Nintendo 3DS homebrew using C++ and devkitPro.
Outputs a `.3dsx` file ready for the Homebrew Launcher.

> [!IMPORTANT]
> This template was made & tested on Linux, it is specifically made to be used with Linux + VSCode (or compatible forks)

---

## Requirements

- [devkitPro](https://devkitpro.org/) toolchain installed
- `DEVKITPRO` environment variable set

Verify:

```bash
echo $DEVKITPRO
```

Expected output:

```
/opt/devkitpro
```

---

## Build

```bash
./build.sh
```

Output will be in:

```
build/
```

Files generated:

- `.elf` → raw executable
- `.3dsx` → Homebrew Launcher format
- `.smdh` → metadata (icon, title, author)

---

## Running on 3DS

Copy the `.3dsx` file to your SD card:

```
/3ds/YourApp/YourApp.3dsx (or whatever other path you want to use)
```

Then launch it via the Homebrew Launcher.

---

## Project Structure

```
.
├── CMakeLists.txt
├── build.sh
├── src/
│   └── main.cpp
├── assets/
│   └── icon.png   (optional)
```

---

## Metadata Configuration

Edit in `CMakeLists.txt`:

```cmake
set(APP_NAME "3DS Template")
set(APP_DESCRIPTION "My first 3DS app")
set(APP_AUTHOR "Your Name")
```

This controls:

- Title shown on 3DS
- Description
- Author/publisher

---

## Icon (SMDH) Guidelines

To use a custom icon:

```cmake
ICON assets/icon.png
```

### Requirements:

- Format: PNG
- Recommended size: **48×48**
- Keep it simple (low detail)
- Avoid transparency-heavy images
- Bright, high-contrast colors work best

The 3DS uses a limited color format internally, so complex images may look bad.

---

## VSCode IntelliSense Setup

Use environment variables (to avoid hardcoding):

```json
"includePath": [
  "${workspaceFolder}/**",
  "${env:DEVKITPRO}/libctru/include",
  "${env:DEVKITPRO}/devkitARM/arm-none-eabi/include"
]
```

---

## Troubleshooting

### `3ds.h not found`

Make sure devkitPro env is loaded:

```bash
source /etc/profile.d/devkit-env.sh
```

---

### Build uses wrong compiler

Ensure CMake uses toolchain:

```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/cmake/3DS.cmake
```

---

## License

Use freely for your projects.
