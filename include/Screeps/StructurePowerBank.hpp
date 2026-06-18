#ifndef SCREEPS_STRUCTURE_POWER_BANK_HPP
#define SCREEPS_STRUCTURE_POWER_BANK_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

class StructurePowerBank : public OwnedStructure
{
public:
	explicit StructurePowerBank(JS::Value value);

	int power() const;
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_POWER_BANK_HPP