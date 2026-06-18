#include "StructureNuker.hpp"

#include "Store.hpp"
#include "RoomPosition.hpp"

namespace Screeps {

StructureNuker::StructureNuker(JS::Value value) : OwnedStructure(std::move(value))
{
}

int StructureNuker::cooldown() const
{
	return value()["cooldown"].as<int>();
}

Store StructureNuker::store() const
{
	return Store(value()["store"]);
}

int StructureNuker::launchNuke(const RoomPosition& pos)
{
	return value().call<int>("launchNuke", pos.value());
}

} // namespace Screeps