/**
 * @file StructureObserver.hpp
 * @brief StructureObserver class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureObserver
 */
#ifndef SCREEPS_STRUCTURE_OBSERVER_HPP
#define SCREEPS_STRUCTURE_OBSERVER_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

/**
 * @class StructureObserver
 * @brief A structure that can observe distant rooms.
 *
 * Observers are structures that allow you to see the contents of rooms that
 * are not visible from your current room. They have a limited range and
 * consume energy when used.
 *
 * @see https://docs.screeps.com/api/#StructureObserver
 * @see OwnedStructure
 */
class StructureObserver : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureObserver from a JavaScript value.
	 * @param value The JavaScript value representing the observer.
	 */
	explicit StructureObserver(JS::Value value);

	/**
	 * @brief Observe a distant room.
	 * @param roomName The name of the room to observe.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_NOT_ENOUGH_ENERGY).
	 * @see https://docs.screeps.com/api/#StructureObserver.observeRoom
	 */
	int observeRoom(const std::string& roomName);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_OBSERVER_HPP