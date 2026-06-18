/**
 * @file StructurePowerBank.hpp
 * @brief StructurePowerBank class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructurePowerBank
 */
#ifndef SCREEPS_STRUCTURE_POWER_BANK_HPP
#define SCREEPS_STRUCTURE_POWER_BANK_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

/**
 * @class StructurePowerBank
 * @brief A structure that stores power resource.
 *
 * Power Banks are structures that contain power resource. They can be attacked
 * to release power resource that can be harvested. They decay over time and
 * have a hit point value that must be reduced to zero to release the power.
 *
 * @see https://docs.screeps.com/api/#StructurePowerBank
 * @see OwnedStructure
 */
class StructurePowerBank : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructurePowerBank from a JavaScript value.
	 * @param value The JavaScript value representing the power bank.
	 */
	explicit StructurePowerBank(JS::Value value);

	/**
	 * @brief Get the amount of power in this power bank.
	 * @return The amount of power resource.
	 * @see https://docs.screeps.com/api/#StructurePowerBank.power
	 */
	int power() const;

	/**
	 * @brief Get the ticks until this power bank decays.
	 * @return The number of ticks until decay.
	 * @see https://docs.screeps.com/api/#StructurePowerBank.ticksToDecay
	 */
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_POWER_BANK_HPP