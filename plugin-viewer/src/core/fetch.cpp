// fetch.cpp

#include "../header/fetch.hpp"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetch_url(const std::string& url) {
    std::cout << "*** Fetching Data ***" << std::endl;

    CURL* curl = curl_easy_init();

    /* Just for local dev !!!
     * Change to:
     *
     * curl_easy_setopt(curl, CURLOPT_CAINFO, "path/to/cacert.pem");
     *
     * and download cacert.pem from
     *
     * https://curl.se/docs/caextract.html
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    std::string readBuffer;

    if (!curl) {
        std::cerr << "[ERROR] curl_easy_init() failed!" << std::endl;
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    // REQUIRED: GitHub blocks requests without User-Agent
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

    // Optional: follow redirects
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "[ERROR] curl_easy_perform() failed: "
                  << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return "";
    }

    curl_easy_cleanup(curl);
    return readBuffer;
}
