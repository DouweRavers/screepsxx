/**
 * @file StructureKeeperLair.hpp
 * @brief StructureKeeperLair class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureKeeperLair
 */
#ifndef SCREEPS_STRUCTURE_KEEPER_LAIR_HPP
#define SCREEPS_STRUCTURE_KEEPER_LAIR_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

/**
 * @class StructureKeeperLair
 * @brief A structure that spawns source keeper creeps.
 *
 * Keeper Lairs are structures that periodically spawn source keeper creeps
 * which defend the room's sources. They appear in rooms with source keepers
 * and must be dealt with strategically.
 *
 * @see https://docs.screeps.com/api/#StructureKeeperLair
 * @see OwnedStructure
 */
class StructureKeeperLair : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureKeeperLair from a JavaScript value.
	 * @param value The JavaScript value representing the keeper lair.
	 */
	explicit StructureKeeperLair(JS::Value value);

	/**
	 * @brief Get the ticks until this keeper lair spawns.
	 * @return The number of ticks until the next spawn.
	 * @see https://docs.screeps.com/api/#StructureKeeperLair.ticksToSpawn
	 */
	int ticksToSpawn() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_KEEPER_LAIR_HPP