/**
 * @file PowerCreep.hpp
 * @brief PowerCreep class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#PowerCreep
 */
#ifndef SCREEPS_POWER_CREEP_HPP
#define SCREEPS_POWER_CREEP_HPP

#include "RoomObject.hpp"
#include "JSON.hpp"

#include <map>
#include <optional>
#include <string>

namespace Screeps {

class Store;
class Structure;
class StructurePowerSpawn;
class StructurePowerBank;
class StructureController;
class RoomObject;
class Resource;

/**
 * @class PowerCreep
 * @brief A special unit with unique abilities that can be created at Power Spawns.
 *
 * Power Creeps are powerful units that have special abilities called "powers".
 * They can be created at StructurePowerSpawn and require power resource to spawn.
 * Power Creeps have a limited lifetime and will die after a certain number of ticks.
 *
 * @see https://docs.screeps.com/api/#PowerCreep
 * @see RoomObject
 */
class PowerCreep : public RoomObject
{
public:
	/**
	 * @struct PowerInfo
	 * @brief Information about a power's level and cooldown.
	 * @see https://docs.screeps.com/api/#PowerCreep
	 */
	struct PowerInfo
	{
		int level;      /**< The level of the power */
		int cooldown;   /**< The cooldown remaining for the power */
	};

	/**
	 * @brief Construct a PowerCreep from a JavaScript value.
	 * @param value The JavaScript value representing the power creep.
	 */
	explicit PowerCreep(JS::Value value);

	/**
	 * @brief Create a new Power Creep.
	 * @param name The name of the new power creep.
	 * @param className The class name of the new power creep.
	 * @return Result code (OK, ERR_NAME_EXISTS, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.create
	 */
	static int create(const std::string& name, const std::string& className);

	// Properties

	/**
	 * @brief Get the carry capacity of this power creep.
	 * @return The maximum amount of resources this power creep can carry.
	 * @see https://docs.screeps.com/api/#PowerCreep.carryCapacity
	 */
	int carryCapacity() const;

	/**
	 * @brief Get the class name of this power creep.
	 * @return The class name string.
	 * @see https://docs.screeps.com/api/#PowerCreep.className
	 */
	std::string className() const;

	/**
	 * @brief Get the time when this power creep will be deleted.
	 * @return The game tick when this power creep will be deleted.
	 * @see https://docs.screeps.com/api/#PowerCreep.deleteTime
	 */
	int deleteTime() const;

	/**
	 * @brief Get the current hit points of this power creep.
	 * @return The current hit points.
	 * @see https://docs.screeps.com/api/#PowerCreep.hits
	 */
	int hits() const;

	/**
	 * @brief Get the maximum hit points of this power creep.
	 * @return The maximum hit points.
	 * @see https://docs.screeps.com/api/#PowerCreep.hitsMax
	 */
	int hitsMax() const;

	/**
	 * @brief Get the unique identifier of this power creep.
	 * @return The unique ID string.
	 * @see https://docs.screeps.com/api/#PowerCreep.id
	 */
	std::string id() const;

	/**
	 * @brief Get the level of this power creep.
	 * @return The level number.
	 * @see https://docs.screeps.com/api/#PowerCreep.level
	 */
	int level() const;

	/**
	 * @brief Get the memory of this power creep.
	 * @return The JSON object containing custom memory data.
	 * @see https://docs.screeps.com/api/#PowerCreep.memory
	 */
	JSON memory() const;

	/**
	 * @brief Set the memory of this power creep.
	 * @param memory The JSON object to store in power creep memory.
	 * @see https://docs.screeps.com/api/#PowerCreep.memory
	 */
	void setMemory(const JSON& memory);

	/**
	 * @brief Check if this power creep belongs to you.
	 * @return true if you own this power creep, false otherwise.
	 * @see https://docs.screeps.com/api/#PowerCreep.my
	 */
	bool my() const;

	/**
	 * @brief Get the name of this power creep.
	 * @return The name string.
	 * @see https://docs.screeps.com/api/#PowerCreep.name
	 */
	std::string name() const;

	/**
	 * @brief Get the owner of this power creep.
	 * @return The username of the owner.
	 * @see https://docs.screeps.com/api/#PowerCreep.owner
	 */
	std::string owner() const;

	/**
	 * @brief Get the store of this power creep.
	 * @return The Store object containing resources carried by this power creep.
	 * @see https://docs.screeps.com/api/#PowerCreep.store
	 */
	Store store() const;

	/**
	 * @brief Get the spawn cooldown time of this power creep.
	 * @return The number of ticks until this power creep can spawn again.
	 * @see https://docs.screeps.com/api/#PowerCreep.spawnCooldownTime
	 */
	int spawnCooldownTime() const;

	/**
	 * @brief Get the ticks to live for this power creep.
	 * @return The number of ticks this power creep will live.
	 * @see https://docs.screeps.com/api/#PowerCreep.ticksToLive
	 */
	int ticksToLive() const;

	// Methods

	/**
	 * @brief Cancel an order for this power creep.
	 * @param methodName The name of the method/order to cancel.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_FOUND).
	 * @see https://docs.screeps.com/api/#PowerCreep.cancelOrder
	 */
	int cancelOrder(const std::string& methodName);

	/**
	 * @brief Delete this power creep.
	 * @param cancel If true, cancel the delete order instead of confirming it.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#PowerCreep.deleteCreep
	 */
	int deleteCreep(bool cancel = false);

	/**
	 * @brief Drop a resource on the ground.
	 * @param resourceType The type of resource to drop.
	 * @param amount The amount of resource to drop (optional, defaults to all).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.drop
	 */
	int drop(const std::string& resourceType, std::optional<int> amount = std::nullopt);

	/**
	 * @brief Enable a room for this power creep.
	 * @param controller The controller of the room to enable.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE).
	 * @see https://docs.screeps.com/api/#PowerCreep.enableRoom
	 */
	int enableRoom(const StructureController& controller);

	/**
	 * @brief Move this power creep in a direction.
	 * @param direction The direction to move (use TOP, RIGHT, BOTTOM, LEFT, etc. constants).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY, ERR_TIRED, ERR_NO_BODYPART, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.move
	 */
	int move(int direction);

	/**
	 * @brief Move this power creep towards another power creep.
	 * @param direction The target power creep to move towards.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY, ERR_TIRED, ERR_NO_BODYPART, ERR_INVALID_TARGET, ERR_NOT_FOUND).
	 * @see https://docs.screeps.com/api/#PowerCreep.move
	 */
	int move(const PowerCreep& direction);

	/**
	 * @brief Move this power creep along a pre-computed path.
	 * @param path The path to follow.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY, ERR_TIRED, ERR_NO_BODYPART, ERR_INVALID_ARGS, ERR_NOT_FOUND).
	 * @see https://docs.screeps.com/api/#PowerCreep.moveByPath
	 */
	int moveByPath(const std::string& path);

	/**
	 * @brief Move this power creep to a position.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 * @param options Movement options (optional).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY, ERR_TIRED, ERR_NO_BODYPART, ERR_INVALID_TARGET, ERR_NOT_FOUND, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.moveTo
	 */
	int moveTo(int x, int y, const std::optional<JSON>& options = std::nullopt);

	/**
	 * @brief Move this power creep to a RoomPosition.
	 * @param target The target position.
	 * @param options Movement options (optional).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY, ERR_TIRED, ERR_NO_BODYPART, ERR_INVALID_TARGET, ERR_NOT_FOUND, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.moveTo
	 */
	int moveTo(const RoomPosition& target, const std::optional<JSON>& options = std::nullopt);

	/**
	 * @brief Move this power creep to a RoomObject.
	 * @param target The target room object.
	 * @param options Movement options (optional).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY, ERR_TIRED, ERR_NO_BODYPART, ERR_INVALID_TARGET, ERR_NOT_FOUND, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.moveTo
	 */
	int moveTo(const RoomObject& target, const std::optional<JSON>& options = std::nullopt);

	/**
	 * @brief Set whether to notify when this power creep is attacked.
	 * @param enabled Whether to enable notifications.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.notifyWhenAttacked
	 */
	int notifyWhenAttacked(bool enabled);

	/**
	 * @brief Pick up a resource from the ground.
	 * @param target The resource to pick up.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_FULL).
	 * @see https://docs.screeps.com/api/#PowerCreep.pickup
	 */
	int pickup(const Resource& target);

	/**
	 * @brief Rename this power creep.
	 * @param name The new name for the power creep.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NAME_EXISTS, ERR_BUSY, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#PowerCreep.rename
	 */
	int rename(const std::string& name);

	/**
	 * @brief Renew this power creep at a Power Spawn.
	 * @param target The Power Spawn to renew at.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_NOT_ENOUGH_ENERGY, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#PowerCreep.renew
	 */
	int renew(const StructurePowerSpawn& target);

	/**
	 * @brief Renew this power creep at a Power Bank.
	 * @param target The Power Bank to renew at.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_NOT_ENOUGH_ENERGY, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#PowerCreep.renew
	 */
	int renew(const StructurePowerBank& target);

	/**
	 * @brief Make this power creep say something.
	 * @param message The message to say.
	 * @param publicMessage If true, the message will be visible to all players (default: false).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#PowerCreep.say
	 */
	int say(const std::string& message, bool publicMessage = false);

	/**
	 * @brief Spawn this power creep at a Power Spawn.
	 * @param powerSpawn The Power Spawn to spawn at.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY, ERR_NOT_ENOUGH_ENERGY, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_RCL_NOT_ENOUGH).
	 * @see https://docs.screeps.com/api/#PowerCreep.spawn
	 */
	int spawn(const StructurePowerSpawn& powerSpawn);

	/**
	 * @brief Kill this power creep immediately.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#PowerCreep.suicide
	 */
	int suicide();

	/**
	 * @brief Transfer a resource to another power creep.
	 * @param target The target power creep.
	 * @param resourceType The type of resource to transfer.
	 * @param amount The amount of resource to transfer (optional, defaults to all).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_ARGS, ERR_FULL).
	 * @see https://docs.screeps.com/api/#PowerCreep.transfer
	 */
	int transfer(const PowerCreep& target, const std::string& resourceType, std::optional<int> amount = std::nullopt);

	/**
	 * @brief Transfer a resource to a structure.
	 * @param target The target structure.
	 * @param resourceType The type of resource to transfer.
	 * @param amount The amount of resource to transfer (optional, defaults to all).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_ARGS, ERR_FULL).
	 * @see https://docs.screeps.com/api/#PowerCreep.transfer
	 */
	int transfer(const Structure& target, const std::string& resourceType, std::optional<int> amount = std::nullopt);

	/**
	 * @brief Upgrade a power for this power creep.
	 * @param power The name of the power to upgrade.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_ARGS, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#PowerCreep.upgrade
	 */
	int upgrade(const std::string& power);

	/**
	 * @brief Use a power on a target.
	 * @param power The name of the power to use.
	 * @param target The target to use the power on (optional).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_ARGS, ERR_BUSY, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE).
	 * @see https://docs.screeps.com/api/#PowerCreep.usePower
	 */
	int usePower(const std::string& power, const std::optional<RoomObject>& target = std::nullopt);

	/**
	 * @brief Withdraw a resource from a target.
	 * @param target The target to withdraw from.
	 * @param resourceType The type of resource to withdraw.
	 * @param amount The amount of resource to withdraw (optional, defaults to all).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_INVALID_ARGS, ERR_NOT_ENOUGH_RESOURCES, ERR_FULL).
	 * @see https://docs.screeps.com/api/#PowerCreep.withdraw
	 */
	int withdraw(const RoomObject& target, const std::string& resourceType, std::optional<int> amount = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_POWER_CREEP_HPP