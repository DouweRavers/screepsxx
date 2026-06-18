#include "Mineral.hpp"

namespace Screeps {

Mineral::Mineral(JS::Value value) : RoomObject(std::move(value))
{
}

int Mineral::density() const
{
	return value()["density"].as<int>();
}

int Mineral::mineralAmount() const
{
	return value()["mineralAmount"].as<int>();
}

std::string Mineral::mineralType() const
{
	return value()["mineralType"].as<std::string>();
}

int Mineral::ticksToRegeneration() const
{
	return value()["ticksToRegeneration"].as<int>();
}

} // namespace Screeps