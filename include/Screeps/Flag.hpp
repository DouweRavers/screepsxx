/**
 * @file Flag.hpp
 * @brief Flag class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Flag
 */
#ifndef SCREEPS_FLAG_HPP
#define SCREEPS_FLAG_HPP

#include "RoomObject.hpp"

namespace Screeps {

/**
 * @class Flag
 * @brief A marker that can be used to mark positions in a room.
 *
 * Flags are visible markers that can be placed in rooms. They can be used to
 * communicate between players, mark positions for creeps to move to, or store
 * custom data in their memory. Each flag has a color, secondary color, and name.
 *
 * @see https://docs.screeps.com/api/#Flag
 * @see RoomObject
 */
class Flag : public RoomObject
{
public:
	/**
	 * @brief Construct a Flag from a JavaScript value.
	 * @param value The JavaScript value representing the flag.
	 */
	explicit Flag(JS::Value value);

	/**
	 * @brief Get the primary color of this flag.
	 * @return The primary color constant.
	 * @see https://docs.screeps.com/api/#Flag.color
	 * @see COLOR_RED, COLOR_PURPLE, COLOR_BLUE, etc. in Constants.hpp
	 */
	int color() const;

	/**
	 * @brief Get the memory of this flag.
	 * @return The JSON object containing custom memory data.
	 * @see https://docs.screeps.com/api/#Flag.memory
	 */
	JSON memory() const;

	/**
	 * @brief Set the memory of this flag.
	 * @param memory The JSON object to store in flag memory.
	 * @see https://docs.screeps.com/api/#Flag.memory
	 */
	void setMemory(const JSON&);

	/**
	 * @brief Get the name of this flag.
	 * @return The name string of the flag.
	 * @see https://docs.screeps.com/api/#Flag.name
	 */
	std::string name() const;

	/**
	 * @brief Get the secondary color of this flag.
	 * @return The secondary color constant.
	 * @see https://docs.screeps.com/api/#Flag.secondaryColor
	 * @see COLOR_RED, COLOR_PURPLE, COLOR_BLUE, etc. in Constants.hpp
	 */
	int secondaryColor() const;

	/**
	 * @brief Remove this flag.
	 * @see https://docs.screeps.com/api/#Flag.remove
	 */
	void remove();

	/**
	 * @brief Set the color and secondary color of this flag.
	 * @param color The primary color constant.
	 * @param secondaryColor The secondary color constant (optional).
	 * @return Result code (OK, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#Flag.setColor
	 */
	int setColor(int color, const std::optional<int>& secondaryColor);

	/**
	 * @brief Set the position of this flag using x, y coordinates.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 * @return Result code (OK, ERR_INVALID_TARGET, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#Flag.setPosition
	 */
	int setPosition(int x, int y);

	/**
	 * @brief Set the position of this flag using a RoomPosition.
	 * @param pos The RoomPosition to set.
	 * @return Result code (OK, ERR_INVALID_TARGET, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#Flag.setPosition
	 */
	int setPosition(const RoomPosition& pos);

	/**
	 * @brief Set the position of this flag using a RoomObject.
	 * @param pos The RoomObject to set position to.
	 * @return Result code (OK, ERR_INVALID_TARGET, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#Flag.setPosition
	 */
	int setPosition(const RoomObject& pos);
};

} // namespace Screeps

#endif // SCREEPS_FLAG_HPP
