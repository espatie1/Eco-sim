#include "core/World.hpp"
#include "components/Population.hpp"
#include "components/Inventory.hpp"
#include "systems/PopulationSystem.hpp"
#include "components/ProductionRecipe.hpp"
#include "systems/ProductionSystem.hpp"
#include "data/ResourceLoader.cpp"
#include "data/RecipeLoader.cpp"
#include "components/PriceBook.hpp"
#include "systems/ConsumptionSystem.hpp"
#include "systems/MarketSystem.hpp"
#include <spdlog/spdlog.h>

int main()
{
    load_resources();
    load_recipes();
    World world;
    auto pricebook = world.registry().create();
    world.registry().emplace<PriceBook>(pricebook,
        PriceBook{
            /*price*/  std::vector<double>(resources_count()),
            /*demand*/ std::vector<double>(resources_count()),
            /*supply*/ std::vector<double>(resources_count())
    });
    auto sawmill = world.registry().create();
    world.registry().emplace<Inventory>(sawmill);
    world.registry().emplace<ProductionRecipe>(sawmill,
        ProductionRecipe{
            /*inputs*/  { {ResourceIds::Wood,  1.0} },
            /*outputs*/ { {ResourceIds::Plank, 4.0} },
            /*hours*/   8.0
        });

    // первичный запас древесины
    auto& inv = world.registry().get<Inventory>(sawmill);
    inv.stock[ResourceIds::Wood] = 50;

    // в цикле:

    constexpr double hours_per_tick = 6.0;
    constexpr int    steps          = 1000;

    for (int i = 0; i < steps; ++i) {
        run_population_tick(world, hours_per_tick / 8760.0);
        run_consumption_tick(world, hours_per_tick / 24.0);
        run_production_tick(world, hours_per_tick);

        if ((i+1) % 4 == 0) run_market_tick(world);  // раз в сутки

        if (i % 40 == 0) {
            const auto wood  = id_from_str("wood");
            const auto plank = id_from_str("plank");
            auto& inv = world.registry().get<Inventory>(sawmill);
            auto& pb  = world.registry().get<PriceBook>(pricebook);
            spdlog::info("Day {:4}: wood={} plank={}  priceW={:.2f}",
                        i/4, inv.stock[wood], inv.stock[plank],
                        pb.price[(size_t)wood]);
        }
    }

    return 0;
}
