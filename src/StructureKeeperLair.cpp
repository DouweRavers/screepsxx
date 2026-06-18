#include "StructureKeeperLair.hpp"

namespace Screeps {

StructureKeeperLair::StructureKeeperLair(JS::Value value) : OwnedStructure(std::move(value))
{
}

int StructureKeeperLair::ticksToSpawn() const
{
	return value()["ticksToSpawn"].as<int>();
}

} // namespace Screeps