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
    */

    // Scrollbereich hinzufügen
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_vexpand(scrolled, TRUE);
    gtk_box_pack_start(GTK_BOX(main_box), scrolled, TRUE, TRUE, 0);

    // Die Box, in der die Plugins gelistet werden
    GtkWidget *plugin_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(scrolled), plugin_list); 

    // Data Fetching
    std::string json = fetch_url("https://raw.githubusercontent.com/ShadowDara/xournalpp-pluginhub/refs/heads/main/data/plugins.json");

    render_plugins_from_json(plugin_list, json);

    // CSS anwenden
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "* { font-size: 14pt; }"
        "window { background-color: #1e1e1e; }"
        "entry, button { font-size: 14pt; }"
        "button { background: #ff4081; color: white; padding: 10px; border-radius: 10px; }"
        "entry { background: #2e2e2e; color: white; }",
        -1, NULL
    );
    // "header/label { color: white; font-size: 14pt; }"

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_show_all(window);
}


// Create a plugin box with details
GtkWidget* create_plugin_box(const std::string& name,
                             const std::string& version,
                             const std::string& author,
                             const std::string& description) {
    // Äußerer Rahmen
    GtkWidget* frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);

    // Vertikaler Box-Container
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 8);
    gtk_container_add(GTK_CONTAINER(frame), vbox);

    // Titel (Plugin Name + Version)
    std::string title = name + " (" + version + ")";
    GtkWidget* title_label = gtk_label_new(title.c_str());
    gtk_widget_set_halign(title_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 0);

    // Autor
    std::string author_text = "Author: " + author;
    GtkWidget* author_label = gtk_label_new(author_text.c_str());
    gtk_widget_set_halign(author_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), author_label, FALSE, FALSE, 0);

    // Beschreibung
    GtkWidget* desc_label = gtk_label_new(description.c_str());
    gtk_label_set_line_wrap(GTK_LABEL(desc_label), TRUE);
    gtk_widget_set_halign(desc_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), desc_label, FALSE, FALSE, 0);

    return frame;
}
