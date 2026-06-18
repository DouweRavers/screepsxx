#include "StructureSpawnSpawning.hpp"

#include "StructureSpawn.hpp"
#include "JS.hpp"

namespace Screeps {

StructureSpawnSpawning::StructureSpawnSpawning(JS::Value value) : Object(std::move(value))
{
}

std::vector<int> StructureSpawnSpawning::directions() const
{
	return JS::jsArrayToVector<int>(value()["directions"]);
}

std::string StructureSpawnSpawning::name() const
{
	return value()["name"].as<std::string>();
}

int StructureSpawnSpawning::needTime() const
{
	return value()["needTime"].as<int>();
}

int StructureSpawnSpawning::remainingTime() const
{
	return value()["remainingTime"].as<int>();
}

StructureSpawn StructureSpawnSpawning::spawn() const
{
	return StructureSpawn(value()["spawn"]);
}

int StructureSpawnSpawning::cancel()
{
	return value().call<int>("cancel");
}

int StructureSpawnSpawning::setDirections(const std::vector<int>& directions)
{
	return value().call<int>("setDirections", JS::vectorToJSArray(directions));
}

} // namespace Screeps