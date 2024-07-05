#include "CURLRequest.h"

CURLRequest::CURLRequest() {
    buff.reserve(CURL_MAX_WRITE_SIZE * 10);

    curl = curl_easy_init();
    if (!curl){
        std::cerr << "error: cURL is not init" << std::endl;
        throw "Error with cURL init";
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buff);
}

CURLRequest::~CURLRequest() {
    curl_easy_cleanup(curl);
}

size_t CURLRequest::callback(void *contents, size_t sz, size_t nmemb, void *userp){
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), sz * nmemb);
    return sz * nmemb;
}

std::string CURLRequest::request(std::string branch){
    buff.clear();
    
    std::string req = "https://rdb.altlinux.org/api/export/branch_binary_packages/";
    req += curl_easy_escape(curl, branch.c_str(), branch.size());

    curl_easy_setopt(curl, CURLOPT_URL, req.c_str());

    CURLcode res = curl_easy_perform(curl);
    std::cout << req << "\n";
    if (res != CURLE_OK) { 
        std::cerr << "error (cURL request failed):\t" << curl_easy_strerror(res) << std::endl;
        buff.clear();
    }

    return buff;
}