// downloader.cpp

#include "../header/downloader.hpp"

size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    std::ofstream* out = static_cast<std::ofstream*>(stream);
    size_t total_size = size * nmemb;
    out->write(static_cast<char*>(ptr), total_size);
    return total_size;
}

bool download_file(const std::string& url, const std::string& out_filename) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::ofstream outfile(out_filename, std::ios::binary);
    if (!outfile) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outfile);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    outfile.close();

    return res == CURLE_OK;
}

/*

int main() {
    std::string url = "https://github.com/user/repo/archive/refs/heads/main.zip";
    std::string output = "repo.zip";

    if (download_file(url, output)) {
        std::cout << "Download erfolgreich.\n";
    } else {
        std::cerr << "Download fehlgeschlagen.\n";
    }
}

*/
