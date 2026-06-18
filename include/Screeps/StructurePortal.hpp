#ifndef SCREEPS_STRUCTURE_PORTAL_HPP
#define SCREEPS_STRUCTURE_PORTAL_HPP

#include "Structure.hpp"

#include <optional>
#include <string>

namespace Screeps {

class RoomPosition;

class StructurePortal : public Structure
{
public:
	explicit StructurePortal(JS::Value value);

	std::optional<RoomPosition> destination() const;
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_PORTAL_HPP