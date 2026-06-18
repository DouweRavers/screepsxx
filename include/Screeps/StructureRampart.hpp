/**
 * @file StructureRampart.hpp
 * @brief StructureRampart class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureRampart
 */
#ifndef SCREEPS_STRUCTURE_RAMPART_HPP
#define SCREEPS_STRUCTURE_RAMPART_HPP

#include "Structure.hpp"

namespace Screeps {

/**
 * @class StructureRampart
 * @brief A defensive wall structure.
 *
 * Ramparts are defensive structures that block movement and provide protection
 * from attacks. They can be made public to allow allied creeps to pass through.
 * Ramparts decay over time if not repaired.
 *
 * @see https://docs.screeps.com/api/#StructureRampart
 * @see Structure
 */
class StructureRampart : public Structure
{
public:
	/**
	 * @brief Construct a StructureRampart from a JavaScript value.
	 * @param value The JavaScript value representing the rampart.
	 */
	explicit StructureRampart(JS::Value value);

	/**
	 * @brief Check if this rampart is public.
	 * @return true if public, false otherwise.
	 * @see https://docs.screeps.com/api/#StructureRampart.isPublic
	 */
	bool isPublic() const;

	/**
	 * @brief Get the ticks until this rampart decays.
	 * @return The number of ticks until decay.
	 * @see https://docs.screeps.com/api/#StructureRampart.ticksToDecay
	 */
	int ticksToDecay() const;

	/**
	 * @brief Set whether this rampart is public.
	 * @param isPublic true to make public, false to make private.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#StructureRampart.setPublic
	 */
	int setPublic(bool isPublic);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_RAMPART_HPP
