/**
 * @file Structure.hpp
 * @brief Base class for all structure types in Screeps.
 * 
 * This file defines the Structure class which serves as the base class for
 * all structure types in the Screeps game. Structures are stationary objects
 * that can be built in rooms, including spawns, towers, walls, roads, and many others.
 */

#ifndef SCREEPS_STRUCTURE_HPP
#define SCREEPS_STRUCTURE_HPP

#include "Constants.hpp"
#include "RoomObject.hpp"

namespace Screeps {

/**
 * @class Structure
 * @brief Base class for all structure types.
 * 
 * Structure is the base class for all buildable objects in Screeps that
 * remain stationary in a room. All structures have:
 * - Hit points and maximum hit points (@ref hits(), @ref hitsMax())
 * - A unique identifier (@ref id())
 * - A structure type (@ref structureType())
 * - The ability to be destroyed (@ref destroy())
 * - An active state check (@ref isActive())
 * 
 * Different structure types include:
 * - Spawn: Creates creeps
 * - Extension: Additional energy storage for spawning
 * - Tower: Defends the room
 * - Wall/Rampart: Blocks movement
 * - Road: Decreases movement cost
 * - Storage/Terminal: Stores resources
 * - And many others
 * 
 * All structures are accessible through @ref Game.structures and can be
 * found using @ref Room::find with FIND_STRUCTURES.
 * 
 * @see RoomObject, OwnedStructure, Game::structures()
 */
class Structure : public RoomObject
{
public:
	/**
	 * @brief Construct a Structure from a JavaScript value.
	 * @param value The JavaScript Structure value.
	 */
	explicit Structure(JS::Value value);

	/**
	 * @brief Get the current hit points of the structure.
	 * @return int The current amount of hit points.
	 * 
	 * @see hitsMax()
	 */
	int hits() const;

	/**
	 * @brief Get the maximum hit points of the structure.
	 * @return int The maximum amount of hit points.
	 * 
	 * @see hits()
	 */
	int hitsMax() const;

	/**
	 * @brief Get the unique identifier of the structure.
	 * @return std::string The unique ID.
	 * 
	 * @see Game::getObjectById
	 */
	std::string id() const;

	/**
	 * @brief Get the type of the structure.
	 * @return std::string The structure type constant (e.g., "spawn", "tower", "wall").
	 * 
	 * @see STRUCTURE_* constants
	 */
	std::string structureType() const;

	/**
	 * @brief Destroy this structure immediately.
	 * 
	 * Removes the structure from the game. You can only destroy your own
	 * structures, and only if there are no hostile creeps in the room.
	 * 
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your structure or not in your room
	 *   - ERR_BUSY (-4): Hostile creeps are in the room
	 */
	int destroy();

	/**
	 * @brief Check if this structure is active.
	 * 
	 * A structure is active if:
	 * - The room controller level is sufficient for this structure type
	 * - The structure is not destroyed
	 * 
	 * If inactive, the structure is highlighted with red in the game.
	 * 
	 * @return bool True if the structure is active, false otherwise.
	 */
	bool isActive();

	/**
	 * @brief Toggle auto-notification when the structure is attacked.
	 * 
	 * Toggle whether to receive email notifications when this structure
	 * is under attack.
	 * 
	 * @param enabled Whether to enable notifications.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your structure
	 *   - ERR_INVALID_ARGS (-10): Invalid boolean value
	 */
	int notifyWhenAttacked(bool enabled);

	/**
	 * @brief The find constant for structures.
	 * 
	 * Use this with Room::find() to find all structures.
	 * 
	 * @see Room::find
	 */
	const static int findConstant = Screeps::FIND_STRUCTURES;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_HPP
