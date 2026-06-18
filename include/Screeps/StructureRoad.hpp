/**
 * @file StructureRoad.hpp
 * @brief StructureRoad class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureRoad
 */
#ifndef SCREEPS_STRUCTURE_ROAD_HPP
#define SCREEPS_STRUCTURE_ROAD_HPP

#include "Structure.hpp"

namespace Screeps {

/**
 * @class StructureRoad
 * @brief A structure that allows faster movement.
 *
 * Roads are structures that reduce the movement cost for creeps. Creeps on roads
 * use less fatigue when moving. Roads decay over time if not repaired.
 *
 * @see https://docs.screeps.com/api/#StructureRoad
 * @see Structure
 */
class StructureRoad : public Structure
{
public:
	/**
	 * @brief Construct a StructureRoad from a JavaScript value.
	 * @param value The JavaScript value representing the road.
	 */
	explicit StructureRoad(JS::Value value);

	/**
	 * @brief Get the ticks until this road decays.
	 * @return The number of ticks until decay.
	 * @see https://docs.screeps.com/api/#StructureRoad.ticksToDecay
	 */
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_ROAD_HPP
