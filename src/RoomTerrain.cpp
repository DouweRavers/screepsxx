#include "RoomTerrain.hpp"
#include "JS.hpp"

namespace Screeps {

RoomTerrain::RoomTerrain(JS::Value value) : Object(std::move(value)) {}

std::string RoomTerrain::get(int x, int y) const {
    return value().call<std::string>("get", x, y);
}

} // namespace Screeps