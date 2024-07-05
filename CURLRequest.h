#ifndef CURLREQUEST_H
#define CURLREQUEST_H

#include <iostream>
#include <string>
#include <curl/curl.h>

class CURLRequest {
private:
    std::string buff;
    CURL* curl;
public:
    CURLRequest();
    CURLRequest(const CURLRequest&) = delete;
    CURLRequest& operator= (const CURLRequest&) = delete;
    ~CURLRequest();

    static size_t callback(void *contents, size_t sz, size_t nmemb, void *userp);
    std::string request(std::string branch);
};

#endif // CURLREQUEST_H