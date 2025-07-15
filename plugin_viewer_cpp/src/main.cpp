#include <gtk/gtk.h>
#include <iostream>
#include "fetch.hpp"

static void on_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Button wurde geklickt!\n");
}

static void on_activate(GtkApplication* app, gpointer user_data) {
    // Fenster
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Xournal++ Plugin Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Headerbar
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Xournal++ Plugin Manager");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);

    // Hauptlayout
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 15);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Label hinzufügen
    GtkWidget *label = gtk_label_new("Willkommen zum Plugin-Manager!");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    // Button hinzufügen
    GtkWidget *button = gtk_button_new_with_label("Plugin hinzufügen");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    // CSS anwenden
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "* { font-size: 14pt; }"
        "window { background-color: #1e1e1e; }"
        "entry, button { font-size: 14pt; }"
        "header/label { color: white; font-size: 14pt; }"
        "button { background: #ff4081; color: white; padding: 10px; border-radius: 10px; }"
        "entry { background: #2e2e2e; color: white; }",
        -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_show_all(window);
}

void fetch_and_parse() {
    std::string html = fetch_url("https://raw.githubusercontent.com/ShadowDara/xournalpp-plugin-hub-idea/refs/heads/main/plugins.json");
    std::cout << "Website-Inhalt:\n\n" << html << "\n\nInhalt Ende" << std::endl;
}

int main(int argc, char **argv) {
    fetch_and_parse();

    GtkApplication *app = gtk_application_new("org.example.gtk3", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
