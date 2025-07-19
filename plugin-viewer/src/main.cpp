#include "header/main.hpp"

int main(int argc, char **argv) {
    //std::string json = fetch_url("https://raw.githubusercontent.com/ShadowDara/xournalpp-plugin-hub-idea/refs/heads/main/plugins.json");
    //parse_json(json);

    GtkApplication *app = gtk_application_new("org.example.gtk3", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    g_signal_connect(app, "button-clicked", G_CALLBACK(on_button_clicked), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return status;
}
