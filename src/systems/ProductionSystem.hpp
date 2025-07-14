#pragma once
#include "../core/World.hpp"
#include "../components/Inventory.hpp"
#include "../components/ProductionRecipe.hpp"

inline void run_production_tick(World& w, double dt_hours)
{
    auto view = w.registry()
                   .view<ProductionRecipe, Inventory>();

    for (auto e : view) {
        auto& recipe   = view.get<ProductionRecipe>(e);
        auto& inv      = view.get<Inventory>(e);

        // если цикл не идёт — проверяем, есть ли сырьё
        bool can_start = true;
        for (auto [res, qty] : recipe.inputs) {
            if (inv.stock[res] < qty) { can_start = false; break; }
        }
        if (can_start && recipe.progress == 0.0) {
            // списываем сырьё
            for (auto [res, qty] : recipe.inputs)
                inv.stock[res] -= qty;
        }

        // если идёт — наращиваем прогресс
        if (recipe.progress < recipe.hours) {
            recipe.progress += dt_hours;
            if (recipe.progress >= recipe.hours) {
                // цикл окончен — кладём выход
                for (auto [res, qty] : recipe.outputs)
                    inv.stock[res] += qty;
                recipe.progress = 0.0;
            }
        }
    }
}
