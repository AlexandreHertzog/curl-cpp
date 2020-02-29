//
// Created by alexh on 29/02/2020.
//

#include "curl.hpp"
#include <curl/curl.h>
#include <stdexcept>

curlcpp::Curl::Curl()
{
    m_lib = curl_easy_init();
    if (m_lib == nullptr)
    {
        throw std::runtime_error("Failed to initialize CURL");
    }
}

curlcpp::Curl::~Curl()
{
    if (m_lib != nullptr)
    {
        curl_easy_cleanup(m_lib);
        m_lib = nullptr;
    }
}

void curlcpp::Curl::setUrl(const std::string &url)
{
    if (m_lib == nullptr)
    {
        throw std::logic_error("Can't set URL if CURL is not initialized");
    }
    curl_easy_setopt(m_lib, CURLOPT_URL, url.c_str());
}

void curlcpp::Curl::setWriteCallback(WriteCallback *c, std::string &outValue)
{
    if (m_lib == nullptr)
    {
        throw std::logic_error("Can't set callback if CURL is not initialized");
    }
    auto rc = curl_easy_setopt(m_lib, CURLOPT_WRITEFUNCTION, c);
    if (CURLE_OK != rc)
    {
        throw std::invalid_argument("Invalid arguments for CURLOPT_WRITEFUNCTION, error " + std::to_string(rc));
    }
    rc = curl_easy_setopt(m_lib, CURLOPT_WRITEDATA, &outValue);
    if (CURLE_OK != rc)
    {
        throw std::invalid_argument("Invalid arguments for CURLOPT_WRITEDATA, error " + std::to_string(rc));
    }
}

void curlcpp::Curl::run()
{
    if (m_lib == nullptr)
    {
        throw std::logic_error("Can't run if CURL is not initialized");
    }
    const auto rc = curl_easy_perform(m_lib);
    if (CURLE_OK != rc)
    {
        throw std::invalid_argument("CURL perform failed with error " + std::to_string(rc));
    }
}
