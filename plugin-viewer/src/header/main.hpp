// main.hpp

#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>

#include "../header/fetch.hpp"
#include "../header/parse.hpp"
#include "../header/ui_main.hpp"

void activate_app(GtkApplication *app, gpointer user_data);
std::string fetch_and_parse();

#endif
