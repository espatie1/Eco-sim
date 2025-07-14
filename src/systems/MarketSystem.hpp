#pragma once
#include "../core/World.hpp"
#include "../components/PriceBook.hpp"
#include "../components/Inventory.hpp"
#include "../components/Resource.hpp"
#include <algorithm>

inline void run_market_tick(World& w)
{
    auto [pbEnt, pb] = *w.registry().view<PriceBook>().each().begin();
    std::fill(pb.demand.begin(), pb.demand.end(), 0.0);
    std::fill(pb.supply.begin(), pb.supply.end(), 0.0);

    // 1. собираем supply
    auto invView = w.registry().view<Inventory>();
    for (auto& [e, inv] : invView.each()) {
        for (auto& [rid, qty] : inv.stock)
            pb.supply[(size_t)rid] += qty;
    }

    // 2. demand пока = вчерашнее потребление wood (пример)
    //    Добавим плавный EMA, чтобы не дёргалось
    const double alpha = 0.2;
    for (size_t i=0;i<pb.demand.size();++i) {
        pb.demand[i] = alpha * pb.demand[i] + (1.0 - alpha) * pb.supply[i] * 0.0; // placeholder
    }

    // 3. считаем цену
    for (size_t i=0;i<pb.price.size();++i) {
        const double base = get_resource(static_cast<ResourceId>(i)).base_price;
        const double d = pb.demand[i];
        const double s = pb.supply[i];
        pb.price[i] = base * (s > 0 ? d / s : 2.0);     // если ресурс на нуле — ×2
    }
}
