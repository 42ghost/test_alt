#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <string>
#include "CURLRequest.h"
#include "JSONHandler.h"

class Comparator {
private:
    JSONHandler branch1;
    JSONHandler branch2;

    std::vector<package_json> b1_except_b2;
    std::vector<package_json> b2_except_b1;
    std::vector<package_json> b1_newer_b2;
public:
    Comparator();
    Comparator(std::string branch1, std::string branch2);
    ~Comparator();

    void compare();
    void save();
};

#endif // COMPARATOR_H