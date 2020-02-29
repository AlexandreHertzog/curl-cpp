#ifndef INCLUDE_CURL_HPP
#define INCLUDE_CURL_HPP

#include <string>

namespace curlcpp
{
class Curl
{
    void *m_lib;

  public:
    using WriteCallback = size_t(void *contents, size_t size, size_t nmemb, void *userp);
    Curl();
    Curl(const Curl &other) = delete;
    ~Curl();

    void setUrl(const std::string &url);

    void setWriteCallback(WriteCallback *c, std::string &outValue);
    void run();
};
} // namespace curlcpp
#endif // INCLUDE_CURL_HPP
