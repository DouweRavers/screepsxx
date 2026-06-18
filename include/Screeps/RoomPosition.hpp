/**
 * @file RoomPosition.hpp
 * @brief Represents a position within a room in the Screeps world.
 * 
 * This file defines the RoomPosition class which represents a specific location
 * in a Screeps room with (x, y) coordinates and a room name. It provides
 * methods for pathfinding, finding objects, and various position utilities.
 */

#ifndef SCREEPS_ROOM_POSITION_HPP
#define SCREEPS_ROOM_POSITION_HPP

#include "Object.hpp"
#include "JSON.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace Screeps {

class RoomObject;

/**
 * @class RoomPosition
 * @brief Represents a position within a Screeps room.
 * 
 * A RoomPosition represents a specific location in the Screeps game world
 * with (x, y) coordinates ranging from 0 to 49, and a room name (e.g., "W1N1").
 * 
 * This class provides methods for:
 * - Finding objects relative to this position (@ref findClosestByPath, @ref findClosestByRange, @ref findInRange)
 * - Pathfinding to other positions (@ref findPathTo)
 * - Position utilities (@ref getDirectionTo, @ref getRangeTo, @ref inRangeTo, etc.)
 * - Looking at the position (@ref look, @ref lookFor)
 * - Creating objects at this position (@ref createConstructionSite, @ref createFlag)
 * 
 * Every RoomObject in a room contains a RoomPosition as its pos() property.
 * 
 * @see RoomObject, Room
 */
class RoomPosition : public Object
{
public:
	/**
	 * @brief Construct a RoomPosition from a JavaScript value.
	 * @param value The JavaScript RoomPosition value.
	 */
	explicit RoomPosition(JS::Value value);

	/**
	 * @brief Construct a RoomPosition with specific coordinates.
	 * 
	 * @param roomName The name of the room (e.g., "W1N1", "E2S3").
	 * @param x The X coordinate in the room (0-49).
	 * @param y The Y coordinate in the room (0-49).
	 */
	RoomPosition(const std::string& roomName, int x, int y);

	/**
	 * @brief Get the room name.
	 * @return std::string The room name.
	 */
	std::string roomName() const;

	/**
	 * @brief Set the room name.
	 * @param name The new room name.
	 */
	void setRoomName(const std::string& name);

	/**
	 * @brief Get the X coordinate.
	 * @return int The X coordinate (0-49).
	 */
	int x() const;

	/**
	 * @brief Set the X coordinate.
	 * @param x The new X coordinate.
	 */
	void setX(int x);

	/**
	 * @brief Get the Y coordinate.
	 * @return int The Y coordinate (0-49).
	 */
	int y() const;

	/**
	 * @brief Set the Y coordinate.
	 * @param y The new Y coordinate.
	 */
	void setY(int y);

	// Find methods
	/**
	 * @brief Find the closest object by path distance.
	 * 
	 * Uses pathfinding to find the object with the shortest path from this position.
	 * This considers actual walkable paths, not just straight-line distance.
	 * 
	 * @param objects Vector of RoomObject pointers to search through.
	 * @return std::unique_ptr<RoomObject> The closest RoomObject, or nullptr if none found.
	 * 
	 * @see findClosestByRange, findInRange
	 */
	std::unique_ptr<RoomObject>
	findClosestByPath(const std::vector<std::unique_ptr<RoomObject>>& objects);

	/**
	 * @brief Find the closest object by path distance (JS::Value version).
	 * 
	 * @param objects Vector of JavaScript values to search through.
	 * @return std::optional<JS::Value> The closest object as JS::Value, or nullopt if none found.
	 */
	std::optional<JS::Value> findClosestByPath(const std::vector<JS::Value>& objects);
	
	/**
	 * @brief Find the closest object by straight-line (Euclidean) distance.
	 * 
	 * This is faster than findClosestByPath as it doesn't perform pathfinding,
	 * but only considers direct distance, not actual walkable paths.
	 * 
	 * @param objects Vector of RoomObject pointers to search through.
	 * @param options Optional JSON object with filtering options.
	 * @return std::unique_ptr<RoomObject> The closest RoomObject, or nullptr if none found.
	 * 
	 * @see findClosestByPath, findInRange
	 */
	std::unique_ptr<RoomObject>
	findClosestByRange(const std::vector<std::unique_ptr<RoomObject>>& objects, const JSON& options = {});

	/**
	 * @brief Find the closest object by straight-line distance (JS::Value version).
	 * 
	 * @param objects Vector of JavaScript values to search through.
	 * @param options Optional JSON object with filtering options.
	 * @return std::optional<JS::Value> The closest object as JS::Value, or nullopt if none found.
	 */
	std::optional<JS::Value> findClosestByRange(const std::vector<JS::Value>& objects, const JSON& options = {});
	
	/**
	 * @brief Find all objects within a specified range.
	 * 
	 * Returns all objects from the given list that are within the specified
	 * straight-line distance from this position.
	 * 
	 * @param objects Vector of RoomObject pointers to search through.
	 * @param range The maximum distance (in squares) to search.
	 * @param options Optional JSON object with filtering options.
	 * @return std::vector<std::unique_ptr<RoomObject>> Vector of RoomObjects within range.
	 * 
	 * @see findClosestByPath, findClosestByRange
	 */
	std::vector<std::unique_ptr<RoomObject>>
	findInRange(const std::vector<std::unique_ptr<RoomObject>>& objects, int range, const JSON& options = {});

	/**
	 * @brief Find all objects within a specified range (JS::Value version).
	 * 
	 * @param objects Vector of JavaScript values to search through.
	 * @param range The maximum distance (in squares) to search.
	 * @param options Optional JSON object with filtering options.
	 * @return std::vector<JS::Value> Vector of objects within range as JS::Value.
	 */
	std::vector<JS::Value>
	findInRange(const std::vector<JS::Value>& objects, int range, const JSON& options = {});

	// Path finding
	/**
	 * @brief Find a path to the specified coordinates.
	 * 
	 * Uses the Screeps pathfinding algorithm to find an optimal path from
	 * this position to the target coordinates. Returns an array of path steps.
	 * 
	 * @param x The target X coordinate.
	 * @param y The target Y coordinate.
	 * @param options Optional JSON object with pathfinding options:
	 *   - ignoreCreeps: Treat creeps as walkable (default: false)
	 *   - ignoreDestructibleStructures: Treat destructible structures as walkable (default: false)
	 *   - ignoreRoads: Ignore road structures (default: false)
	 *   - maxOps: Maximum pathfinding operations (default: 2000)
	 *   - maxCost: Maximum allowed path cost (default: Infinity)
	 *   - heuristicWeight: Weight for A* heuristic (default: 1.2)
	 * @return std::vector<JSON> Array of path steps, each containing direction, x, y, dx, dy.
	 * 
	 * @see findPathTo(const RoomPosition&), Room::findPath
	 */
	std::vector<JSON> findPathTo(int x, int y, const JSON& options = {});

	/**
	 * @brief Find a path to the specified RoomPosition.
	 * 
	 * @param target The target position.
	 * @param options Optional JSON object with pathfinding options.
	 * @return std::vector<JSON> Array of path steps.
	 * 
	 * @see findPathTo(int, int), Room::findPath
	 */
	std::vector<JSON> findPathTo(const RoomPosition& target, const JSON& options = {});

	// Position utilities
	/**
	 * @brief Get the direction to the specified coordinates.
	 * 
	 * Returns one of the direction constants (TOP, RIGHT, BOTTOM, LEFT, etc.)
	 * representing the direction from this position to the target.
	 * 
	 * @param x The target X coordinate.
	 * @param y The target Y coordinate.
	 * @return int One of the direction constants.
	 * 
	 * @see getRangeTo, inRangeTo
	 */
	int getDirectionTo(int x, int y) const;

	/**
	 * @brief Get the direction to the specified RoomPosition.
	 * 
	 * @param target The target position.
	 * @return int One of the direction constants.
	 */
	int getDirectionTo(const RoomPosition& target) const;
	
	/**
	 * @brief Get the linear distance to the specified coordinates.
	 * 
	 * Calculates the straight-line (Manhattan) distance between this position
	 * and the target coordinates.
	 * 
	 * @param x The target X coordinate.
	 * @param y The target Y coordinate.
	 * @return int The distance in squares.
	 * 
	 * @see getDirectionTo, inRangeTo
	 */
	int getRangeTo(int x, int y) const;

	/**
	 * @brief Get the linear distance to the specified RoomPosition.
	 * 
	 * @param target The target position.
	 * @return int The distance in squares.
	 */
	int getRangeTo(const RoomPosition& target) const;
	
	/**
	 * @brief Check if this position is within a specified range of coordinates.
	 * 
	 * @param x The target X coordinate.
	 * @param y The target Y coordinate.
	 * @param range The maximum distance to check.
	 * @return bool True if the target is within range, false otherwise.
	 * 
	 * @see getRangeTo, isNearTo
	 */
	bool inRangeTo(int x, int y, int range) const;

	/**
	 * @brief Check if this position is within a specified range of another position.
	 * 
	 * @param target The target position.
	 * @param range The maximum distance to check.
	 * @return bool True if the target is within range, false otherwise.
	 */
	bool inRangeTo(const RoomPosition& target, int range) const;
	
	/**
	 * @brief Check if this position is at the specified coordinates.
	 * 
	 * @param x The X coordinate to compare.
	 * @param y The Y coordinate to compare.
	 * @return bool True if the position matches, false otherwise.
	 * 
	 * @see isNearTo
	 */
	bool isEqualTo(int x, int y) const;

	/**
	 * @brief Check if this position is at the same location as another position.
	 * 
	 * @param target The position to compare.
	 * @return bool True if the positions match, false otherwise.
	 */
	bool isEqualTo(const RoomPosition& target) const;
	
	/**
	 * @brief Check if this position is adjacent to the specified coordinates.
	 * 
	 * A position is "near" if it's directly orthogonally or diagonally adjacent
	 * (maximum distance of 1 in both x and y directions).
	 * 
	 * @param x The X coordinate to check.
	 * @param y The Y coordinate to check.
	 * @return bool True if the position is adjacent, false otherwise.
	 * 
	 * @see isEqualTo, inRangeTo
	 */
	bool isNearTo(int x, int y) const;

	/**
	 * @brief Check if this position is adjacent to another position.
	 * 
	 * @param target The position to check.
	 * @return bool True if the position is adjacent, false otherwise.
	 */
	bool isNearTo(const RoomPosition& target) const;

	// Look methods
	/**
	 * @brief Get all objects at this position.
	 * 
	 * Returns an array of all objects (creeps, structures, resources, terrain, etc.)
	 * that are present at this position in the room.
	 * 
	 * @return std::vector<JS::Value> Array of objects at this position.
	 * 
	 * @see lookFor
	 */
	std::vector<JS::Value> look() const;

	/**
	 * @brief Get objects of a specific type at this position.
	 * 
	 * Returns an array of objects of the specified type that are present at
	 * this position.
	 * 
	 * @param type The type of objects to look for. Use LOOK_* constants:
	 *   - LOOK_CREEPS: Creeps
	 *   - LOOK_ENERGY: Energy resources
	 *   - LOOK_RESOURCES: All resources
	 *   - LOOK_SOURCES: Sources
	 *   - LOOK_MINERALS: Minerals
	 *   - LOOK_DEPOSITS: Deposits
	 *   - LOOK_STRUCTURES: Structures
	 *   - LOOK_FLAGS: Flags
	 *   - LOOK_CONSTRUCTION_SITES: Construction sites
	 *   - LOOK_NUKES: Nukes
	 *   - LOOK_TERRAIN: Terrain
	 *   - LOOK_TOMBSTONES: Tombstones
	 *   - LOOK_POWER_CREEPS: Power creeps
	 *   - LOOK_RUINS: Ruins
	 * @return std::vector<JS::Value> Array of objects of the specified type.
	 * 
	 * @see look
	 */
	std::vector<JS::Value> lookFor(const std::string& type) const;

	// Creation methods
	/**
	 * @brief Create a construction site at this position.
	 * 
	 * Creates a new construction site for the specified structure type at this position.
	 * 
	 * @param structureType The type of structure to build. Use STRUCTURE_* constants:
	 *   - STRUCTURE_SPAWN: Spawn
	 *   - STRUCTURE_EXTENSION: Extension
	 *   - STRUCTURE_ROAD: Road
	 *   - STRUCTURE_WALL: Wall
	 *   - STRUCTURE_RAMPART: Rampart
	 *   - STRUCTURE_KEEPER_LAIR: Keeper lair
	 *   - STRUCTURE_PORTAL: Portal
	 *   - STRUCTURE_CONTROLLER: Controller
	 *   - STRUCTURE_LINK: Link
	 *   - STRUCTURE_STORAGE: Storage
	 *   - STRUCTURE_TOWER: Tower
	 *   - STRUCTURE_OBSERVER: Observer
	 *   - STRUCTURE_POWER_BANK: Power bank
	 *   - STRUCTURE_POWER_SPAWN: Power spawn
	 *   - STRUCTURE_EXTRACTOR: Extractor
	 *   - STRUCTURE_LAB: Lab
	 *   - STRUCTURE_TERMINAL: Terminal
	 *   - STRUCTURE_CONTAINER: Container
	 *   - STRUCTURE_NUKER: Nuker
	 *   - STRUCTURE_FACTORY: Factory
	 *   - STRUCTURE_INVADER_CORE: Invader core
	 * @param name Optional name for the structure (only used for spawns).
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_INVALID_TARGET (-7): The structure cannot be placed at this location
	 *   - ERR_FULL (-8): Too many construction sites
	 *   - ERR_INVALID_ARGS (-10): Invalid arguments
	 *   - ERR_RCL_NOT_ENOUGH (-14): Room Controller Level insufficient
	 * 
	 * @see Room::createConstructionSite
	 */
	int createConstructionSite(const std::string& structureType, const std::optional<std::string>& name = std::nullopt);

	/**
	 * @brief Create a flag at this position.
	 * 
	 * Creates a new flag at this position with optional name and colors.
	 * 
	 * @param name Optional name for the flag. If not provided, a random name is generated.
	 * @param color Optional primary color. Use COLOR_* constants:
	 *   - COLOR_RED, COLOR_PURPLE, COLOR_BLUE, COLOR_CYAN
	 *   - COLOR_GREEN, COLOR_YELLOW, COLOR_ORANGE, COLOR_BROWN
	 *   - COLOR_GREY, COLOR_WHITE
	 * @param secondaryColor Optional secondary color (same constants as color).
	 * @return std::string The name of the created flag, or empty string on error.
	 * 
	 * @see Room::createFlag, Flag
	 */
	std::string createFlag(const std::optional<std::string>& name = std::nullopt, 
	                     const std::optional<int>& color = std::nullopt, 
	                     const std::optional<int>& secondaryColor = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_ROOM_POSITION_HPP
