#include "StructureInvaderCore.hpp"
#include "StructureSpawnSpawning.hpp"

namespace Screeps {

StructureInvaderCore::StructureInvaderCore(JS::Value value) : OwnedStructure(std::move(value))
{
}

int StructureInvaderCore::level() const
{
	return value()["level"].as<int>();
}

int StructureInvaderCore::ticksToDeploy() const
{
	return value()["ticksToDeploy"].as<int>();
}

std::optional<StructureSpawnSpawning> StructureInvaderCore::spawning() const
{
	if (value()["spawning"].isUndefined())
		return std::nullopt;
	return StructureSpawnSpawning(value()["spawning"]);
}

} // namespace Screeps