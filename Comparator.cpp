#include "Comparator.h"


Comparator::Comparator() {
}

Comparator::Comparator(std::string branch1, std::string branch2) {
    CURLRequest curl_req;
    std::string data1 = curl_req.request(branch1);
    std::string data2 = curl_req.request(branch2);
    
    this->branch1 = JSONHandler(branch1, data1);
    this->branch2 = JSONHandler(branch2, data2);
}

Comparator::~Comparator() {
}

void Comparator::compare() {
    b1_except_b2 = std::move(branch1.except(branch2));
    b2_except_b1 = std::move(branch2.except(branch1));
    b1_newer_b2 = std::move(branch1.newer(branch2));
}

void Comparator::save() {
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value br1_ex_br2(rapidjson::kArrayType);
    for(const auto& data : b1_except_b2) {
        rapidjson::Value item(rapidjson::kObjectType);
        item.AddMember("arch", rapidjson::Value(data.arch.c_str(), allocator).Move(), allocator);
        item.AddMember("buildtime", data.buildtime, allocator);
        item.AddMember("disttag", rapidjson::Value(data.disttag.c_str(), allocator).Move(), allocator);
        item.AddMember("epoch", data.epoch, allocator);
        item.AddMember("name", rapidjson::Value(data.name.c_str(), allocator).Move(), allocator);
        item.AddMember("release", rapidjson::Value(data.release.c_str(), allocator).Move(), allocator);
        item.AddMember("source", rapidjson::Value(data.source.c_str(), allocator).Move(), allocator);
        item.AddMember("version", rapidjson::Value(data.version.c_str(), allocator).Move(), allocator);
        br1_ex_br2.PushBack(item, allocator);
    }

    rapidjson::Value br2_ex_br1(rapidjson::kArrayType);
    for(const auto& data : b2_except_b1) {
        rapidjson::Value item(rapidjson::kObjectType);
        item.AddMember("arch", rapidjson::Value(data.arch.c_str(), allocator).Move(), allocator);
        item.AddMember("buildtime", data.buildtime, allocator);
        item.AddMember("disttag", rapidjson::Value(data.disttag.c_str(), allocator).Move(), allocator);
        item.AddMember("epoch", data.epoch, allocator);
        item.AddMember("name", rapidjson::Value(data.name.c_str(), allocator).Move(), allocator);
        item.AddMember("release", rapidjson::Value(data.release.c_str(), allocator).Move(), allocator);
        item.AddMember("source", rapidjson::Value(data.source.c_str(), allocator).Move(), allocator);
        item.AddMember("version", rapidjson::Value(data.version.c_str(), allocator).Move(), allocator);
        br2_ex_br1.PushBack(item, allocator);
    }

    rapidjson::Value n_packs(rapidjson::kArrayType);
    for(const auto& data : b1_newer_b2) {
        rapidjson::Value item(rapidjson::kObjectType);
        item.AddMember("arch", rapidjson::Value(data.arch.c_str(), allocator).Move(), allocator);
        item.AddMember("buildtime", data.buildtime, allocator);
        item.AddMember("disttag", rapidjson::Value(data.disttag.c_str(), allocator).Move(), allocator);
        item.AddMember("epoch", data.epoch, allocator);
        item.AddMember("name", rapidjson::Value(data.name.c_str(), allocator).Move(), allocator);
        item.AddMember("release", rapidjson::Value(data.release.c_str(), allocator).Move(), allocator);
        item.AddMember("source", rapidjson::Value(data.source.c_str(), allocator).Move(), allocator);
        item.AddMember("version", rapidjson::Value(data.version.c_str(), allocator).Move(), allocator);
        n_packs.PushBack(item, allocator);
    }

    document.SetObject();
    document.AddMember("branch1_except_branch2", br1_ex_br2, allocator);
    document.AddMember("branch2_except_branch1", br2_ex_br1, allocator);
    document.AddMember("branch1_newer_branch2", n_packs, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::ofstream ofs(branch1.getBranach() + "_" + branch2.getBranach() + ".json");
    ofs << buffer.GetString();
    ofs.close();
}