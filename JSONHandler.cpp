#include "JSONHandler.h"

using std::string, std::map, std::vector, std::pair;
using std::cout, std::cin, std::endl;

JSONHandler::JSONHandler() {
    branch = "";
    branch_packs = {};
}

JSONHandler::JSONHandler(std::string name, std::string data) {
    branch = name;

    rapidjson::Document document;
    document.Parse(data.c_str());

    const unsigned int length = document["length"].GetInt();
    const auto& packages = document["packages"];

    for (rapidjson::SizeType i = 0; i < length; i++) {
        const auto& pkg = packages[i];
        const string arch = pkg["arch"].GetString();
        const int buildtime = pkg["buildtime"].GetInt();
        const string disttag = pkg["disttag"].GetString();
        const int epoch = pkg["epoch"].GetInt();
        const string name = pkg["name"].GetString();
        const string release = pkg["release"].GetString();
        const string source = pkg["source"].GetString();
        const string version = pkg["version"].GetString();
        
        branch_packs[{arch, name}] = {
            arch,
            buildtime,
            disttag,
            epoch,
            name,
            release,
            source,
            version
        };
    }
}

JSONHandler::~JSONHandler() {
}

std::string JSONHandler::getBranach(){
    return branch;
}

package_json JSONHandler::getPackage(std::string arch, std::string name){
    return branch_packs[{arch, name}];
}

vector<package_json> JSONHandler::except(JSONHandler branch){
    vector<package_json> result = {};

    for (auto pack : branch_packs){
        if (branch.branch_packs.find(pack.first) == branch.branch_packs.end()){
            result.push_back(pack.second);
        }
    }
    
    return result;
}

vector<package_json> JSONHandler::newer(JSONHandler branch){
    vector<package_json> result = {};

    string vr1, vr2;
    for (auto pack : branch_packs){
        if (branch.branch_packs.find(pack.first) != branch.branch_packs.end()){
            if (rpmcmp(pack.second, branch.branch_packs[pack.first]) == 1) {
                result.push_back(pack.second);
            }
        }
    }

    return result;
}

int rpmcmp(package_json p1, package_json p2) {
    std::vector<std::variant<int, std::string>> ver1, ver2, rel1, rel2;
    ver1 = split(p1.version);
    ver2 = split(p2.version);
    int res = verrelcmp(ver1, ver2);
    if (res != 0){
        return res;
    }

    rel1 = split(p1.release);
    rel2 = split(p2.release);
    res = verrelcmp(rel1, rel2);

    return res;
}

int verrelcmp(std::vector<std::variant<int, std::string>> arg1,std::vector<std::variant<int, std::string>> arg2){
    for (int i = 0; i < std::min(arg1.size(), arg2.size()); ++i){
        if (std::holds_alternative<int>(arg1[i]) && std::holds_alternative<int>(arg2[i])){
            if (arg1[i] > arg2[i]){
                return 1;
            } else if (arg1[i] < arg2[i]) {
                return -1;
            }
        } else if (std::holds_alternative<std::string>(arg1[i]) && std::holds_alternative<std::string>(arg2[i])){
            if (arg1[i] > arg2[i]){
                return 1;
            } else if (arg1[i] < arg2[i]) {
                return -1;
            }
        } else {
            if (std::holds_alternative<int>(arg1[i])) {
                return 1;
            } else if (std::holds_alternative<int>(arg2[i])){
                return -1;
            }
        }
    }
    if (arg1.size() > arg2.size()) {
        return 1;
    } else if (arg1.size() < arg2.size()) {
        return -1;
    }

    return 0;
}

std::vector<std::variant<int, std::string>> split(std::string input){
    std::vector<std::variant<int, std::string>> tokens = {};
    std::string cur = "";
    for (char c : input){
        if (isdigit(c)) {
            if (!cur.empty() && isalpha(cur.back())) {
                tokens.push_back(cur);
                cur.clear();
            }
            cur += c;
        } else if (isalpha(c)) {
            if (!cur.empty() && isdigit(cur.back())) {
                tokens.push_back(std::stoi(cur));
                cur.clear();
            }
            cur += c;
        } else {
            if (!cur.empty()) {
                if (isdigit(cur.back())) {
                    tokens.push_back(std::stoi(cur));
                } else {
                    tokens.push_back(cur);
                }
                cur.clear();
            }
        }
    }
    if (!cur.empty()) {
        if (isdigit(cur.back())) {
            tokens.push_back(std::stoi(cur));
        } else {
            tokens.push_back(cur);
        }
    }
    return tokens;
}