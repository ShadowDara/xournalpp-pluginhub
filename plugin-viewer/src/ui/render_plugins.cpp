// render_plugins.cpp

#include "../header/render_plugins.hpp"

void render_plugins_from_json(GtkWidget* container, const std::string& json_str) {
    try {
        auto data = json::parse(json_str);

        std::cout << "*** Loading Json ***" << std::endl;

        if (!data.is_array()) {
            std::cerr << "JSON ist kein Array\n";
            return;
        }

        for (const auto& plugin : data) {
            std::string name = plugin.value("name", "Unbekannt");
            std::string author = plugin.value("author", "Unbekannt");
            std::string version = plugin.value("version", "Unbekannt");

            GtkWidget* frame = gtk_frame_new(nullptr);
            GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            gtk_container_set_border_width(GTK_CONTAINER(box), 5);
            gtk_container_add(GTK_CONTAINER(frame), box);

            GtkWidget* name_label = gtk_label_new(("Name: " + name).c_str());
            GtkWidget* author_label = gtk_label_new(("Autor: " + author).c_str());
            GtkWidget* version_label = gtk_label_new(("Version: " + version).c_str());

            gtk_box_pack_start(GTK_BOX(box), name_label, FALSE, FALSE, 0);
            gtk_box_pack_start(GTK_BOX(box), author_label, FALSE, FALSE, 0);
            gtk_box_pack_start(GTK_BOX(box), version_label, FALSE, FALSE, 0);

            gtk_box_pack_start(GTK_BOX(container), frame, FALSE, FALSE, 5);
            
            gtk_widget_show(frame);
        }
    } catch (const std::exception& e) {
        std::cerr << "JSON Fehler: " << e.what() << "\n";
    }
}
