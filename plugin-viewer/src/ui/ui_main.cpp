#include "../header/ui_main.hpp"

void on_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Button wurde geklickt!\n");
}

void on_activate(GtkApplication* app, gpointer user_data) {
    // Fenster
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Xournal++ Plugin Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    // Hauptbox erstellen (das EINZIGE direkte Kind des Fensters)
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Headerbar
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Xournal++ Plugin Manager");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);

    // Hauptlayout
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 15);
    gtk_container_add(GTK_CONTAINER(main_box), box);

    // Label hinzufügen
    GtkWidget *label = gtk_label_new("Willkommen zum Plugin-Manager!");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    /* Button hinzufügen
    GtkWidget *button = gtk_button_new_with_label("Plugin hinzufügen");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    g_signal_connect(app, "button-clicked", G_CALLBACK(on_button_clicked), NULL);
    */

    // Scrollbereich hinzufügen
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_vexpand(scrolled, TRUE);
    gtk_box_pack_start(GTK_BOX(main_box), scrolled, TRUE, TRUE, 0);

    // Die Box, in der die Plugins gelistet werden
    GtkWidget *plugin_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(scrolled), plugin_list); 

    // Data Fetching
    std::string json = fetch_url("https://raw.githubusercontent.com/ShadowDara/xournalpp-pluginhub/main/data/plugins.json");  // Fix: falscher Pfad (refs/heads)

    render_plugins_from_json(plugin_list, json);

    // CSS anwenden
    GtkCssProvider* provider = gtk_css_provider_new();
    GdkDisplay* display = gdk_display_get_default();
    GdkScreen* screen = gdk_display_get_default_screen(display);
    
    GError* error = nullptr;
    gtk_css_provider_load_from_path(provider, STYLE_PATH, &error);  // Fix: std::string → c_str()

    if (error) {
        g_warning("Error loading CSS: %s", error->message);
        g_clear_error(&error);
    }

    gtk_style_context_add_provider_for_screen(
        screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    gtk_widget_show_all(window);
}
