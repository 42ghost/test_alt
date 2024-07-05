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
    vector<package_json> result;

    for (auto pack : branch_packs){
        if (branch.branch_packs.find(pack.first) == branch.branch_packs.end()){
            result.push_back(pack.second);
        }
    }
    
    return result;
}

vector<package_json> JSONHandler::newer(JSONHandler branch){
    vector<package_json> result;

    string vr1, vr2;
    for (auto pack : branch_packs){
        if (branch.branch_packs.find(pack.first) != branch.branch_packs.end()){
            vr1 = pack.second.version + pack.second.release;
            vr2 = branch.branch_packs[pack.first].version + branch.branch_packs[pack.first].release;
            if (vr1 > vr2) {
                result.push_back(pack.second);
            }
        }
    }

    return result;
}