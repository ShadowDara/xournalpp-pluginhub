#include "header/main.hpp"

int main(int argc, char **argv) {
    std::string json = fetch_url("https://raw.githubusercontent.com/ShadowDara/xournalpp-pluginhub/refs/heads/main/data/plugins.json");

    if (json.empty()) {
        std::cerr << "[ERROR] Empty response! Check your internet connection, URL, or curl config." << std::endl;
    } else {
        std::cout << "[DEBUG] JSON content:\n" << json << std::endl;
        parse_json(json);
    }

    GtkApplication *app = gtk_application_new("org.example.gtk3", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return status;
}
