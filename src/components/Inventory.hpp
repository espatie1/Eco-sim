#pragma once
#include <unordered_map>
#include "Resource.hpp"

struct Inventory {
    std::unordered_map<ResourceId, double> stock;
};
