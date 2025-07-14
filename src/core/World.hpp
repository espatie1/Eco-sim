#pragma once
#include <entt/entt.hpp>

class World {
public:
    entt::registry& registry() { return reg; }

private:
    entt::registry reg;
};
