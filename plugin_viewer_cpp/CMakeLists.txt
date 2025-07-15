cmake_minimum_required(VERSION 3.10)
project(gtk3_example)

find_package(PkgConfig REQUIRED)

# GTK3 suchen
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# libcurl suchen
find_package(CURL REQUIRED)

# Executable und Quellcode-Dateien
add_executable(app src/main.cpp src/fetch.hpp src/fetch.cpp)

# Include-Verzeichnisse
target_include_directories(app PRIVATE
    ${GTK3_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
)

# Bibliotheken linken
target_link_libraries(app PRIVATE
    ${GTK3_LIBRARIES}
    ${CURL_LIBRARIES}
)

# Zusätzliche GTK-Compiler-Flags
add_definitions(${GTK3_CFLAGS_OTHER})
