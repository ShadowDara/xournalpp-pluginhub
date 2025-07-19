FROM fedora:42

# 1. Cross-Compiler + GTK3 für Windows installieren
RUN dnf -y update && \
    dnf -y install \
        mingw64-gcc \
        mingw64-gcc-c++ \
        mingw64-pkg-config \
        mingw64-gtk3 \
        mingw64-glib2 \
        mingw64-cmake \
        mingw64-libcurl \
        mingw64-nlohmann-json \
        mingw64-gtk3-devel \
        cmake \
        make \
        git && \
    dnf clean all

# 2. Arbeitsverzeichnis setzen
WORKDIR /app

# 3. Projekt rein kopieren
COPY /plugin-viewer /app

# 4. Build-Toolchain für MinGW (optional: kannst du auch in Datei auslagern)
RUN printf "%s\n" \
"set(CMAKE_SYSTEM_NAME Windows)" \
"set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)" \
"set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)" \
"set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)" \
"set(PKG_CONFIG_EXECUTABLE x86_64-w64-mingw32-pkg-config)" \
"set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32/sys-root/mingw)" \
"set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)" \
"set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)" \
"set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)" \
"set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)" \
> /app/toolchain-mingw64.cmake

# 5. Build-Befehl (du kannst das auch als ENTRYPOINT machen)
CMD mkdir -p build && cd build && \
    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw64.cmake \
        -DCMAKE_BUILD_TYPE=Release && \
    make && \
    echo "Windows-Build fertig unter /app/build/" \
    cp $(x86_64-w64-mingw32-objdump -p build/app.exe | grep 'DLL Name' | awk '{print $3}' | xargs -I{} find /usr/x86_64-w64-mingw32/sys-root/mingw/bin -name {}) build/ || true \
    cd build && zip -r app-windows.zip *
