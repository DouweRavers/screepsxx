#ifndef SCREEPS_STRUCTURE_INVADER_CORE_HPP
#define SCREEPS_STRUCTURE_INVADER_CORE_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

class StructureSpawnSpawning;

class StructureInvaderCore : public OwnedStructure
{
public:
	explicit StructureInvaderCore(JS::Value value);

	int level() const;
	int ticksToDeploy() const;
	std::optional<StructureSpawnSpawning> spawning() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_INVADER_CORE_HPP