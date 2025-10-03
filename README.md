# SecureFileTransfer

A minimal Qt6 C++ example demonstrating a GUI client/server file transfer with a simple XOR encryption.

This repository contains a cross-platform Qt6 project (QtCore, QtNetwork, QtWidgets). Below are platform-specific build instructions and the commands to push the project to GitHub.

Quick build (generic):

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Run the application (from the build directory):

Linux/macOS:
```bash
./SecureFileTransfer
```
Windows (MSYS2 Mingw64 shell):
```bash
./SecureFileTransfer.exe
```

Platform-specific setup
-----------------------

Windows (MSYS2 / MinGW-w64) - (no Visual Studio)
- Install MSYS2 (https://www.msys2.org) or via winget:
	```powershell
	winget install --id=MSYS2.MSYS2 -e
	```
- Open the "MSYS2 MinGW 64-bit" shell (important — use MinGW64 environment).
- Update packages and install toolchain, CMake and Qt6:
	```bash
	pacman -Syu
	# reopen MSYS2 MinGW64 shell if core updated
	pacman -Su
	pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-qt6 mingw-w64-x86_64-qt6-tools
	```
- Build and run (in MSYS2 MinGW64 shell):
	```bash
	mkdir -p build && cd build
	cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=/mingw64
	mingw32-make -j$(nproc)
	./SecureFileTransfer.exe
	```
- Deploy:
	```bash
	/mingw64/bin/windeployqt.exe SecureFileTransfer.exe
	```

macOS (Homebrew)
- Install Homebrew (https://brew.sh) if needed.
- Install CMake and Qt6 via Homebrew:
	```bash
	brew install cmake
	brew install qt@6
	```
- Configure and build:
	```bash
	mkdir build && cd build
	cmake .. -DCMAKE_PREFIX_PATH="$(brew --prefix qt@6)"
	cmake --build . --config Release
	./SecureFileTransfer
	```
	If CMake cannot find Qt: set
	```bash
	cmake .. -DQt6_DIR="$(brew --prefix qt@6)/lib/cmake/Qt6"
	```

Linux (Debian/Ubuntu and distro-agnostic notes)
- Install a C++ toolchain and CMake. On Debian/Ubuntu:
	```bash
	sudo apt update
	sudo apt install build-essential cmake qt6-base-dev qt6-network-dev libqt6widgets6
	```
	Package names vary by distribution. If your distro provides Qt6 packages via package manager, install Qt6 base and network modules (qt6-base, qt6-network).
- Build:
	```bash
	mkdir build && cd build
	cmake ..
	cmake --build .
	./SecureFileTransfer
	```

Pushing to GitHub (how to add remote and push)
------------------------------------------------
I did not push to any remote automatically. To push this repository to GitHub, create a repository on GitHub and then run (replace the URL below with your repository URL):

```bash
# from the project root
git init
git config user.name "Your Name"
git config user.email "you@example.com"
git add .
git commit -m "Initial SecureFileTransfer Qt6 project"
git branch -M main
git remote add origin <YOUR_GIT_REMOTE_URL>
git push -u origin main
```

If you'd like, provide me with the remote URL and I can add the remote and push from this environment for you.

Notes
-----
- This is a demo project with a simple XOR cipher for demonstration purposes only — not secure for production use.
- For large file transfers in production, consider moving file I/O off the GUI thread and using a secure encryption library (e.g., OpenSSL or libsodium) instead of XOR.
