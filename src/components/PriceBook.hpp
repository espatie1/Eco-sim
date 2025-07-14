#pragma once
#include <vector>
#include "../components/Resource.hpp"

struct PriceBook {
    std::vector<double> price;   // индекс совпадает с ResourceId
    std::vector<double> demand;
    std::vector<double> supply;
};
