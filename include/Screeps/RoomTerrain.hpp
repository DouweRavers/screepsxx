/**
 * @file RoomTerrain.hpp
 * @brief RoomTerrain class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#RoomTerrain
 */
#ifndef SCREEPS_ROOM_TERRAIN_HPP
#define SCREEPS_ROOM_TERRAIN_HPP

#include "Object.hpp"
#include <string>

namespace Screeps {

/**
 * @class RoomTerrain
 * @brief Provides access to the terrain data of a room.
 *
 * RoomTerrain allows you to query the terrain type at any position in a room.
 * The terrain can be plain (0), wall (1), or swamp (2). This information is useful
 * for pathfinding and movement calculations.
 *
 * @see https://docs.screeps.com/api/#RoomTerrain
 * @see Object
 * @see TERRAIN_MASK_WALL, TERRAIN_MASK_SWAMP, TERRAIN_MASK_LAVA in Constants.hpp
 */
class RoomTerrain : public Object
{
public:
    /**
     * @brief Construct a RoomTerrain from a JavaScript value.
     * @param value The JavaScript value representing the room terrain.
     */
    explicit RoomTerrain(JS::Value value);

    /**
     * @brief Get the terrain type at a specific position.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return The terrain type: 0 (plain), 1 (wall), or 2 (swamp).
     * @see https://docs.screeps.com/api/#RoomTerrain.get
     */
    int get(int x, int y) const;
};

} // namespace Screeps

#endif // SCREEPS_ROOM_TERRAIN_HPP