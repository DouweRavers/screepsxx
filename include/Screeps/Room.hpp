/**
 * @file Room.hpp
 * @brief Represents a room in the Screeps game world.
 * 
 * This file defines the Room class which represents a specific room in the Screeps
 * game world. Rooms contain terrain, structures, creeps, resources, and other game
 * objects. The Room class provides methods for finding objects, pathfinding, and
 * examining the room's contents.
 */

#ifndef SCREEPS_ROOM_HPP
#define SCREEPS_ROOM_HPP

#include "../nlohmann/json.hpp"
#include "Constants.hpp"
#include "Object.hpp"

namespace Screeps {
class RoomObject;
class RoomPosition;
class StructureController;
class StructureStorage;
class StructureTerminal;
class RoomVisual;
class RoomTerrain;

/**
 * @class Room
 * @brief Represents a room in the Screeps game world.
 * 
 * A Room represents a 50x50 grid area in the Screeps game world with a unique
 * name (e.g., "W1N1", "E2S3"). Each room contains terrain (plain, swamp, wall),
 * and can contain structures, creeps, resources, and other game objects.
 * 
 * The Room class provides methods for:
 * - Accessing room properties (@ref controller, @ref terminal, @ref storage, @ref visual)
 * - Finding objects in the room (@ref find)
 * - Pathfinding within the room (@ref findPath)
 * - Looking at specific positions (@ref lookAt, @ref lookForAt)
 * - Creating construction sites and flags (@ref createConstructionSite, @ref createFlag)
 * - Accessing room metadata and memory (@ref name, @ref memory)
 * 
 * All rooms are accessible through the global @ref Game.rooms map.
 * 
 * @see Game, RoomObject, RoomPosition
 */
class Room : public Object
{
public:
	/**
	 * @struct PathStep
	 * @brief Represents a single step in a path.
	 * 
	 * A PathStep contains the coordinates and direction information for one
	 * step in a path found by the pathfinding algorithms.
	 */
    struct PathStep
    {
		/** @brief The X coordinate of this step. */
        int x;
		/** @brief The Y coordinate of this step. */
        int y;
		/** @brief The X direction component (-1, 0, or 1). */
        int dx;
		/** @brief The Y direction component (-1, 0, or 1). */
        int dy;
		/** @brief The direction constant for this step. */
        int direction;
    };

    /**
	 * @brief Construct a Room from a JavaScript value.
	 * @param value The JavaScript Room value.
	 */
    explicit Room(JS::Value value);

    // Properties
    /**
	 * @brief Get the controller structure of this room.
	 * 
	 * Returns the StructureController for this room if one exists,
	 * or std::nullopt if the room has no controller.
	 * 
	 * @return std::optional<StructureController> The room controller, or nullopt.
	 * 
	 * @see StructureController
	 */
    std::optional<StructureController> controller() const;

	/**
	 * @brief Get the terminal structure of this room.
	 * 
	 * Returns the StructureTerminal for this room if one exists,
	 * or std::nullopt if the room has no terminal.
	 * 
	 * @return std::optional<StructureTerminal> The room terminal, or nullopt.
	 * 
	 * @see StructureTerminal
	 */
    std::optional<StructureTerminal> terminal() const;

	/**
	 * @brief Get the visual object for this room.
	 * 
	 * Returns the RoomVisual object that can be used to draw debug
	 * information in the room.
	 * 
	 * @return std::optional<RoomVisual> The room visual object, or nullopt.
	 * 
	 * @see RoomVisual
	 */
    std::optional<RoomVisual> visual() const;

	/**
	 * @brief Get the storage structure of this room.
	 * 
	 * Returns the StructureStorage for this room if one exists,
	 * or std::nullopt if the room has no storage.
	 * 
	 * @return std::optional<StructureStorage> The room storage, or nullopt.
	 * 
	 * @see StructureStorage
	 */
    std::optional<StructureStorage> storage() const;

    // Energy
    /**
	 * @brief Get the total amount of energy available in all spawns and extensions.
	 * 
	 * @return int The total energy available.
	 */
    int energyAvailable() const;

	/**
	 * @brief Get the total energy capacity of all spawns and extensions.
	 * 
	 * @return int The total energy capacity available.
	 */
    int energyCapacityAvailable() const;

    // Memory
    /**
	 * @brief Get the room-specific memory object.
	 * 
	 * This is a shorthand for accessing Memory.rooms[room.name].
	 * Use this to store and retrieve room-specific data that persists
	 * between game ticks.
	 * 
	 * @return JSON The room memory object.
	 * 
	 * @see setMemory
	 */
    JSON memory() const;

	/**
	 * @brief Set the room-specific memory object.
	 * 
	 * @param memory The new memory content as a JSON object.
	 * 
	 * @see memory
	 */
    void setMemory(const JSON& memory);

    // Metadata
    /**
	 * @brief Get the room name.
	 * 
	 * @return std::string The room name (e.g., "W1N1", "E2S3").
	 */
    std::string name() const;

    // Pathfinding
    /**
	 * @brief Find an optimal path between two positions within this room.
	 * 
	 * Uses the Jump Point Search algorithm to find a path from fromPos to toPos
	 * within this room, considering terrain and obstacles.
	 * 
	 * @param fromPos The starting position.
	 * @param toPos The target position.
	 * @param options Optional JSON object with pathfinding options:
	 *   - ignoreCreeps: Treat creeps as walkable (default: false)
	 *   - ignoreDestructibleStructures: Treat destructible structures as walkable (default: false)
	 *   - ignoreRoads: Ignore road structures (default: false)
	 *   - costCallback: Custom callback to modify cost matrix
	 *   - maxOps: Maximum pathfinding operations (default: 2000)
	 *   - maxCost: Maximum allowed path cost (default: Infinity)
	 *   - heuristicWeight: Weight for A* heuristic (default: 1.2)
	 * @return std::vector<PathStep> Array of path steps from start to target.
	 * 
	 * @see RoomPosition::findPathTo, serializePath, deserializePath
	 */
    std::vector<PathStep> findPath(const RoomPosition& fromPos, const RoomPosition& toPos, const JSON& options = {});

	/**
	 * @brief Serialize a path to a compact string representation.
	 * 
	 * This is useful for storing paths in memory between game ticks.
	 * 
	 * @param path The path to serialize.
	 * @return std::string The serialized path string.
	 * 
	 * @see deserializePath
	 */
    std::string serializePath(const std::vector<PathStep>& path) const;

	/**
	 * @brief Deserialize a path from a compact string representation.
	 * 
	 * @param path The serialized path string.
	 * @return std::vector<PathStep> The deserialized path.
	 * 
	 * @see serializePath
	 */
    std::vector<PathStep> deserializePath(const std::string& path) const;

    // Position
    /**
	 * @brief Create a RoomPosition at the specified coordinates.
	 * 
	 * @param x The X coordinate (0-49).
	 * @param y The Y coordinate (0-49).
	 * @return std::optional<RoomPosition> The RoomPosition, or nullopt if invalid.
	 * 
	 * @see RoomPosition
	 */
    std::optional<RoomPosition> getPositionAt(int x, int y) const;

	/**
	 * @brief Get the terrain data for this room.
	 * 
	 * Returns a RoomTerrain object that provides fast access to terrain
	 * information for this room. This works even for rooms that are not
	 * currently visible.
	 * 
	 * @return RoomTerrain The terrain object for this room.
	 * 
	 * @see RoomTerrain
	 */
    RoomTerrain getTerrain() const;

    // Look
    /**
	 * @brief Get all objects at the specified coordinates.
	 * 
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of objects at the position.
	 * 
	 * @see lookForAt
	 */
    std::vector<std::unique_ptr<RoomObject>> lookAt(int x, int y) const;

	/**
	 * @brief Get all objects at the specified RoomPosition.
	 * 
	 * @param target The position to look at.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of objects at the position.
	 */
    std::vector<std::unique_ptr<RoomObject>> lookAt(const RoomPosition& target) const;

	/**
	 * @brief Get all objects in a rectangular area.
	 * 
	 * @param top The top Y boundary (inclusive).
	 * @param left The left X boundary (inclusive).
	 * @param bottom The bottom Y boundary (inclusive).
	 * @param right The right X boundary (inclusive).
	 * @param asArray If true, return results as a flat array instead of nested objects.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of objects in the area.
	 * 
	 * @see lookForAtArea
	 */
    std::vector<std::unique_ptr<RoomObject>> lookAtArea(int top, int left, int bottom, int right, const std::optional<bool>& asArray = std::nullopt) const;

	/**
	 * @brief Get objects of a specific type at the specified coordinates.
	 * 
	 * @param type The type of objects to look for. Use LOOK_* constants:
	 *   - LOOK_CREEPS, LOOK_ENERGY, LOOK_RESOURCES, LOOK_SOURCES
	 *   - LOOK_MINERALS, LOOK_DEPOSITS, LOOK_STRUCTURES, LOOK_FLAGS
	 *   - LOOK_CONSTRUCTION_SITES, LOOK_NUKES, LOOK_TERRAIN
	 *   - LOOK_TOMBSTONES, LOOK_POWER_CREEPS, LOOK_RUINS
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of objects of the specified type.
	 * 
	 * @see lookAt
	 */
    std::vector<std::unique_ptr<RoomObject>> lookForAt(const std::string& type, int x, int y) const;

	/**
	 * @brief Get objects of a specific type at the specified RoomPosition.
	 * 
	 * @param type The type of objects to look for (LOOK_* constants).
	 * @param target The position to look at.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of objects of the specified type.
	 */
    std::vector<std::unique_ptr<RoomObject>> lookForAt(const std::string& type, const RoomPosition& target) const;

	/**
	 * @brief Get objects of a specific type in a rectangular area.
	 * 
	 * @param type The type of objects to look for (LOOK_* constants).
	 * @param top The top Y boundary (inclusive).
	 * @param left The left X boundary (inclusive).
	 * @param bottom The bottom Y boundary (inclusive).
	 * @param right The right X boundary (inclusive).
	 * @param asArray If true, return results as a flat array.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of objects of the specified type in the area.
	 */
    std::vector<std::unique_ptr<RoomObject>> lookForAtArea(const std::string& type, int top, int left, int bottom, int right, const std::optional<bool>& asArray = std::nullopt) const;

    // Construction
    /**
	 * @brief Create a construction site at the specified coordinates.
	 * 
	 * Creates a new construction site for building a structure at the given
	 * position in this room.
	 * 
	 * @param x The X coordinate (0-49).
	 * @param y The Y coordinate (0-49).
	 * @param structureType The type of structure to build. Use STRUCTURE_* constants.
	 * @param name Optional name for the structure (only used for spawns).
	 * @return int Error code:
	 *   - OK (0): Success
	 *   - ERR_NOT_OWNER (-1): Not the room owner
	 *   - ERR_INVALID_TARGET (-7): Invalid placement location
	 *   - ERR_FULL (-8): Too many construction sites
	 *   - ERR_INVALID_ARGS (-10): Invalid arguments
	 *   - ERR_RCL_NOT_ENOUGH (-14): Room Controller Level insufficient
	 * 
	 * @see createConstructionSite(const RoomPosition&, ...)
	 */
    int createConstructionSite(int x, int y, const std::string& structureType, const std::optional<std::string>& name = std::nullopt);

	/**
	 * @brief Create a construction site at the specified RoomPosition.
	 * 
	 * @param pos The position to create the construction site at.
	 * @param structureType The type of structure to build.
	 * @param name Optional name for the structure.
	 * @return int Error code (see createConstructionSite(int, int, ...)).
	 */
    int createConstructionSite(const RoomPosition& pos, const std::string& structureType, const std::optional<std::string>& name = std::nullopt);

    // Flags
    /**
	 * @brief Create a flag at the specified coordinates.
	 * 
	 * Creates a new flag at the given position in this room.
	 * 
	 * @param x The X coordinate (0-49).
	 * @param y The Y coordinate (0-49).
	 * @param name Optional name for the flag.
	 * @param color Optional primary color (COLOR_* constants).
	 * @param secondaryColor Optional secondary color (COLOR_* constants).
	 * @return int Error code:
	 *   - Flag name on success
	 *   - ERR_NAME_EXISTS (-3): Flag with this name already exists
	 *   - ERR_FULL (-8): Too many flags
	 *   - ERR_INVALID_ARGS (-10): Invalid arguments
	 * 
	 * @see createFlag(const RoomPosition&, ...), Flag
	 */
    int createFlag(int x, int y, const std::optional<std::string>& name = std::nullopt, const std::optional<std::string>& color = std::nullopt, const std::optional<std::string>& secondaryColor = std::nullopt);

	/**
	 * @brief Create a flag at the specified RoomPosition.
	 * 
	 * @param pos The position to create the flag at.
	 * @param name Optional name for the flag.
	 * @param color Optional primary color.
	 * @param secondaryColor Optional secondary color.
	 * @return int Error code (see createFlag(int, int, ...)).
	 */
    int createFlag(const RoomPosition& pos, const std::optional<std::string>& name = std::nullopt, const std::optional<std::string>& color = std::nullopt, const std::optional<std::string>& secondaryColor = std::nullopt);

    // Find
    /**
	 * @brief Find objects of a specific type in this room.
	 * 
	 * Finds all objects matching the specified type and optional predicate.
	 * Results are cached automatically for the same room and type.
	 * 
	 * @param type The type of objects to find. Use FIND_* constants:
	 *   - FIND_EXIT_TOP, FIND_EXIT_RIGHT, FIND_EXIT_BOTTOM, FIND_EXIT_LEFT, FIND_EXIT
	 *   - FIND_CREEPS, FIND_MY_CREEPS, FIND_HOSTILE_CREEPS
	 *   - FIND_POWER_CREEPS, FIND_MY_POWER_CREEPS, FIND_HOSTILE_POWER_CREEPS
	 *   - FIND_SOURCES_ACTIVE, FIND_SOURCES
	 *   - FIND_DROPPED_RESOURCES
	 *   - FIND_STRUCTURES, FIND_MY_STRUCTURES, FIND_HOSTILE_STRUCTURES
	 *   - FIND_FLAGS
	 *   - FIND_CONSTRUCTION_SITES, FIND_MY_CONSTRUCTION_SITES, FIND_HOSTILE_CONSTRUCTION_SITES
	 *   - FIND_MINERALS
	 *   - FIND_NUKES
	 *   - FIND_TOMBSTONES
	 *   - FIND_RUINS
	 *   - FIND_DEPOSITS
	 * @param predicate Optional predicate function to filter results.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of matching objects.
	 * 
	 * @see find<T>
	 */
    std::vector<std::unique_ptr<RoomObject>> find(int type, std::function<bool(const JS::Value&)> predicate = {}) const;

	/**
	 * @brief Find objects of a specific type with a typed predicate.
	 * 
	 * Template version of find() that allows using a typed predicate function.
	 * 
	 * @tparam T The type of objects to find (must have findConstant defined).
	 * @param predicate Optional predicate function to filter results.
	 * @return std::vector<std::unique_ptr<RoomObject>> Array of matching objects.
	 * 
	 * @usage
	 * @code
	 * // Find all my creeps with hits less than max
	 * auto creeps = room.find<Creep>([](const Creep& c) {
	 *     return c.hits() < c.hitsMax();
	 * });
	 * @endcode
	 */
    template <class T>
    std::vector<std::unique_ptr<RoomObject>> find(std::function<bool(const T&)> predicate = {}) const
    {
        if (predicate)
        {
            auto p = [&](const JS::Value& value) { return predicate(T(value)); };
            return find(T::findConstant, p);
        }
        return find(T::findConstant);
    }

    // Exits
    /**
	 * @brief Find the exit direction to another room.
	 * 
	 * Returns the direction constant for the exit that leads from this room
	 * to the specified target room.
	 * 
	 * @param room The target room name or Room object.
	 * @return int The direction constant (FIND_EXIT_TOP, FIND_EXIT_RIGHT, etc.)
	 *   or an error code:
	 *   - ERR_NO_PATH (-2): No path found
	 *   - ERR_INVALID_ARGS (-10): Invalid arguments
	 * 
	 * @see RoomPosition::findClosestByPath
	 */
    int findExitTo(const std::string& room);

	/**
	 * @brief Find the exit direction to another room (Room version).
	 * 
	 * @param room The target Room object.
	 * @return int The direction constant or error code.
	 */
    int findExitTo(const Room& room);

    // Events
    /**
	 * @brief Get the event log for this room.
	 * 
	 * Returns an array of events that occurred in this room on the previous
	 * game tick. Events include attacks, builds, harvests, heals, repairs,
	 * and other game actions.
	 * 
	 * @param raw If true, return raw JSON string instead of parsed objects.
	 * @return std::vector<JSON> Array of event objects, each containing:
	 *   - event: The event type constant
	 *   - objectId: The ID of the object involved
	 *   - data: Event-specific data
	 * 
	 * @see https://docs.screeps.com/api/#Room.getEventLog for event types and data
	 */
    std::vector<JSON> getEventLog(bool raw = false) const;

private:
    std::vector<std::unique_ptr<RoomObject>> createRoomObjects(const std::vector<JS::Value>& objects) const;
    std::vector<std::unique_ptr<RoomObject>> flattenAndCreateRoomObjects(JS::Value result) const;
};

} // namespace Screeps

#endif // SCREEPS_ROOM_HPP