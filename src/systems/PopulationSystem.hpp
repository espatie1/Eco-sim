#pragma once
#include "../core/World.hpp"
#include "../components/Population.hpp"

inline void run_population_tick(World& w, double dt_years)
{
    auto view = w.registry().view<Population>();
    for (auto e : view) {
        auto& pop = view.get<Population>(e);
        const double delta = pop.citizens * (pop.birth_rate - pop.death_rate) * dt_years;
        pop.citizens += delta;
    }
}
