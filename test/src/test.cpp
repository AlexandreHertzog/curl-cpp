#include "curlcpp/curl.hpp"
#include <iostream>
#include <string>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    std::string readBuffer;

    curlcpp::Curl curl;
    curl.setUrl("http://www.google.com");
    curl.setWriteCallback(WriteCallback, readBuffer);
    curl.run();
    std::cout << readBuffer << std::endl;
    return 0;
}
