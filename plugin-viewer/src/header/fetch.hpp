// fetch.hpp

#ifndef FETCH_HPP
#define FETCH_HPP

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <stdexcept>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
std::string fetch_url(const std::string& url);

#endif
