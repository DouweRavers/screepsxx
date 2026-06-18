/**
 * @file StructureSpawn.hpp
 * @brief Represents a spawn structure that can create creeps.
 * 
 * This file defines the StructureSpawn class which represents a spawn
 * structure in Screeps. Spawns are the primary way to create new creeps
 * and are essential for any colony.
 */

#ifndef SCREEPS_STRUCTURE_SPAWN_HPP
#define SCREEPS_STRUCTURE_SPAWN_HPP

#include "OwnedStructure.hpp"

#include <optional>

namespace Screeps {

class Creep;
class Store;

/**
 * @class StructureSpawn
 * @brief A structure that can spawn new creeps.
 * 
 * A StructureSpawn (or simply "spawn") is the colony center that can create,
 * renew, and recycle creeps. Each spawn has:
 * - 300 energy capacity
 * - 5000 hit points
 * - Auto-regenerates 1 energy per tick when room energy is below 300
 * 
 * The number of spawns available depends on the room controller level:
 * - Level 1-6: 1 spawn
 * - Level 7: 2 spawns
 * - Level 8: 3 spawns
 * 
 * All spawns are accessible through @ref Game.spawns and can be found using
 * @ref Room::find with FIND_MY_SPAWNS.
 * 
 * @see OwnedStructure, Creep, Game::spawns()
 */
class StructureSpawn : public OwnedStructure
{
public:
	/**
	 * @class Spawning
	 * @brief Represents the creep currently being spawned.
	 * 
	 * When a spawn is in the process of spawning a creep, this object
	 * contains information about the spawning process.
	 */
	class Spawning;

	/**
	 * @brief Construct a StructureSpawn from a JavaScript value.
	 * @param obj The JavaScript spawn value.
	 */
	explicit StructureSpawn(JS::Value obj);

	/**
	 * @brief Get the spawn's memory object.
	 * 
	 * This is a shorthand to Memory.spawns[spawn.name].
	 * Use this to store and retrieve spawn-specific data.
	 * 
	 * @return JSON The spawn's memory object.
	 * 
	 * @see setMemory(), name()
	 */
	JSON memory() const;

	/**
	 * @brief Set the spawn's memory object.
	 * 
	 * @param memory The new memory content as a JSON object.
	 * 
	 * @see memory()
	 */
	void setMemory(const JSON&);

	/**
	 * @brief Get the spawn's name.
	 * @return std::string The spawn's name.
	 * 
	 * @see Game::spawns()
	 */
	std::string name() const;

	/**
	 * @brief Get information about the creep currently being spawned.
	 * 
	 * @return std::optional<Spawning> Spawning object if a creep is being spawned, or nullopt otherwise.
	 * 
	 * @see Spawning
	 */
	std::optional<Spawning> spawning() const;

	/**
	 * @brief Get the spawn's store (energy inventory).
	 * 
	 * The store contains energy that can be used for spawning creeps.
	 * 
	 * @return Store The spawn's store object.
	 * 
	 * @see Store
	 */
	Store store() const;

	/**
	 * @brief Spawn a new creep with the specified body and name.
	 * 
	 * Starts the creep spawning process. The required energy is withdrawn
	 * from the spawn and its extensions.
	 * 
	 * Each body part takes 3 ticks to spawn. The spawn cannot perform
	 * other actions while spawning.
	 * 
	 * @param body Array of body part types. Use BODYPART_* constants:
	 *   - MOVE, WORK, CARRY, ATTACK, RANGED_ATTACK, HEAL, TOUGH, CLAIM
	 *   - Maximum 50 parts, minimum 1 part
	 * @param name The name for the new creep (max 100 characters, must be unique).
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your spawn
	 *   - ERR_NAME_EXISTS (-3): Name already exists
	 *   - ERR_BUSY (-4): Spawn is already spawning
	 *   - ERR_NOT_ENOUGH_ENERGY (-6): Not enough energy
	 *   - ERR_INVALID_ARGS (-10): Invalid body or name
	 *   - ERR_RCL_NOT_ENOUGH (-14): Insufficient RCL
	 * 
	 * @see spawnCreep(const vector<string>&, const string&, const JSON&)
	 */
	int spawnCreep(const std::vector<std::string>& body, const std::string& name);

	/**
	 * @brief Spawn a new creep with additional options.
	 * 
	 * @param body Array of body part types.
	 * @param name The name for the new creep.
	 * @param options Optional JSON object with spawning options:
	 *   - memory: Initial memory for the new creep
	 *   - energyStructures: Array of spawns/extensions to use for energy
	 *   - dryRun: If true, only check if spawning is possible
	 *   - directions: Array of desired spawn directions
	 * @return int Error code (see spawnCreep(const vector<string>&, const string&)).
	 * 
	 * @see spawnCreep(const vector<string>&, const string&)
	 */
	int spawnCreep(const std::vector<std::string>& body, const std::string& name, const JSON& options);

	/**
	 * @brief Recycle a creep, returning resources to the spawn.
	 * 
	 * Kills the target creep and returns up to 100% of resources spent on
	 * its spawning and boosting, depending on remaining time to live.
	 * Energy return is limited to 125 units per body part.
	 * The target must be at an adjacent square.
	 * 
	 * @param target The creep to recycle.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your spawn or creep
	 *   - ERR_INVALID_TARGET (-7): Invalid creep
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_RCL_NOT_ENOUGH (-14): Insufficient RCL
	 * 
	 * @see renewCreep
	 */
	int recycleCreep(const Creep& target);

	/**
	 * @brief Renew a creep's time to live.
	 * 
	 * Increases the target creep's remaining time to live.
	 * The target must be at an adjacent square and must not have CLAIM parts.
	 * The spawn must not be busy with spawning.
	 * 
	 * Each execution increases the creep's timer by:
	 * floor(600 / body_size) ticks
	 * 
	 * Energy required:
	 * ceil(creep_cost / 2.5 / body_size)
	 * 
	 * Renewing a creep removes all of its boosts.
	 * 
	 * @param target The creep to renew.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your spawn or creep
	 *   - ERR_BUSY (-4): Spawn is spawning
	 *   - ERR_NOT_ENOUGH_ENERGY (-6): Not enough energy
	 *   - ERR_INVALID_TARGET (-7): Invalid creep or has CLAIM parts
	 *   - ERR_FULL (-8): Creep's timer is full
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_RCL_NOT_ENOUGH (-14): Insufficient RCL
	 * 
	 * @see recycleCreep
	 */
	int renewCreep(const Creep& target);
};

/**
 * @brief Represents the creep currently being spawned by a StructureSpawn.
 * 
 * This object contains information about the spawning process and allows
 * some control over it.
 */
class StructureSpawn::Spawning : public Object
{
public:
	/**
	 * @brief Construct a Spawning object from a JavaScript value.
	 * @param value The JavaScript spawning value.
	 */
	explicit Spawning(JS::Value value);

	/**
	 * @brief Get the spawn directions for the new creep.
	 * 
	 * Returns an array of direction constants that the new creep will use
	 * when spawned.
	 * 
	 * @return std::vector<int> Array of direction constants.
	 * 
	 * @see setDirections
	 */
	std::vector<int> directions() const;

	/**
	 * @brief Get the name of the creep being spawned.
	 * @return std::string The creep's name.
	 */
	std::string name() const;

	/**
	 * @brief Get the total time needed to spawn the creep.
	 * @return int The total spawning time in ticks.
	 */
	int needTime() const;

	/**
	 * @brief Get the remaining time to complete spawning.
	 * @return int The remaining spawning time in ticks.
	 */
	int remainingTime() const;

	/**
	 * @brief Get the spawn that is performing the spawning.
	 * @return StructureSpawn The spawn object.
	 */
	StructureSpawn spawn();

	/**
	 * @brief Cancel the spawning process.
	 * 
	 * Cancels spawning immediately. Energy spent on spawning is not returned.
	 * 
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your spawn
	 */
	int cancel();

	/**
	 * @brief Set the desired spawn directions for the new creep.
	 * 
	 * Sets the directions the new creep should move when spawned.
	 * 
	 * @param directions Array of direction constants:
	 *   - TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT, LEFT, TOP_LEFT
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your spawn
	 *   - ERR_INVALID_ARGS (-10): Invalid directions array
	 * 
	 * @see directions()
	 */
	int setDirections(const std::vector<int>& directions);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_SPAWN_HPP
