#pragma once
#include "Resource.hpp"
#include <vector>

struct IO {
    ResourceId id;
    double     qty;
};

struct ProductionRecipe {
    std::vector<IO> inputs;     // Wood×1
    std::vector<IO> outputs;    // Plank×4
    double          hours;      // длительность цикла
    double          progress{0.0};
};
