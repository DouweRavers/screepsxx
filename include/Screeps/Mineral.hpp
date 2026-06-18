/**
 * @file Mineral.hpp
 * @brief Mineral class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Mineral
 */
#ifndef SCREEPS_MINERAL_HPP
#define SCREEPS_MINERAL_HPP

#include "RoomObject.hpp"

#include <string>

namespace Screeps {

/**
 * @class Mineral
 * @brief A mineral deposit that can be harvested for resources.
 *
 * Minerals are resource nodes that contain various mineral types (H, O, L, K, Z, U, X).
 * They appear in rooms and can be harvested by creeps with WORK body parts.
 * Each mineral has a density that affects the amount of resource available.
 *
 * @see https://docs.screeps.com/api/#Mineral
 * @see RoomObject
 */
class Mineral : public RoomObject
{
public:
	/**
	 * @brief Construct a Mineral from a JavaScript value.
	 * @param value The JavaScript value representing the mineral.
	 */
	explicit Mineral(JS::Value value);

	/**
	 * @brief Get the density of this mineral.
	 * @return The density value (1-4, with 4 being highest).
	 * @see https://docs.screeps.com/api/#Mineral.density
	 * @see DENSITY_* constants in Constants.hpp
	 */
	int density() const;

	/**
	 * @brief Get the current amount of mineral available.
	 * @return The amount of mineral remaining.
	 * @see https://docs.screeps.com/api/#Mineral.mineralAmount
	 */
	int mineralAmount() const;

	/**
	 * @brief Get the type of mineral.
	 * @return The mineral type string.
	 * @see https://docs.screeps.com/api/#Mineral.mineralType
	 * @see RESOURCE_* constants in Constants.hpp
	 */
	std::string mineralType() const;

	/**
	 * @brief Get the ticks until this mineral regenerates.
	 * @return The number of ticks until regeneration.
	 * @see https://docs.screeps.com/api/#Mineral.ticksToRegeneration
	 */
	int ticksToRegeneration() const;
};

} // namespace Screeps

#endif // SCREEPS_MINERAL_HPP