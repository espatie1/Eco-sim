#pragma once
#include <string>
#include <cstdint>

enum struct ResourceId : uint32_t {};      // просто индекс

// Константы для часто используемых ресурсов
namespace ResourceIds {
    constexpr ResourceId Wood = static_cast<ResourceId>(0);
    constexpr ResourceId Plank = static_cast<ResourceId>(1);
}

size_t resources_count();

struct ResourceInfo {
    ResourceId        id;
    std::string       name;
    double            base_price;
};

// доступ к загруженным данным
const ResourceInfo& get_resource(ResourceId);
ResourceId          id_from_str(const std::string&);

// хеш для unordered_map<ResourceId, …>
namespace std {
    template<> struct hash<ResourceId> {
        size_t operator()(const ResourceId& r) const noexcept {
            return static_cast<size_t>(r);
        }
    };
}
