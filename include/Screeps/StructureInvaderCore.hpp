/**
 * @file StructureInvaderCore.hpp
 * @brief StructureInvaderCore class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureInvaderCore
 */
#ifndef SCREEPS_STRUCTURE_INVADER_CORE_HPP
#define SCREEPS_STRUCTURE_INVADER_CORE_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

class StructureSpawnSpawning;

/**
 * @class StructureInvaderCore
 * @brief A structure that spawns hostile creeps in invaded rooms.
 *
 * Invader Cores are enemy structures that periodically spawn hostile creeps.
 * They appear in rooms that are under attack by invaders and must be destroyed
 * to stop the spawning of enemy creeps.
 *
 * @see https://docs.screeps.com/api/#StructureInvaderCore
 * @see OwnedStructure
 */
class StructureInvaderCore : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureInvaderCore from a JavaScript value.
	 * @param value The JavaScript value representing the invader core.
	 */
	explicit StructureInvaderCore(JS::Value value);

	/**
	 * @brief Get the level of this invader core.
	 * @return The invader core level.
	 * @see https://docs.screeps.com/api/#StructureInvaderCore.level
	 */
	int level() const;

	/**
	 * @brief Get the ticks until this invader core deploys.
	 * @return The number of ticks until deployment.
	 * @see https://docs.screeps.com/api/#StructureInvaderCore.ticksToDeploy
	 */
	int ticksToDeploy() const;

	/**
	 * @brief Get the spawning information of this invader core.
	 * @return Optional StructureSpawnSpawning object if currently spawning.
	 * @see https://docs.screeps.com/api/#StructureInvaderCore.spawning
	 */
	std::optional<StructureSpawnSpawning> spawning() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_INVADER_CORE_HPP