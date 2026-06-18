/**
 * @file Creep.hpp
 * @brief Represents a creep - your unit in the Screeps game.
 * 
 * This file defines the Creep class which represents a player-controlled unit
 * in the Screeps game. Creeps can move, harvest resources, build structures,
 * attack enemies, and perform many other actions. Each creep has a body composed
 * of various body parts (MOVE, WORK, CARRY, ATTACK, etc.) that determine its
 * capabilities.
 */

#ifndef SCREEPS_CREEP_H
#define SCREEPS_CREEP_H

#include "JSON.hpp"
#include "RoomObject.hpp"

#include <optional>

namespace Screeps {

class ConstructionSite;
class Resource;
class Source;
class Store;
class Structure;
class StructureController;

/**
 * @class Creep
 * @brief A player-controlled unit that can perform various actions.
 * 
 * Creeps are your main units in Screeps. Each creep consists of up to 50 body
 * parts that determine its capabilities. Creeps can:
 * - Move around the room (@ref move, @ref moveTo, @ref moveByPath)
 * - Harvest energy and resources (@ref harvest)
 * - Build and repair structures (@ref build, @ref repair)
 * - Attack other creeps and structures (@ref attack, @ref rangedAttack, @ref rangedMassAttack)
 * - Heal other creeps (@ref heal, @ref rangedHeal)
 * - Transfer and withdraw resources (@ref transfer, @ref withdraw)
 * - And many other actions
 * 
 * Each creep has a limited lifespan (default 1500 ticks, 600 ticks for creeps
 * with CLAIM parts) and will die when its time to live reaches 0.
 * 
 * All your creeps are accessible through @ref Game.creeps.
 * 
 * @see RoomObject, Game::creeps(), StructureSpawn
 */
class Creep : public RoomObject
{
public:
	/**
	 * @struct Body
	 * @brief Represents a single body part of a creep.
	 * 
	 * Each body part has a type (MOVE, WORK, CARRY, etc.), hit points,
	 * and optionally a boost mineral that enhances its capabilities.
	 */
	struct Body
	{
		/** @brief The boost mineral type if this part is boosted, or nullopt if not boosted. */
		std::optional<std::string> boost;
		/** @brief The type of this body part (MOVE, WORK, CARRY, ATTACK, etc.). */
		std::string type;
		/** @brief The remaining hit points of this body part. */
		int hits;
	};

	/**
	 * @brief Construct a Creep from a JavaScript value.
	 * @param value The JavaScript Creep value.
	 */
	explicit Creep(JS::Value);

	/**
	 * @brief Get the creep's body parts.
	 * 
	 * @return std::vector<Body> Array of Body objects representing each body part.
	 * 
	 * @see Body
	 */
	std::vector<Body> body() const;

	/**
	 * @brief Get the creep's fatigue value.
	 * 
	 * Fatigue is a movement indicator. If it's greater than zero, the creep
	 * cannot move. Fatigue decreases by the number of MOVE parts * 2 each tick.
	 * 
	 * @return int The current fatigue value.
	 */
	int fatigue() const;

	/**
	 * @brief Get the creep's current hit points.
	 * 
	 * @return int The current amount of hit points.
	 * 
	 * @see hitsMax()
	 */
	int hits() const;

	/**
	 * @brief Get the creep's maximum hit points.
	 * 
	 * @return int The maximum amount of hit points.
	 * 
	 * @see hits()
	 */
	int hitsMax() const;

	/**
	 * @brief Get the creep's unique identifier.
	 * 
	 * @return std::string The unique ID.
	 * 
	 * @see Game::getObjectById
	 */
	std::string id() const;

	/**
	 * @brief Get the creep's memory object.
	 * 
	 * This is a shorthand to Memory.creeps[creep.name]. Use this to store
	 * and retrieve creep-specific data that persists between game ticks.
	 * 
	 * @return JSON The creep's memory object.
	 * 
	 * @see setMemory(), name()
	 */
	JSON memory() const;

	/**
	 * @brief Set the creep's memory object.
	 * 
	 * @param memory The new memory content as a JSON object.
	 * 
	 * @see memory()
	 */
	void setMemory(const JSON& memory);

	/**
	 * @brief Check if this is your creep.
	 * 
	 * @return bool True if this creep is owned by you, false otherwise.
	 */
	bool my() const;

	/**
	 * @brief Get the creep's name.
	 * 
	 * @return std::string The creep's name.
	 * 
	 * @see Game::creeps()
	 */
	std::string name() const;

	/**
	 * @brief Get the creep's owner username.
	 * 
	 * @return std::string The username of the creep's owner.
	 */
	std::string owner() const;

	/**
	 * @brief Get the creep's current saying.
	 * 
	 * Returns the text message that the creep was saying at the last tick.
	 * 
	 * @return std::string The current saying text.
	 * 
	 * @see say()
	 */
	std::string saying() const;

	/**
	 * @brief Check if the creep is currently spawning.
	 * 
	 * @return bool True if the creep is still being spawned, false otherwise.
	 */
	bool spawning() const;

	/**
	 * @brief Get the creep's store (inventory).
	 * 
	 * The store contains all resources the creep is carrying.
	 * Access specific resources using store[resourceType].
	 * 
	 * @return Store The creep's store object.
	 * 
	 * @see Store, Store::getCapacity(), Store::getUsedCapacity()
	 */
	Store store() const;

	/**
	 * @brief Get the creep's remaining time to live.
	 * 
	 * Each creep has a limited lifespan. When this reaches 0, the creep dies.
	 * 
	 * @return int The number of ticks until the creep dies.
	 */
	int ticksToLive() const;

	// Action methods

	/**
	 * @brief Attack another creep, power creep, or structure.
	 * 
	 * Performs a short-ranged attack on the target. Requires ATTACK body parts.
	 * If the target is inside a rampart, the rampart is attacked instead.
	 * The target must be at an adjacent square.
	 * 
	 * @param target The target to attack (Creep, PowerCreep, or Structure).
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid target
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No ATTACK body parts
	 * 
	 * @see rangedAttack, rangedMassAttack
	 */
	int attack(const RoomObject& target);

	/**
	 * @brief Attack a room controller.
	 * 
	 * Decreases the controller's downgrade timer by 300 ticks per CLAIM body part,
	 * or reservation timer by 1 tick per CLAIM body part.
	 * If the controller is owned, it cannot be upgraded or attacked for 1000 ticks.
	 * The target must be at an adjacent square.
	 * 
	 * @param target The controller to attack.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid controller
	 *   - ERR_TIRED (-11): Attack cooldown active
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No CLAIM body parts
	 * 
	 * @see claimController, reserveController
	 */
	int attackController(const StructureController& target);

	/**
	 * @brief Build a structure at a construction site.
	 * 
	 * Builds the structure at the target construction site using carried energy.
	 * Requires WORK and CARRY body parts. The target must be within 3 squares.
	 * 
	 * @param target The construction site to build at.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): No energy carried
	 *   - ERR_INVALID_TARGET (-7): Invalid construction site
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No WORK body parts
	 * 
	 * @see ConstructionSite, repair
	 */
	int build(const ConstructionSite& target);

	/**
	 * @brief Cancel a pending order.
	 * 
	 * Cancels the order given during the current game tick.
	 * 
	 * @param methodName The name of the method to cancel (e.g., "move", "attack", etc.).
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_FOUND (-5): Order not found
	 */
	int cancelOrder(const std::string& methodName);

	/**
	 * @brief Claim a neutral room controller.
	 * 
	 * Takes control of a neutral controller under your ownership.
	 * Requires CLAIM body parts. The target must be at an adjacent square.
	 * You need sufficient Global Control Level to claim new rooms.
	 * 
	 * @param target The controller to claim.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid neutral controller
	 *   - ERR_FULL (-8): Too many rooms in Novice Area
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No CLAIM body parts
	 *   - ERR_GCL_NOT_ENOUGH (-15): Insufficient GCL
	 *   - ERR_ACCESS_DENIED (-16): No access to restricted shard
	 * 
	 * @see reserveController, attackController
	 */
	int claimController(const StructureController& target);

	/**
	 * @brief Dismantle a structure.
	 * 
	 * Dismantles any structure (even hostile) returning 50% of the energy
	 * spent on its repair. Requires WORK body parts.
	 * If the creep has an empty CARRY body part, the energy goes into it;
	 * otherwise it's dropped on the ground. The target must be adjacent.
	 * 
	 * @param target The structure to dismantle.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid structure
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No WORK body parts
	 * 
	 * @see build, repair
	 */
	int dismantle(const Structure& target);

	/**
	 * @brief Drop a resource on the ground.
	 * 
	 * Drops the specified resource at the creep's current position.
	 * 
	 * @param resourceType The type of resource to drop. Use RESOURCE_* constants.
	 * @param amount Optional amount to drop. If omitted, all carried amount is dropped.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): Not enough of the resource
	 *   - ERR_INVALID_ARGS (-10): Invalid resource type
	 * 
	 * @see pickup, transfer
	 */
	int drop(const std::string& resourceType, std::optional<int> amount);

	/**
	 * @brief Add a safe mode activation to a room controller.
	 * 
	 * The creep must be at an adjacent square to the target and have 1000 ghodium.
	 * 
	 * @param target The room controller.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): Not enough ghodium
	 *   - ERR_INVALID_TARGET (-7): Invalid controller
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 * 
	 * @see StructureController::activateSafeMode
	 */
	int generateSafeMode(const StructureController& target);

	/**
	 * @brief Get the number of active (undamaged) body parts of a specific type.
	 * 
	 * @param type The body part type to count. Use BODYPART_* constants:
	 *   - MOVE, WORK, CARRY, ATTACK, RANGED_ATTACK, HEAL, TOUGH, CLAIM
	 * @return int The number of active body parts of the specified type.
	 * 
	 * @see body()
	 */
	int getActiveBodyParts(const std::string& type);

	/**
	 * @brief Harvest energy or resources from a source, mineral, or deposit.
	 * 
	 * Harvests energy from sources or resources from minerals and deposits.
	 * Requires WORK body part. If the creep has an empty CARRY body part,
	 * the harvested resource goes into it; otherwise it's dropped on the ground.
	 * The target must be at an adjacent square.
	 * 
	 * @param target The source, mineral, or deposit to harvest.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep or room owned by another
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_FOUND (-5): Extractor not found
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): Source has no energy
	 *   - ERR_INVALID_TARGET (-7): Invalid target
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_TIRED (-11): Extractor or deposit cooling down
	 *   - ERR_NO_BODYPART (-12): No WORK body parts
	 * 
	 * @see Source, Mineral, Deposit
	 */
	int harvest(const Source& target);

	/**
	 * @brief Heal another creep.
	 * 
	 * Restores the target creep's damaged body parts and increases hits.
	 * Requires HEAL body parts. The target must be at an adjacent square.
	 * 
	 * @param target The creep to heal.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid creep
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No HEAL body parts
	 * 
	 * @see rangedHeal
	 */
	int heal(const Creep& target);

	/**
	 * @brief Move the creep in a specific direction.
	 * 
	 * Requires MOVE body parts, or another creep nearby pulling.
	 * 
	 * @param direction One of the direction constants:
	 *   - TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT, LEFT, TOP_LEFT
	 *   - Or another Creep object (the direction creep)
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_IN_RANGE (-9): Target creep too far
	 *   - ERR_INVALID_ARGS (-10): Invalid direction
	 *   - ERR_TIRED (-11): Fatigue > 0
	 *   - ERR_NO_BODYPART (-12): No MOVE body parts
	 * 
	 * @see moveTo, moveByPath, pull
	 */
	int move(int direction);

	/**
	 * @brief Move the creep in the direction of another creep.
	 * 
	 * @param direction The creep whose position determines the direction.
	 * @return int Error code (see move(int)).
	 */
	int move(const Creep& direction);

	/**
	 * @brief Move the creep using a predefined path.
	 * 
	 * Uses a path that was previously found using pathfinding methods.
	 * Requires MOVE body parts.
	 * 
	 * @param path The serialized path string or path array.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_FOUND (-5): Path doesn't match creep location
	 *   - ERR_INVALID_ARGS (-10): Invalid path
	 *   - ERR_TIRED (-11): Fatigue > 0
	 *   - ERR_NO_BODYPART (-12): No MOVE body parts
	 * 
	 * @see RoomPosition::findPathTo, Room::findPath
	 */
	int moveByPath(const std::string& path);

	/**
	 * @brief Move the creep to a specific position or object.
	 * 
	 * Finds the optimal path to the target and moves one step along it.
	 * If the target is in another room, uses the exit as the target.
	 * Requires MOVE body parts.
	 * 
	 * @param x The target X coordinate (same room only).
	 * @param y The target Y coordinate (same room only).
	 * @param options Optional JSON object with options:
	 *   - reusePath: Reuse path from memory for N ticks (default: 5)
	 *   - serializeMemory: Serialize path in memory (default: true)
	 *   - noPathFinding: Only use memorized path
	 *   - Any options supported by Room.findPath()
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_NO_PATH (-2): No path found
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_FOUND (-5): No memorized path
	 *   - ERR_INVALID_TARGET (-7): Invalid target
	 *   - ERR_TIRED (-11): Fatigue > 0
	 *   - ERR_NO_BODYPART (-12): No MOVE body parts
	 */
	int moveTo(int x, int y, const std::optional<JSON>& options = std::nullopt);

	/**
	 * @brief Move the creep to a RoomPosition.
	 * 
	 * @param target The target position (can be in any room).
	 * @param options Optional JSON object with options.
	 * @return int Error code (see moveTo(int, int, ...)).
	 */
	int moveTo(const RoomPosition& target, const std::optional<JSON>& options = std::nullopt);

	/**
	 * @brief Move the creep to a RoomObject.
	 * 
	 * @param target The target object (uses its position).
	 * @param options Optional JSON object with options.
	 * @return int Error code (see moveTo(int, int, ...)).
	 */
	int moveTo(const RoomObject& target, const std::optional<JSON>& options = std::nullopt);

	/**
	 * @brief Toggle auto-notification when the creep is attacked.
	 * 
	 * Toggle whether to receive email notifications when this creep is
	 * under attack.
	 * 
	 * @param enabled Whether to enable notifications.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_ARGS (-10): Invalid boolean value
	 */
	int notifyWhenAttacked(bool enabled);

	/**
	 * @brief Pick up a resource from the ground.
	 * 
	 * Picks up a dropped resource at an adjacent square.
	 * Requires CARRY body parts.
	 * 
	 * @param target The resource to pick up.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid resource
	 *   - ERR_FULL (-8): Creep carry is full
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 * 
	 * @see drop, withdraw
	 */
	int pickup(const Resource& target);

	/**
	 * @brief Pull another creep.
	 * 
	 * Helps another creep to follow this creep. The fatigue generated
	 * for the target's move is added to this creep instead.
	 * Requires MOVE body parts. The target must be at an adjacent square.
	 * This creep must move elsewhere, and the target must move towards this creep.
	 * 
	 * @param target The creep to pull.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid creep
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 * 
	 * @see move
	 */
	int pull(const Creep& target);

	/**
	 * @brief Attack a target at range.
	 * 
	 * Performs a ranged attack on the target. Requires RANGED_ATTACK body parts.
	 * If the target is inside a rampart, the rampart is attacked instead.
	 * The target must be within 3 squares.
	 * 
	 * @param target The creep or structure to attack.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid target
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No RANGED_ATTACK body parts
	 * 
	 * @see attack, rangedMassAttack
	 */
	int rangedAttack(const Creep& target);

	/**
	 * @brief Attack a structure at range.
	 * 
	 * @param target The structure to attack.
	 * @return int Error code (see rangedAttack(const Creep&)).
	 */
	int rangedAttack(const Structure& target);

	/**
	 * @brief Heal a target creep at range.
	 * 
	 * Heals another creep at a distance. Requires HEAL body parts.
	 * The target must be within 3 squares.
	 * 
	 * @param target The creep to heal.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid creep
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No HEAL body parts
	 * 
	 * @see heal
	 */
	int rangedHeal(const Creep& target);

	/**
	 * @brief Attack all hostile creeps and structures within range.
	 * 
	 * Performs a ranged mass attack on all hostile units within 3 squares.
	 * Requires RANGED_ATTACK body parts. The attack power depends on the
	 * range to each target. Friendly units are not affected.
	 * 
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NO_BODYPART (-12): No RANGED_ATTACK body parts
	 * 
	 * @see rangedAttack
	 */
	int rangedMassAttack();

	/**
	 * @brief Repair a damaged structure.
	 * 
	 * Repairs a damaged structure using carried energy.
	 * Requires WORK and CARRY body parts. The target must be within 3 squares.
	 * 
	 * @param target The structure to repair.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): No energy carried
	 *   - ERR_INVALID_TARGET (-7): Invalid structure
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No WORK body parts
	 * 
	 * @see build, dismantle
	 */
	int repair(const Structure& target);

	/**
	 * @brief Reserve a neutral room controller.
	 * 
	 * Temporarily blocks a neutral controller from being claimed by other
	 * players and restores energy sources to full capacity.
	 * Each tick increases the reservation timer by 1 tick per CLAIM body part.
	 * Maximum reservation period is 5000 ticks.
	 * The target must be at an adjacent square.
	 * 
	 * @param target The controller to reserve.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid neutral controller
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No CLAIM body parts
	 *   - ERR_ACCESS_DENIED (-16): No access to restricted shard
	 * 
	 * @see claimController, attackController
	 */
	int reserveController(const StructureController& target);

	/**
	 * @brief Display a speech balloon above the creep.
	 * 
	 * Shows a visual speech balloon with the specified message for one tick.
	 * You can read the last message using the saying() property.
	 * 
	 * @param message The message to display (max 10 characters).
	 * @param visibleToAll If true, other players can see this message.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 * 
	 * @see saying
	 */
	int say(const std::string& message, bool visibleToAll = false);

	/**
	 * @brief Sign a controller with text.
	 * 
	 * Signs a controller with an arbitrary text visible to all players.
	 * The text appears in the room UI, on the world map, and can be accessed
	 * via the API. You can sign unowned and hostile controllers.
	 * The target must be at an adjacent square.
	 * Pass an empty string to remove the sign.
	 * 
	 * @param target The controller to sign.
	 * @param text The sign text (cut off after 100 characters).
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_INVALID_TARGET (-7): Invalid controller
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 * 
	 * @see StructureController::sign
	 */
	int signController(const StructureController& target, const std::string& text);

	/**
	 * @brief Kill the creep immediately.
	 * 
	 * The creep dies immediately without any resource return.
	 * 
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 */
	int suicide();

	/**
	 * @brief Transfer resources to another creep.
	 * 
	 * Transfers resources from this creep to another creep or structure.
	 * The target must be at an adjacent square.
	 * 
	 * @param target The creep or structure to transfer to.
	 * @param resourceType The type of resource to transfer.
	 * @param amount Optional amount to transfer. If omitted, all carried amount is used.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): Not enough of the resource
	 *   - ERR_INVALID_TARGET (-7): Invalid target
	 *   - ERR_FULL (-8): Target is full
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_INVALID_ARGS (-10): Invalid resource type or amount
	 * 
	 * @see withdraw, drop
	 */
	int transfer(const Creep& target,
	             const std::string& resourceType,
	             const std::optional<int>& amount = std::nullopt);

	/**
	 * @brief Transfer resources to a structure.
	 * 
	 * @param target The structure to transfer to.
	 * @param resourceType The type of resource to transfer.
	 * @param amount Optional amount to transfer.
	 * @return int Error code (see transfer(const Creep&, ...)).
	 */
	int transfer(const Structure& target,
	             const std::string& resourceType,
	             const std::optional<int>& amount = std::nullopt);

	/**
	 * @brief Upgrade a room controller.
	 * 
	 * Upgrades the controller using carried energy. Upgrading controllers
	 * raises your Global Control Level.
	 * Requires WORK and CARRY body parts. The target must be within 3 squares.
	 * 
	 * Upgrading a fully upgraded level 8 controller is limited to 15 energy
	 * units per tick regardless of creeps' abilities.
	 * Each upgrade increases the controller's ticksToDowngrade timer by 100.
	 * 
	 * @param target The controller to upgrade.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep or controller
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): No energy carried
	 *   - ERR_INVALID_TARGET (-7): Invalid controller or upgrading blocked
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_NO_BODYPART (-12): No WORK body parts
	 *   - ERR_ACCESS_DENIED (-16): No access to restricted shard
	 * 
	 * @see StructureController, claimController
	 */
	int upgradeController(const StructureController& target);

	/**
	 * @brief Withdraw resources from a structure or tombstone.
	 * 
	 * Withdraws resources from a structure, tombstone, or ruin.
	 * The target must be at an adjacent square.
	 * Multiple creeps can withdraw from the same object in the same tick.
	 * 
	 * @param target The structure, tombstone, or ruin to withdraw from.
	 * @param resourceType The type of resource to withdraw.
	 * @param amount Optional amount to withdraw. If omitted, all available amount is used.
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not your creep or hostile rampart
	 *   - ERR_BUSY (-4): Creep is spawning
	 *   - ERR_NOT_ENOUGH_RESOURCES (-6): Not enough of the resource
	 *   - ERR_INVALID_TARGET (-7): Invalid target
	 *   - ERR_FULL (-8): Creep carry is full
	 *   - ERR_NOT_IN_RANGE (-9): Target too far
	 *   - ERR_INVALID_ARGS (-10): Invalid resource type or amount
	 * 
	 * @see transfer, pickup
	 */
	int withdraw(const RoomObject& target,
	             const std::string& resourceType,
	             const std::optional<int>& amount = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_CREEP_H
