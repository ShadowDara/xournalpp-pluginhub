// ui_main.hpp
#ifndef UI_MAIN_HPP
#define UI_MAIN_HPP

#include <iostream>
#include <string>
#include <gtk/gtk.h>

#include "../header/fetch.hpp"
#include "../header/parse.hpp"
#include "../header/render_plugins.hpp"

void on_button_clicked(GtkButton *button, gpointer user_data);
void on_activate(GtkApplication* app, gpointer user_data);
GtkWidget* create_plugin_box(const std::string& name, const std::string& version, const std::string& author, const std::string& description);

#endif
