#!/usr/bin/env bash

set -e
set -o pipefail

# Aktuelles Skriptverzeichnis (build/Windows)
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Projektverzeichnis: plugin-viewer
project_root="$(cd "$script_dir/../../plugin-viewer" && pwd)"

# Build-Verzeichnis
build_dir="$project_root/build"

# Install/Dist Verzeichnis
setup_dir_name="dist"
setup_dir="$build_dir/$setup_dir_name"

prefix=${MSYSTEM_PREFIX:-/mingw64}

echo "[INFO] Projektverzeichnis: $project_root"
echo "[INFO] Build-Verzeichnis: $build_dir"
echo "[INFO] Install-Verzeichnis: $setup_dir"
echo "[INFO] MSYSTEM_PREFIX: $prefix"

# Aufräumen
rm -rf "$setup_dir"
mkdir -p "$setup_dir/bin" "$setup_dir/lib" "$setup_dir/share"

# CMake-Konfiguration und Build
echo "[INFO] Konfiguriere CMake..."
cmake -S "$project_root" -B "$build_dir" -DCMAKE_BUILD_TYPE=Release

echo "[INFO] Baue Projekt..."
cmake --build "$build_dir" --config Release

echo "[INFO] Installiere Projekt..."
cmake --install "$build_dir" --prefix "$setup_dir"

# Executable-Name prüfen (ggf. anpassen)
app_exe_name="app.exe"
app_exe_path="$setup_dir/bin/$app_exe_name"

if [[ ! -f "$app_exe_path" ]]; then
    echo "[ERROR] $app_exe_path nicht gefunden!"
    echo "[TIPP] Prüfe, ob dein CMakeLists.txt 'app' korrekt erzeugt!"
    exit 1
fi

# DLLs kopieren
echo "[INFO] Kopiere benötigte DLLs..."
ldd "$app_exe_path" | grep -oE '([A-Za-z]:)?(/[^\ ]+)+\.dll' | sort -u | while read -r dll; do
    echo "  Kopiere $dll"
    cp -u "$dll" "$setup_dir/bin/"
done

# ZIP-Archiv
echo "[INFO] Erstelle ZIP-Archiv..."
cd "$build_dir"
zip_file="app-windows.zip"
rm -f "$zip_file"
7z a -tzip "$zip_file" "$setup_dir_name"/* > /dev/null

echo "[SUCCESS] Fertig! Archiv erstellt unter: $(realpath "$zip_file")"
