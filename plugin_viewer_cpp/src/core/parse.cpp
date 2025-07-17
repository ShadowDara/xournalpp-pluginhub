// parse.cpp
#include "../header/parse.hpp"

// Parse JSON data and print plugin information
void parse_json(const std::string &json) {
    nlohmann::json j = nlohmann::json::parse(json);

    std::cout << "------------------------" << std::endl;
    if (j.is_array()) {
        for (const auto& plugin : j) {
            std::cout << "Plugin Name: " << plugin["name"].get<std::string>() << std::endl;
            std::cout << "Version: " << plugin["version"].get<std::string>() << std::endl;
            std::cout << "Description: " << plugin["description"].get<std::string>() << std::endl;
            std::cout << "Author: " << plugin["author"].get<std::string>() << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    } else {
        std::cerr << "Fehler beim Parsen des JSON: Erwartetes Array." << std::endl;
    }
}
