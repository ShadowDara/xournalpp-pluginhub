#!/usr/bin/env bash

set -e
set -o pipefail

# Current script directory (build/Windows)
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Project root directory: plugin-viewer
project_root="$(cd "$script_dir/../../plugin-viewer" && pwd)"

# Build directory
build_dir="$project_root/build"

# Install/Dist directory
setup_dir_name="dist"
setup_dir="$build_dir/$setup_dir_name"

prefix=${MSYSTEM_PREFIX:-/mingw64}

echo "[INFO] Project root: $project_root"
echo "[INFO] Build directory: $build_dir"
echo "[INFO] Install directory: $setup_dir"
echo "[INFO] MSYSTEM_PREFIX: $prefix"

# Cleanup
rm -rf "$setup_dir"
mkdir -p "$setup_dir/bin" "$setup_dir/lib" "$setup_dir/share"

# CMake configuration and build
echo "[INFO] Configuring CMake..."
cmake -S "$project_root" -B "$build_dir" -DCMAKE_BUILD_TYPE=Release

echo "[INFO] Building project..."
cmake --build "$build_dir" --config Release

echo "[INFO] Installing project..."
cmake --install "$build_dir" --prefix "$setup_dir"

# Check executable name (adjust if needed)
app_exe_name="app.exe"
app_exe_path="$setup_dir/bin/$app_exe_name"

if [[ ! -f "$app_exe_path" ]]; then
    echo "[ERROR] $app_exe_path not found!"
    echo "[HINT] Check if your CMakeLists.txt correctly produces 'app'!"
    exit 1
fi

# Copy required DLLs
echo "[INFO] Copying required DLLs..."
ldd "$app_exe_path" | grep -oE '([A-Za-z]:)?(/[^\ ]+)+\.dll' | sort -u | while read -r dll; do
    echo "  Copying $dll"
    cp -u "$dll" "$setup_dir/bin/"
done

# Starting
echo "[INFO] Starting the program"
start $setup_dir/bin/$app_exe_name

# ZIP archive
echo "[INFO] Creating ZIP archive..."
cd "$build_dir"
zip_file="app-windows.zip"
rm -f "$zip_file"
"$SEVENZ" a -tzip "$zip_file" "$setup_dir_name"/* > /dev/null

echo "[SUCCESS] Finished! Archive created at: $(realpath "$zip_file")"
