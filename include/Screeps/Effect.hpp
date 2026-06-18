/**
 * @file Effect.hpp
 * @brief Effect struct definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Effect
 */
#ifndef SCREEPS_EFFECT_H
#define SCREEPS_EFFECT_H

#include <optional>

namespace Screeps {

/**
 * @struct Effect
 * @brief Represents a game effect applied to a room object.
 *
 * Effects are special states that can be applied to creeps, structures, or rooms
 * that modify their behavior or properties for a limited duration.
 *
 * @see https://docs.screeps.com/api/#Effect
 */
struct Effect
{
	int effect;                /**< The effect type constant */
	std::optional<int> level;  /**< The level/power of the effect (optional) */
	int ticksRemaining;        /**< The number of ticks until the effect expires */
};

} // namespace Screeps

#endif // SCREEPS_EFFECT_H
