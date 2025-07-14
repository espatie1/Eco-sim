#pragma once
#include "../core/World.hpp"
#include "../components/Population.hpp"
#include "../components/Inventory.hpp"
#include "../components/Resource.hpp"

inline void run_consumption_tick(World& w, double dt_days)
{
    const auto wood = id_from_str("wood");

    auto view = w.registry().view<Population, Inventory>();
    for (auto e : view) {
        auto& pop = view.get<Population>(e);
        auto& inv = view.get<Inventory>(e);

        double need = pop.citizens * pop.wood_per_capita_day * dt_days;
        double& stock = inv.stock[wood];         // по hash<ResourceId>
        if (stock >= need) { stock -= need; }
        else { stock = 0.0; }                    // нехватка → будущий голод
    }
}
