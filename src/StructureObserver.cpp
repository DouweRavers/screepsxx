#include "StructureObserver.hpp"

namespace Screeps {

StructureObserver::StructureObserver(JS::Value value) : OwnedStructure(std::move(value))
{
}

int StructureObserver::observeRoom(const std::string& roomName)
{
	return value().call<int>("observeRoom", roomName);
}

} // namespace Screeps