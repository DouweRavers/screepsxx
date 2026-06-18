#ifndef SCREEPS_STRUCTURE_POWER_SPAWN_HPP
#define SCREEPS_STRUCTURE_POWER_SPAWN_HPP

#include "OwnedStructure.hpp"
#include "JSON.hpp"

#include <string>

namespace Screeps {

class Store;

class StructurePowerSpawn : public OwnedStructure
{
public:
	explicit StructurePowerSpawn(JS::Value value);

	int energy() const;
	int energyCapacity() const;
	int power() const;
	int powerCapacity() const;
	Store store() const;

	int processPower();
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_POWER_SPAWN_HPP