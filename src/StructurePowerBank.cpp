#include "StructurePowerBank.hpp"

namespace Screeps {

StructurePowerBank::StructurePowerBank(JS::Value value) : OwnedStructure(std::move(value))
{
}

int StructurePowerBank::power() const
{
	return value()["power"].as<int>();
}

int StructurePowerBank::ticksToDecay() const
{
	return value()["ticksToDecay"].as<int>();
}

} // namespace Screeps