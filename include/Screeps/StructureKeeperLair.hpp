#ifndef SCREEPS_STRUCTURE_KEEPER_LAIR_HPP
#define SCREEPS_STRUCTURE_KEEPER_LAIR_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

class StructureKeeperLair : public OwnedStructure
{
public:
	explicit StructureKeeperLair(JS::Value value);

	int ticksToSpawn() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_KEEPER_LAIR_HPP