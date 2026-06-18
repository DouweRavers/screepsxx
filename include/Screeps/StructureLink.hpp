/**
 * @file StructureLink.hpp
 * @brief StructureLink class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureLink
 */
#ifndef SCREEPS_STRUCTURE_LINK_HPP
#define SCREEPS_STRUCTURE_LINK_HPP

#include "OwnedStructure.hpp"

namespace Screeps {

class Store;

/**
 * @class StructureLink
 * @brief A structure that can transfer energy between links.
 *
 * Links are structures that can store energy and transfer it to other links
 * across the room or between rooms. They are useful for distributing energy
 * efficiently across a base.
 *
 * @see https://docs.screeps.com/api/#StructureLink
 * @see OwnedStructure
 */
class StructureLink : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureLink from a JavaScript value.
	 * @param value The JavaScript value representing the link.
	 */
	explicit StructureLink(JS::Value value);

	/**
	 * @brief Get the current cooldown of this link.
	 * @return The remaining cooldown ticks.
	 * @see https://docs.screeps.com/api/#StructureLink.cooldown
	 */
	int cooldown() const;

	/**
	 * @brief Get the store of this link.
	 * @return The Store object containing energy in this link.
	 * @see https://docs.screeps.com/api/#StructureLink.store
	 */
	Store store() const;

	/**
	 * @brief Transfer energy to another link.
	 * @param target The target link to transfer energy to.
	 * @param amount The amount of energy to transfer (optional, defaults to all).
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_ENERGY, ERR_INVALID_TARGET, ERR_FULL, ERR_COOLDOWN, ERR_INVALID_ARGS).
	 * @see https://docs.screeps.com/api/#StructureLink.transferEnergy
	 */
	int transferEnergy(const StructureLink& target, const std::optional<int>& amount = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_LINK_HPP
