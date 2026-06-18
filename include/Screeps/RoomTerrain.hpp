#ifndef SCREEPS_ROOM_TERRAIN_HPP
#define SCREEPS_ROOM_TERRAIN_HPP

#include "Object.hpp"
#include <string>

namespace Screeps {

class RoomTerrain : public Object
{
public:
    explicit RoomTerrain(JS::Value value);

    // Returns the terrain type at (x, y): "plain", "wall", or "swamp"
    std::string get(int x, int y) const;
};

} // namespace Screeps

#endif // SCREEPS_ROOM_TERRAIN_HPP