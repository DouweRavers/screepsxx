#include "RoomTerrain.hpp"
#include "JS.hpp"

namespace Screeps {

RoomTerrain::RoomTerrain(JS::Value value) : Object(std::move(value)) {}

int RoomTerrain::get(int x, int y) const {
    return value().call<int>("get", x, y);
}

} // namespace Screeps