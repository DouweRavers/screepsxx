/**
 * @file Game.hpp
 * @brief The global Game object containing all gameplay information.
 * 
 * This file defines the GameObject class which represents the main global game
 * object in Screeps. It provides access to all game state including rooms, creeps,
 * structures, CPU information, and other global properties.
 */

#ifndef SCREEPS_GAME_HPP
#define SCREEPS_GAME_HPP

#include "Object.hpp"

#include <memory>

namespace Screeps {

class ConstructionSite;
class Creep;
class Flag;
class GameMap;
class GameMarket;
class PowerCreep;
class Room;
class RoomObject;
class StructureSpawn;
class Structure;

/**
 * @class GameObject
 * @brief The main global game object containing all gameplay information.
 * 
 * GameObject (accessed globally as @ref Game) is the primary entry point for
 * accessing game state. It provides access to:
 * - All rooms visible to your script (@ref rooms())
 * - All your creeps (@ref creeps())
 * - All your spawns (@ref spawns())
 * - All structures (@ref structures())
 * - CPU usage information (@ref cpu(), @ref cpuGetUsed())
 * - Global game time (@ref time())
 * - And many other game systems
 * 
 * This object is automatically populated by the Screeps game engine at the
 * beginning of each game tick.
 * 
 * @see Room, Creep, Structure
 */
class GameObject : public Object
{
public:
	/**
	 * @struct GCL
	 * @brief Global Control Level information.
	 * 
	 * The GCL (Global Control Level) determines how many rooms you can control.
	 * It increases as you control more rooms and decreases when you lose control.
	 */
	struct GCL
	{
		/** @brief The current GCL level (1-8). */
		int level;
		/** @brief The current progress towards the next GCL level. */
		int progress;
		/** @brief The total progress required to reach the next GCL level. */
		int progressTotal;
	};

	/** @typedef GPL
	 * @brief Global Power Level - same structure as GCL but for power.
	 * 
	 * GPL determines your power level and the number of power creeps you can spawn.
	 */
	using GPL = GCL;

	/**
	 * @struct Shard
	 * @brief Information about the current world shard.
	 * 
	 * A shard is a separate world instance in Screeps. Each shard has its own
	 * map and game state.
	 */
	struct Shard
	{
		/** @brief The name of the shard. */
		std::string name;
		/** @brief The type of the shard (currently always "normal"). */
		std::string type;
		/** @brief Whether this shard is the PTR (Public Test Realm). */
		bool ptr;
	};

	/**
	 * @brief Default constructor.
	 */
	GameObject();

	/**
	 * @brief Get all construction sites owned by you.
	 * 
	 * Returns a map of all your construction sites with their IDs as keys.
	 * Construction sites are structures that are currently being built.
	 * 
	 * @return std::map<std::string, ConstructionSite> Map of construction sites.
	 * 
	 * @see ConstructionSite, Room::createConstructionSite
	 */
	std::map<std::string, ConstructionSite> constructionSites() const;

	/**
	 * @brief Get the CPU information object.
	 * 
	 * Returns a JSON object containing:
	 * - limit: Your CPU limit for the current shard
	 * - tickLimit: Available CPU for the current tick
	 * - bucket: Accumulated unused CPU
	 * - shardLimits: CPU limits per shard
	 * - unlocked: Whether full CPU is unlocked
	 * - unlockedTime: Time until CPU unlock expires
	 * 
	 * @return JSON The CPU information object.
	 * 
	 * @see cpuGetUsed, cpuGetHeapStatistics, cpuHalt, cpuUnlock
	 */
	JSON cpu() const;

	/**
	 * @brief Get all creeps owned by you.
	 * 
	 * Returns a map of all your creeps with their names as keys.
	 * Creeps are your units that can move, harvest, build, attack, etc.
	 * 
	 * @return std::map<std::string, Creep> Map of creeps.
	 * 
	 * @see Creep, Room::find
	 */
	std::map<std::string, Creep> creeps() const;

	/**
	 * @brief Get all flags owned by you.
	 * 
	 * Returns a map of all your flags with their names as keys.
	 * Flags are markers you can place in rooms to remember locations.
	 * 
	 * @return std::map<std::string, Flag> Map of flags.
	 * 
	 * @see Flag, Room::createFlag
	 */
	std::map<std::string, Flag> flags() const;

	/**
	 * @brief Get your Global Control Level information.
	 * 
	 * @return GCL The current GCL level, progress, and progressTotal.
	 * 
	 * @see GPL, gpl()
	 */
	GCL gcl() const;

	/**
	 * @brief Get your Global Power Level information.
	 * 
	 * @return GPL The current GPL level, progress, and progressTotal.
	 * 
	 * @see GCL, gcl()
	 */
	GPL gpl() const;

	/**
	 * @brief Get the global map object.
	 * 
	 * The map object provides information about the world map including
	 * terrain, room status, and routing between rooms.
	 * 
	 * @return GameMap The global map object.
	 * 
	 * @see GameMap
	 */
	GameMap map() const;

	/**
	 * @brief Get the global market object.
	 * 
	 * The market object allows you to trade resources with other players
	 * through the in-game market system.
	 * 
	 * @return GameMarket The global market object.
	 * 
	 * @see GameMarket
	 */
	GameMarket market() const;

	/**
	 * @brief Get all power creeps owned by you.
	 * 
	 * Returns a map of all your power creeps with their names as keys.
	 * Power creeps are special immortal units with unique abilities.
	 * 
	 * @return std::map<std::string, PowerCreep> Map of power creeps.
	 * 
	 * @see PowerCreep
	 */
	std::map<std::string, PowerCreep> powerCreeps() const;

	/**
	 * @brief Get your account's global resources.
	 * 
	 * Returns a map of resource types to amounts for account-bound resources
	 * like pixels, CPU unlocks, access keys, and subscription tokens.
	 * 
	 * @return std::map<std::string, int> Map of resource types to amounts.
	 * 
	 * @see cpuUnlock, cpuGeneratePixel
	 */
	std::map<std::string, int> resources() const;

	/**
	 * @brief Get all rooms available to you.
	 * 
	 * Returns a map of all rooms that are currently visible to your script.
	 * A room is visible if you have a creep or owned structure in it.
	 * 
	 * @return std::map<std::string, Room> Map of room names to Room objects.
	 * 
	 * @see Room
	 */
	std::map<std::string, Room> rooms() const;

	/**
	 * @brief Get the current shard information.
	 * 
	 * @return Shard The shard information object.
	 * 
	 * @see Shard, GameMap
	 */
	Shard shard() const;

	/**
	 * @brief Get all spawns owned by you.
	 * 
	 * Returns a map of all your spawns with their names as keys.
	 * Spawns are structures that can create creeps.
	 * 
	 * @return std::map<std::string, StructureSpawn> Map of spawns.
	 * 
	 * @see StructureSpawn
	 */
	std::map<std::string, StructureSpawn> spawns() const;

	/**
	 * @brief Get all structures owned by you.
	 * 
	 * Returns a map of all your structures with their IDs as keys.
	 * 
	 * @return std::map<std::string, Structure> Map of structures.
	 * 
	 * @see Structure, Room::find
	 */
	std::map<std::string, Structure> structures() const;

	/**
	 * @brief Get the current game time.
	 * 
	 * Returns the system game tick counter which increments automatically
	 * on every tick.
	 * 
	 * @return int The current game tick.
	 */
	int time() const;

	/**
	 * @brief Get heap statistics for the JavaScript virtual machine.
	 * 
	 * Returns an object with heap statistics similar to Node.js's
	 * v8.getHeapStatistics(), plus an externally_allocated_size property.
	 * 
	 * @return JSON Object containing heap statistics:
	 *   - total_heap_size
	 *   - total_heap_size_executable
	 *   - total_physical_size
	 *   - total_available_size
	 *   - used_heap_size
	 *   - heap_size_limit
	 *   - externally_allocated_size
	 *   - etc.
	 */
	JSON cpuGetHeapStatistics();

	/**
	 * @brief Get the amount of CPU used so far in the current game tick.
	 * 
	 * Returns the CPU time used from the beginning of the current tick.
	 * Always returns 0 in Simulation mode.
	 * 
	 * @return double The CPU time used in the current tick.
	 * 
	 * @see cpu(), cpuHalt()
	 */
	double cpuGetUsed();

	/**
	 * @brief Reset the runtime environment and wipe all data in heap memory.
	 * 
	 * This method immediately stops execution and clears the heap.
	 * Use with caution as it will terminate your current tick's processing.
	 */
	void cpuHalt();

	/**
	 * @brief Allocate CPU limits to different shards.
	 * 
	 * Reallocates CPU limits across different shards. The total amount
	 * of CPU should remain equal to the current total. This method can
	 * only be used once per 12 hours.
	 * 
	 * @param limits A map of shard names to CPU limits.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_BUSY (-4): Cooldown period not over
	 *   - ERR_INVALID_ARGS (-10): Invalid limits object
	 * 
	 * @see cpu(), shard()
	 */
	int cpuSetShardLimits(const std::map<std::string, int>& limits);

	/**
	 * @brief Unlock full CPU for your account for 24 hours.
	 * 
	 * Consumes 1 CPU unlock resource bound to your account.
	 * If full CPU is not currently unlocked, it may take up to 5 minutes
	 * for the unlock to take effect.
	 * 
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): No CPU unlocks available
	 *   - ERR_FULL (-8): CPU already unlocked with subscription
	 * 
	 * @see resources(), cpuGeneratePixel
	 */
	int cpuUnlock();

	/**
	 * @brief Generate 1 pixel resource unit for 10000 CPU from your bucket.
	 * 
	 * Pixels are a special resource used for various game features.
	 * This consumes 10,000 CPU from your bucket.
	 * 
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): Not enough CPU in bucket
	 * 
	 * @see resources()
	 */
	int cpuGeneratePixel();

	/**
	 * @brief Get a game object by its unique ID.
	 * 
	 * Retrieves any game object (creep, structure, resource, etc.) by its
	 * unique identifier. Only objects from visible rooms can be accessed.
	 * 
	 * @param id The unique object ID.
	 * @return std::unique_ptr<RoomObject> The object if found, nullptr otherwise.
	 * 
	 * @see RoomObject::id()
	 */
	std::unique_ptr<RoomObject> getObjectById(const std::string& id);

	/**
	 * @brief Send a notification to your account email.
	 * 
	 * Sends a custom message to your profile email. You can schedule up to
	 * 20 notifications during one game tick. Not available in Simulation Room.
	 * 
	 * @param message The message text (max 1000 characters).
	 * @param groupInterval If set to 0 (default), notification is sent immediately.
	 *   Otherwise, notifications are grouped and sent later using the specified
	 *   time in minutes.
	 * 
	 * @see https://docs.screeps.com/api/#Game.notify
	 */
	void notify(const std::string& message, int groupInterval = 0);
};

/**
 * @brief The global Game object instance.
 * 
 * This is the main entry point for accessing all game state.
 * Access it using `Screeps::Game` in your code.
 * 
 * @see GameObject
 */
extern GameObject Game;

} // namespace Screeps

#endif // SCREEPS_GAME_HPP
