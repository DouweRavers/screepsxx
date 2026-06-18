#ifndef SCREEPS_STRUCTURE_SPAWN_SPAWNING_HPP
#define SCREEPS_STRUCTURE_SPAWN_SPAWNING_HPP

#include "Object.hpp"

#include <string>
#include <vector>

namespace Screeps {

class StructureSpawn;

class StructureSpawnSpawning : public Object
{
public:
	explicit StructureSpawnSpawning(JS::Value value);

	std::vector<int> directions() const;
	std::string name() const;
	int needTime() const;
	int remainingTime() const;
	StructureSpawn spawn() const;

	int cancel();
	int setDirections(const std::vector<int>& directions);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_SPAWN_SPAWNING_HPP