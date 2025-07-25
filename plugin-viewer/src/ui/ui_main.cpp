#include "../header/ui_main.hpp"

// Hauptaktivierung des GTK-Programms
void on_activate(GtkApplication* app, gpointer user_data) {
    // === Fenster erstellen ===
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Xournal++ Plugin Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // === Haupt-Layoutbox ===
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // === Headerbar ===
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Xournal++ Plugin Manager");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);

    // === Inhalt-Box ===
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 15);
    gtk_container_add(GTK_CONTAINER(main_box), box);

    // Begrüßungslabel
    GtkWidget *label = gtk_label_new("Willkommen zum Plugin-Manager!");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    // === Button-Leiste einfügen ===
    GtkWidget *button_row = create_button_row();
    gtk_box_pack_start(GTK_BOX(box), button_row, FALSE, FALSE, 0);

    // === Scrollbereich ===
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_vexpand(scrolled, TRUE);
    gtk_box_pack_start(GTK_BOX(main_box), scrolled, TRUE, TRUE, 0);

    // === Pluginliste ===
    GtkWidget *plugin_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(scrolled), plugin_list);

    // === Plugins laden ===
    std::string json = fetch_url("https://raw.githubusercontent.com/ShadowDara/xournalpp-pluginhub/main/data/plugins.json");
    render_plugins_from_json(plugin_list, json);

    // === CSS laden und anwenden ===
    GtkCssProvider* provider = gtk_css_provider_new();
    GdkDisplay* display = gdk_display_get_default();
    GdkScreen* screen = gdk_display_get_default_screen(display);

    GError* error = nullptr;
    gtk_css_provider_load_from_path(provider, STYLE_PATH, &error);

    if (error) {
        g_warning("Fehler beim Laden des CSS: %s", error->message);
        g_clear_error(&error);
    }

    gtk_style_context_add_provider_for_screen(
        screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    // === Fenster anzeigen ===
    gtk_widget_show_all(window);
}
