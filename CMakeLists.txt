cmake_minimum_required(VERSION 3.23)
project(eco-sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Санитайзеры в Debug
include(cmake/CompileOptions.cmake)

# FetchContent внешних библиотек
include(FetchContent)
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG        v3.13.0
)
FetchContent_MakeAvailable(entt)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(eco-sim
    src/main.cpp
    src/core/World.cpp
    src/systems/PopulationSystem.hpp
    src/systems/ProductionSystem.hpp            # <─ заголовок c inline-кодом
    src/systems/ConsumptionSystem.hpp
    src/systems/MarketSystem.hpp
)

# Копируем папку data/ из исходников в директорию с бинарником
add_custom_command(TARGET eco-sim  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data          # откуда
            $<TARGET_FILE_DIR:eco-sim>/data   # куда (рядом с eco-sim)
)

target_include_directories(eco-sim PRIVATE src)
target_link_libraries(eco-sim PRIVATE EnTT::EnTT spdlog::spdlog nlohmann_json::nlohmann_json)
