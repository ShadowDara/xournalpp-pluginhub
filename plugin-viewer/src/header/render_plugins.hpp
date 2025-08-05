// render_pluigins.hpp

#ifndef RENDER_PLUGINS_HPP
#define RENDER_PLUGINS_HPP

#include <iostream>
#include <gtk/gtk.h>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void render_plugins_from_json(GtkWidget* container, const std::string& json_str);

#endif
