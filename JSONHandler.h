#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <variant>
#include <utility>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>

struct package_json {
    std::string arch;
    int buildtime;
    std::string disttag;
    int epoch;
    std::string name;
    std::string release;
    std::string source;
    std::string version;
};

class JSONHandler {
private:
    std::string branch;
    std::map<std::pair<std::string, std::string>, package_json> branch_packs;
public:
    JSONHandler();
    JSONHandler(std::string name, std::string data);
    ~JSONHandler();

    std::string getBranach();
    package_json getPackage(std::string arch, std::string name);

    std::vector<package_json> except(JSONHandler);
    std::vector<package_json> newer(JSONHandler);
};

int rpmcmp(package_json p1, package_json p2);
int verrelcmp(std::vector<std::variant<unsigned long long, std::string>> ,std::vector<std::variant<unsigned long long, std::string>>);
std::vector<std::variant<unsigned long long, std::string>> split(std::string);

#endif
