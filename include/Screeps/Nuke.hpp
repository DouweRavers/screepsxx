/**
 * @file Nuke.hpp
 * @brief Nuke class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Nuke
 */
#ifndef SCREEPS_NUKE_HPP
#define SCREEPS_NUKE_HPP

#include "RoomObject.hpp"

#include <string>

namespace Screeps {

/**
 * @class Nuke
 * @brief A nuclear missile that has been launched.
 *
 * Nukes are destructive weapons that can be launched from StructureNuker.
 * They travel for a number of ticks before landing and exploding, dealing
 * massive damage to all objects in the target room.
 *
 * @see https://docs.screeps.com/api/#Nuke
 * @see RoomObject
 */
class Nuke : public RoomObject
{
public:
	/**
	 * @brief Construct a Nuke from a JavaScript value.
	 * @param value The JavaScript value representing the nuke.
	 */
	explicit Nuke(JS::Value value);

	/**
	 * @brief Get the name of the room that launched this nuke.
	 * @return The name of the launch room.
	 * @see https://docs.screeps.com/api/#Nuke.launchRoomName
	 */
	std::string launchRoomName() const;

	/**
	 * @brief Get the time until this nuke lands.
	 * @return The number of ticks until landing.
	 * @see https://docs.screeps.com/api/#Nuke.timeToLand
	 */
	int timeToLand() const;
};

} // namespace Screeps

#endif // SCREEPS_NUKE_HPP