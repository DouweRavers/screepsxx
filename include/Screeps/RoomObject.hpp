/**
 * @file RoomObject.hpp
 * @brief Base class for objects that have a position in a room.
 * 
 * This file defines the RoomObject class which serves as the base class for
 * all Screeps game objects that have a position within a room. This includes
 * creeps, structures, resources, and other entities that exist at specific
 * coordinates in a room.
 */

#ifndef SCREEPS_ROOM_OBJECT_HPP
#define SCREEPS_ROOM_OBJECT_HPP

#include "Object.hpp"

namespace Screeps {

class Effect;
class RoomPosition;
class Room;

/**
 * @class RoomObject
 * @brief Base class for all objects that exist at a position within a room.
 * 
 * RoomObject is the base class for most Screeps game entities that have a
 * physical presence in a room. This includes creeps, structures, resources,
 * construction sites, and other placeable objects.
 * 
 * The class provides access to the object's position (@ref pos()), the room
 * it belongs to (@ref room()), and any effects that may be applied to it
 * (@ref effects()).
 * 
 * @see Object, RoomPosition, Room, Creep, Structure
 */
class RoomObject : public Object
{
public:
	/**
	 * @brief Construct a RoomObject from a JavaScript value.
	 * @param value The JavaScript value representing the room object.
	 */
	explicit RoomObject(JS::Value value);

	/**
	 * @brief Virtual destructor.
	 * 
	 * Ensures proper cleanup of derived classes.
	 */
	virtual ~RoomObject();

	/**
	 * @brief Get the list of effects applied to this object.
	 * 
	 * Effects can be natural game effects or power effects applied by
	 * Power Creeps. Each effect has properties like effect ID, level,
	 * and ticks remaining.
	 * 
	 * @return std::vector<Effect> Array of Effect objects applied to this object.
	 * 
	 * @see Effect, PowerCreep
	 */
	std::vector<Effect> effects() const;

	/**
	 * @brief Get the position of this object in the room.
	 * 
	 * Returns a RoomPosition object representing the (x, y) coordinates
	 * and room name where this object is located.
	 * 
	 * @return RoomPosition The position object.
	 * 
	 * @see RoomPosition
	 */
	RoomPosition pos() const;

	/**
	 * @brief Get the room this object belongs to.
	 * 
	 * Returns the Room object that contains this object. This may be
	 * undefined for flags or construction sites placed in rooms that
	 * are not currently visible to you.
	 * 
	 * @return Room The room object.
	 * 
	 * @see Room
	 */
	Room room() const;
};

/**
 * @brief Factory function to create a RoomObject from a JavaScript value.
 * 
 * This function creates the appropriate derived RoomObject type based on
 * the JavaScript value's type and properties.
 * 
 * @param object The JavaScript value to convert to a RoomObject.
 * @return std::unique_ptr<RoomObject> A unique pointer to the created RoomObject.
 */
std::unique_ptr<RoomObject> createRoomObject(JS::Value object);

/**
 * @brief Template function to check if a RoomObject is of a specific type.
 * 
 * This utility function performs a dynamic cast to check if the given
 * RoomObject pointer points to an object of type T.
 * 
 * @tparam T The type to check for.
 * @param ptr The RoomObject pointer to check.
 * @return bool True if the object is of type T, false otherwise.
 * 
 * @usage
 * @code
 * auto obj = ...; // some RoomObject
 * if (is<Creep>(obj)) {
 *     Creep* creep = static_cast<Creep*>(obj.get());
 *     // work with creep
 * }
 * @endcode
 */
template <typename T>
bool is(const std::unique_ptr<RoomObject>& ptr)
{
	return dynamic_cast<T*>(ptr.get());
}

} // namespace Screeps

#endif // SCREEPS_ROOM_OBJECT_HPP
