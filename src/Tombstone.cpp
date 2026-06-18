#include "Tombstone.hpp"

#include "Creep.hpp"
#include "PowerCreep.hpp"
#include "Store.hpp"

namespace Screeps {

Tombstone::Tombstone(JS::Value value) : RoomObject(std::move(value))
{
}

std::unique_ptr<Creep> Tombstone::creep() const
{
	if (value()["creep"].isUndefined())
		return nullptr;
	return std::make_unique<Creep>(value()["creep"]);
}

std::unique_ptr<PowerCreep> Tombstone::powerCreep() const
{
	if (value()["creep"].isUndefined())
		return nullptr;
	// Note: According to API, tombstone.creep can be Creep or PowerCreep
	// For now, we'll return nullptr for PowerCreep as it's not implemented yet
	return nullptr;
}

int Tombstone::deathTime() const
{
	return value()["deathTime"].as<int>();
}

std::string Tombstone::id() const
{
	return value()["id"].as<std::string>();
}

Store Tombstone::store() const
{
	return Store(value()["store"]);
}

int Tombstone::ticksToDecay() const
{
	return value()["ticksToDecay"].as<int>();
}

} // namespace Screeps