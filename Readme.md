# MinGW (MSYS2) Setup + dbg.h Installation Guide

## 1. Install MSYS2

1. Download the installer from https://www.msys2.org and run it (default install path: `C:\msys64`).
2. After install finishes, it opens an MSYS2 terminal automatically. Close it — you don't need the plain MSYS2 shell for building.
3. From the Start Menu, open **"MSYS2 UCRT64"** specifically (not "MSYS2 MSYS" or "MSYS2 MINGW64"). This is the environment for a modern 64-bit toolchain.
4. Update the package database:
   ```bash
   pacman -Syu
   ```
   If it asks you to close the terminal and reopen, do so, then run `pacman -Syu` again.
5. Install the 64-bit GCC toolchain:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```
6. Add the compiler to your Windows PATH:
   - Press **Win**, search **"Environment Variables"**, open **"Edit the system environment variables"**.
   - Click **Environment Variables...**
   - Under **System variables** (or **User variables**), select **Path** → **Edit** → **New**.
   - Add: `C:\msys64\ucrt64\bin`
   - Click OK on all dialogs.
7. Open a **new** Command Prompt / PowerShell window (PATH changes need a fresh terminal) and verify:
   ```
   g++ -dumpmachine
   g++ --version
   ```
   `-dumpmachine` should print something like `x86_64-w64-mingw32` — confirming a 64-bit toolchain (not `i686-...`).

## 2. Uninstalling an old/wrong MinGW (if you have one)

1. Find it: `where g++` (shows the install path).
2. Check **Settings → Apps → Installed apps** for an uninstaller (e.g. TDM-GCC has one).
3. If there's no uninstaller, just delete the folder: `rmdir /s /q C:\path\to\old\mingw`.
4. Remove its `bin` folder from PATH (same Environment Variables screen as above).
5. Open a new terminal and confirm `where g++` no longer finds it.

## 3. Place `dbg.h`

Put the file at:
```
C:\msys64\ucrt64\include\algo\dbg.h
```

From the UCRT64 terminal:
```bash
mkdir -p /ucrt64/include/algo
cp /path/to/dbg.h /ucrt64/include/algo/dbg.h
```

This makes `#include <algo/dbg.h>` resolve from any project with no extra `-I` flag needed, since `ucrt64/include` is already a default system include path for this toolchain.

## 4. Precompile `dbg.h` (faster builds)

Precompiling turns the (large) `<bits/stdc++.h>` pull-in inside `dbg.h` into a cached binary form, so g++ doesn't reparse it every build.

From the UCRT64 terminal:
```bash
cd /ucrt64/include/algo
g++ -std=c++23 -x c++-header dbg.h -o dbg.h.gch
```

This creates `dbg.h.gch` right next to `dbg.h`. GCC automatically detects and uses it whenever it sees `#include <algo/dbg.h>` — no code changes or extra flags needed.

**Notes:**
- The `-std=c++23` used here must match the `-std=` flag in your actual build command (e.g. your Sublime build system). If you change that flag later, regenerate the `.gch` with the same flag, or it'll be silently ignored (falls back to normal parsing, just no speedup — never a hard error).
- Expect the `.gch` file to be large (~100–150MB) — that's normal, since it's precompiling the entire standard library header.
- Regenerate the `.gch` any time you edit `dbg.h`. A stale `.gch` is automatically ignored by GCC (no correctness risk, just loses the speedup).
- For the speedup to apply, `dbg.h` must be the first real include in your `.cpp` file (or behind identical `#ifdef` branches each time), e.g.:
  ```cpp
  #ifdef ONLINE_JUDGE
  #include <bits/stdc++.h>
  #define dbg(...)
  #else
  #include <algo/dbg.h>
  #endif
  using namespace std;
  ```