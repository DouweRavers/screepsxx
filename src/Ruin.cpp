#include "Ruin.hpp"

namespace Screeps {

Ruin::Ruin(JS::Value value) : RoomObject(std::move(value))
{
}

std::string Ruin::id() const
{
	return value()["id"].as<std::string>();
}

Store Ruin::store() const
{
	return Store(value()["store"]);
}

int Ruin::ticksToDecay() const
{
	return value()["ticksToDecay"].as<int>();
}

} // namespace Screeps
