// button_row.hpp

#ifndef BUTTON_ROW_HPP
#define BUTTON_ROW_HPP

#include <gtk/gtk.h>

GtkWidget* create_button_row();
static void on_add_button_clicked(GtkButton *button, gpointer user_data);
static void on_remove_button_clicked(GtkButton *button, gpointer user_data);
static void on_refresh_button_clicked(GtkButton *button, gpointer user_data);

#endif
