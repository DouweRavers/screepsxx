/**
 * @file StructurePortal.hpp
 * @brief StructurePortal class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructurePortal
 */
#ifndef SCREEPS_STRUCTURE_PORTAL_HPP
#define SCREEPS_STRUCTURE_PORTAL_HPP

#include "Structure.hpp"

#include <optional>
#include <string>

namespace Screeps {

class RoomPosition;

/**
 * @class StructurePortal
 * @brief A structure that provides a portal to another room.
 *
 * Portals are temporary structures that appear randomly and provide a direct
 * connection between two rooms. Creeps can move through portals to instantly
 * travel to the destination room. Portals decay over time.
 *
 * @see https://docs.screeps.com/api/#StructurePortal
 * @see Structure
 */
class StructurePortal : public Structure
{
public:
	/**
	 * @brief Construct a StructurePortal from a JavaScript value.
	 * @param value The JavaScript value representing the portal.
	 */
	explicit StructurePortal(JS::Value value);

	/**
	 * @brief Get the destination of this portal.
	 * @return Optional RoomPosition of the destination, or nullopt if not set.
	 * @see https://docs.screeps.com/api/#StructurePortal.destination
	 */
	std::optional<RoomPosition> destination() const;

	/**
	 * @brief Get the ticks until this portal decays.
	 * @return The number of ticks until decay.
	 * @see https://docs.screeps.com/api/#StructurePortal.ticksToDecay
	 */
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_PORTAL_HPP