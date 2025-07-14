#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include "../components/ProductionRecipe.hpp"
#include "../components/Resource.hpp"

std::vector<ProductionRecipe> all_recipes;

void load_recipes(const std::string& dir="data/recipes")
{
    using json=nlohmann::json;
    all_recipes.clear();
    for (auto& entry : std::filesystem::directory_iterator(dir))
    {
        std::ifstream f(entry.path());
        json j; f >> j;
        ProductionRecipe r;
        r.hours = j["hours"].get<double>();
        for (auto& in : j["inputs"])
            r.inputs.push_back({ id_from_str(in["id"]), in["qty"] });
        for (auto& out : j["outputs"])
            r.outputs.push_back({ id_from_str(out["id"]), out["qty"] });
        all_recipes.push_back(std::move(r));
    }
}
