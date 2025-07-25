// button_row.cpp

#include "../header/button_row.hpp"

GtkWidget* create_button_row() {
    // Horizontale Box für Buttons
    GtkWidget *button_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    // Plugin hinzufügen
    GtkWidget *add_button = gtk_button_new_with_label("Plugin hinzufügen");
    g_signal_connect(add_button, "clicked", G_CALLBACK(on_add_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(button_row), add_button, FALSE, FALSE, 0);

    // Plugin entfernen
    GtkWidget *remove_button = gtk_button_new_with_label("Plugin entfernen");
    g_signal_connect(remove_button, "clicked", G_CALLBACK(on_remove_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(button_row), remove_button, FALSE, FALSE, 0);

    // Aktualisieren
    GtkWidget *refresh_button = gtk_button_new_with_label("Aktualisieren");
    g_signal_connect(refresh_button, "clicked", G_CALLBACK(on_refresh_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(button_row), refresh_button, FALSE, FALSE, 0);

    return button_row;
}

static void on_add_button_clicked(GtkButton* button, gpointer user_data) {
    g_print("Add-Button wurde geklickt!\n");
}

static void on_remove_button_clicked(GtkButton* button, gpointer user_data) {
    g_print("Remove-Button wurde geklickt!\n");
}

static void on_refresh_button_clicked(GtkButton* button, gpointer user_data) {
    g_print("Refresh-Button wurde geklickt!\n");
}
