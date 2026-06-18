/**
 * @file StructureNuker.hpp
 * @brief StructureNuker class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureNuker
 */
#ifndef SCREEPS_STRUCTURE_NUKER_HPP
#define SCREEPS_STRUCTURE_NUKER_HPP

#include "OwnedStructure.hpp"
#include "JSON.hpp"

#include <string>

namespace Screeps {

class RoomPosition;
class Store;

/**
 * @class StructureNuker
 * @brief A structure that can launch nuclear missiles.
 *
 * Nukers are structures that can launch nukes at distant rooms. They require
 * energy and ghodium resources to operate and have a long cooldown period
 * between launches.
 *
 * @see https://docs.screeps.com/api/#StructureNuker
 * @see OwnedStructure
 */
class StructureNuker : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureNuker from a JavaScript value.
	 * @param value The JavaScript value representing the nuker.
	 */
	explicit StructureNuker(JS::Value value);

	/**
	 * @brief Get the current cooldown of this nuker.
	 * @return The remaining cooldown ticks.
	 * @see https://docs.screeps.com/api/#StructureNuker.cooldown
	 */
	int cooldown() const;

	/**
	 * @brief Get the store of this nuker.
	 * @return The Store object containing resources in this nuker.
	 * @see https://docs.screeps.com/api/#StructureNuker.store
	 */
	Store store() const;

	/**
	 * @brief Launch a nuke at a target position.
	 * @param pos The target RoomPosition to launch the nuke at.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#StructureNuker.launchNuke
	 */
	int launchNuke(const RoomPosition& pos);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_NUKER_HPP