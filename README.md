# eco-sim — Data‑Driven Economic Sandbox (WIP)

A minimal **C++20 + ECS** prototype of a living historical economy.  
Everything here is **pre‑alpha**, proving the core feedback loop:

> _population growth → resource consumption → dynamic prices → production feedback_

---

## 1 · Target look & feel

| Layer | Idea |
|-------|------|
| **Node Graph UI** | Squares = economic nodes (settlement, mine, factory); coloured links = resource / logistics / workforce. |
| **Zoom Levels** | 0 = country heat‑map, 1 = district, 2 = single node (inventory / HR / finance). |
| **Live Map** | Hex / square tiles, roads & rivers; moving dots show real goods flow. |
| **Events** | Epidemics, Luddite riots, trade fairs, global crises — rule‑driven JSON. |
| **AI Companies** | GOAP + genetic tuning; personality drives dumping, price gouging, tax fraud, etc. |

Minimal pastel art, smooth zoom — focus is **data clarity**, not 3‑D graphics.

---

## 2 · Repo snapshot

```
eco-sim/
├─ CMakeLists.txt
├─ src/                # core, components, systems, data loaders, main.cpp
├─ data/               # resources.json, recipes/
└─ cmake/CompileOptions.cmake
```

### Working ✅
* Population, Consumption, Production, Market (v0) systems
* JSON hot‑loaded, no recompilation to tweak rules

Build & run:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .          # binary appears + data/ copied here
./eco-sim                # watch wood price rise as supply falls
```

Console sample:

```
Day    0: wood=50 plank=0   priceW=1.00
Day   60: wood=0  plank=480 priceW=2.00
```

---

## 3 · Roadmap

| Sprint | Goal | Key tasks |
|--------|------|-----------|
| 0.2 | ExtractionSystem | add lumber camp producing wood |
| 0.3 | Logistics skeleton | deliveries with ETA & cost |
| 0.4 | ImGui prototype | node graph, live tables, price chart |
| 0.5 | EventSystem v1 | JSON‑driven epidemics / unrest |
| 0.6 | Company AI v0 | GOAP actions + personality |
| 0.7 | Persistence | save/load world |
| 0.8 | Multithread tick | Taskflow + profiling |
| 1.0 | Medieval MVP | map, tech progress, UI polish |

---

## 4 · Contributing

1. **Add resource** – edit `data/resources.json`  
2. **Add recipe** – drop file into `data/recipes/`  
3. **Add system** – new header in `src/systems/` and call in main loop  
4. **Add UI panel** – code in `src/ui/`

---

## 5 · Requirements

* C++20 compiler (GCC 12 / Clang 14 / MSVC 17.6)
* CMake ≥ 3.23
* ninja-build (optional)
