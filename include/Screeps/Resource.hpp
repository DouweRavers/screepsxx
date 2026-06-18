/**
 * @file Resource.hpp
 * @brief Represents a dropped resource pile on the ground.
 * 
 * This file defines the Resource class which represents a dropped resource
 * (like energy, minerals, etc.) that appears when a creep drops resources or
 * when resources are naturally present in the room.
 */

#ifndef SCREEPS_RESOURCE_HPP
#define SCREEPS_RESOURCE_HPP

#include "RoomObject.hpp"

namespace Screeps {

/**
 * @class Resource
 * @brief A dropped resource pile that can be picked up.
 * 
 * A Resource represents any dropped resource that appears on the ground
 * in a room. This can be energy dropped by creeps, resources from destroyed
 * structures, or other resource deposits.
 * 
 * Dropped resource piles decay over time. The decay rate is:
 * ceil(amount / 1000) units per tick.
 * 
 * Resources can be picked up by creeps with CARRY body parts using
 * Creep::pickup().
 * 
 * All resources can be found using Room::find() with FIND_DROPPED_RESOURCES
 * or by looking at positions with LOOK_RESOURCES or LOOK_ENERGY.
 * 
 * @see RoomObject, Creep::pickup(), Room::find()
 */
class Resource : public RoomObject
{
public:
	/**
	 * @brief Construct a Resource from a JavaScript value.
	 * @param value The JavaScript Resource value.
	 */
	explicit Resource(JS::Value value);

	/**
	 * @brief Get the amount of resource in the pile.
	 * @return int The number of resource units.
	 */
	int amount() const;

	/**
	 * @brief Get the unique identifier of the resource pile.
	 * @return std::string The unique ID.
	 * 
	 * @see Game::getObjectById
	 */
	std::string id() const;

	/**
	 * @brief Get the type of resource.
	 * @return std::string The resource type constant (e.g., RESOURCE_ENERGY, RESOURCE_UTRIUM).
	 * 
	 * @see RESOURCE_* constants
	 */
	std::string resourceType() const;
};

} // namespace Screeps

#endif // SCREEPS_RESOURCE_HPP
