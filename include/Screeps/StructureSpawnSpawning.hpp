/**
 * @file StructureSpawnSpawning.hpp
 * @brief StructureSpawnSpawning class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureSpawn.spawning
 */
#ifndef SCREEPS_STRUCTURE_SPAWN_SPAWNING_HPP
#define SCREEPS_STRUCTURE_SPAWN_SPAWNING_HPP

#include "Object.hpp"

#include <string>
#include <vector>

namespace Screeps {

class StructureSpawn;

/**
 * @class StructureSpawnSpawning
 * @brief Represents a creep currently being spawned.
 *
 * This object is returned by StructureSpawn.spawning and contains information
 * about a creep that is currently in the process of being spawned.
 *
 * @see https://docs.screeps.com/api/#StructureSpawn.spawning
 * @see Object
 */
class StructureSpawnSpawning : public Object
{
public:
	/**
	 * @brief Construct a StructureSpawnSpawning from a JavaScript value.
	 * @param value The JavaScript value representing the spawning info.
	 */
	explicit StructureSpawnSpawning(JS::Value value);

	/**
	 * @brief Get the spawn directions for this spawning creep.
	 * @return Vector of direction constants.
	 * @see https://docs.screeps.com/api/#StructureSpawnSpawning.directions
	 */
	std::vector<int> directions() const;

	/**
	 * @brief Get the name of the creep being spawned.
	 * @return The name of the new creep.
	 * @see https://docs.screeps.com/api/#StructureSpawnSpawning.name
	 */
	std::string name() const;

	/**
	 * @brief Get the total time needed to spawn this creep.
	 * @return The total spawn time in ticks.
	 * @see https://docs.screeps.com/api/#StructureSpawnSpawning.needTime
	 */
	int needTime() const;

	/**
	 * @brief Get the remaining time to spawn this creep.
	 * @return The remaining spawn time in ticks.
	 * @see https://docs.screeps.com/api/#StructureSpawnSpawning.remainingTime
	 */
	int remainingTime() const;

	/**
	 * @brief Get the spawn that is spawning this creep.
	 * @return The StructureSpawn object.
	 * @see https://docs.screeps.com/api/#StructureSpawnSpawning.spawn
	 */
	StructureSpawn spawn() const;

	/**
	 * @brief Cancel the spawning of this creep.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_FOUND).
	 * @see https://docs.screeps.com/api/#StructureSpawnSpawning.cancel
	 */
	int cancel();

	/**
	 * @brief Set the spawn directions for this spawning creep.
	 * @param directions Vector of direction constants.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#StructureSpawnSpawning.setDirections
	 */
	int setDirections(const std::vector<int>& directions);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_SPAWN_SPAWNING_HPP