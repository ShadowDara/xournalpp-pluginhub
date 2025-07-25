cmake_minimum_required(VERSION 3.10)
project(xournalpp_plugin_viewer)

# Definiere Pfad zur CSS-Datei
set(STYLE_PATH "${CMAKE_BINARY_DIR}/dist/share/style.css")

# config.hpp aus Vorlage erzeugen (landet im Build-Verzeichnis)
configure_file(src/header/config.hpp.in ../src/header/config.hpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(app 
    src/main.cpp

    # Header files
    src/header/button_row.hpp
    src/header/fetch.hpp
    src/header/main.hpp
    src/header/parse.hpp
    src/header/render_plugins.hpp
    src/header/ui_main.hpp

    # Core Files
    src/core/fetch.cpp
    src/core/parse.cpp

    # UI Files
    src/ui/button_row.cpp
    src/ui/render_plugins.cpp
    src/ui/ui_main.cpp
)

# Header aus Build-Verzeichnis einbinden (damit config.hpp gefunden wird)
target_include_directories(app PRIVATE 
    ${CMAKE_BINARY_DIR}         # <- enthält die generierte config.hpp
    ${GTK3_INCLUDE_DIRS}
)

# GTK3 Flags
target_link_libraries(app PRIVATE ${GTK3_LIBRARIES})
add_definitions(${GTK3_CFLAGS_OTHER})

# curl & json (modern targets)
target_link_libraries(app PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)

# App installieren
install(TARGETS app
    RUNTIME DESTINATION bin
)

# CSS-Datei mitinstallieren
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/style.css
        DESTINATION share)
