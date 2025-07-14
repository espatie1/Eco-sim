#include "nlohmann/json.hpp"
#include <fstream>
#include "../components/Resource.hpp"

static std::vector<ResourceInfo> resources;
static std::unordered_map<std::string, ResourceId> str2id;

void load_resources(const std::string& path = "data/resources.json")
{
    using json = nlohmann::json;
    std::ifstream f(path);
    json j;   f >> j;

    resources.clear();
    str2id.clear();

    for (size_t i=0;i<j.size();++i) {
        const auto& node = j[i];
        ResourceInfo info;
        info.id         = static_cast<ResourceId>(i);
        info.name       = node["id"].get<std::string>();
        info.base_price = node["base_price"].get<double>();
        resources.push_back(info);
        str2id[info.name] = info.id;
    }
}

const ResourceInfo& get_resource(ResourceId id) { return resources[(size_t)id]; }
ResourceId id_from_str(const std::string& s)   { return str2id.at(s); }

size_t resources_count() {
    return resources.size();   // resources — тот самый std::vector<ResourceInfo>
}
