/**
 * @file Ruin.hpp
 * @brief Ruin class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Ruin
 */
#ifndef SCREEPS_RUIN_HPP
#define SCREEPS_RUIN_HPP

#include "RoomObject.hpp"

namespace Screeps {

/**
 * @class Ruin
 * @brief A ruined structure that remains after destruction.
 *
 * Ruins are the remains of destroyed structures. They decay over time and
 * may contain information about the original structure.
 *
 * @see https://docs.screeps.com/api/#Ruin
 * @see RoomObject
 */
class Ruin : public RoomObject
{
public:
	/**
	 * @brief Construct a Ruin from a JavaScript value.
	 * @param value The JavaScript value representing the ruin.
	 */
	explicit Ruin(JS::Value value);
};

} // namespace Screeps

#endif // SCREEPS_RUIN_HPP
