#include "Nuke.hpp"

namespace Screeps {

Nuke::Nuke(JS::Value value) : RoomObject(std::move(value))
{
}

std::string Nuke::launchRoomName() const
{
	return value()["launchRoomName"].as<std::string>();
}

int Nuke::timeToLand() const
{
	return value()["timeToLand"].as<int>();
}

} // namespace Screeps