#include "StructurePortal.hpp"

#include "RoomPosition.hpp"

namespace Screeps {

StructurePortal::StructurePortal(JS::Value value) : Structure(std::move(value))
{
}

std::optional<RoomPosition> StructurePortal::destination() const
{
	if (value()["destination"].isUndefined())
		return std::nullopt;
	return RoomPosition(value()["destination"]);
}

int StructurePortal::ticksToDecay() const
{
	return value()["ticksToDecay"].as<int>();
}

} // namespace Screeps