#include "StructureFactory.hpp"

#include "Store.hpp"

namespace Screeps {

StructureFactory::StructureFactory(JS::Value value) : OwnedStructure(std::move(value))
{
}

int StructureFactory::cooldown() const
{
	return value()["cooldown"].as<int>();
}

int StructureFactory::level() const
{
	return value()["level"].as<int>();
}

Store StructureFactory::store() const
{
	return Store(value()["store"]);
}

int StructureFactory::storeCapacity() const
{
	return value()["storeCapacity"].as<int>();
}

int StructureFactory::produce(const std::string& resourceType)
{
	return value().call<int>("produce", resourceType);
}

} // namespace Screeps