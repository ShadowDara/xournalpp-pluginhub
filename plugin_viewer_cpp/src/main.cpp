#include <iostream>
#include <gtk/gtk.h>
#include "fetch.hpp"

static void on_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Button wurde geklickt!\n");

    // Beispiel: Inhalt von example.com fetchen
    std::string html = fetch_url("https://raw.githubusercontent.com/ShadowDara/xournalpp-plugin-hub-idea/refs/heads/main/plugins.json");
    std::cout << "Website-Inhalt:\n" << html << std::endl;
}

static void on_activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Xournal++ Plugin Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    // Layout-Box erstellen (vertikal)
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Label hinzufügen
    GtkWidget *label = gtk_label_new("Willkommen zum Plugin-Manager!");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    // Button hinzufügen
    GtkWidget *button = gtk_button_new_with_label("Plugin hinzufügen");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    // Start the Application
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.example.gtk3", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
