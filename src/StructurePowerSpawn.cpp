#include "StructurePowerSpawn.hpp"

#include "Store.hpp"

namespace Screeps {

StructurePowerSpawn::StructurePowerSpawn(JS::Value value) : OwnedStructure(std::move(value))
{
}

int StructurePowerSpawn::energy() const
{
	return value()["energy"].as<int>();
}

int StructurePowerSpawn::energyCapacity() const
{
	return value()["energyCapacity"].as<int>();
}

int StructurePowerSpawn::power() const
{
	return value()["power"].as<int>();
}

int StructurePowerSpawn::powerCapacity() const
{
	return value()["powerCapacity"].as<int>();
}

Store StructurePowerSpawn::store() const
{
	return Store(value()["store"]);
}

int StructurePowerSpawn::processPower()
{
	return value().call<int>("processPower");
}

} // namespace Screeps