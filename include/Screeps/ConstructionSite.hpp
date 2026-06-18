/**
 * @file ConstructionSite.hpp
 * @brief ConstructionSite class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#ConstructionSite
 */
#ifndef SCREEPS_CONSTRUCTION_SITE_HPP
#define SCREEPS_CONSTRUCTION_SITE_HPP

#include "Constants.hpp"
#include "RoomObject.hpp"

namespace Screeps {

/**
 * @class ConstructionSite
 * @brief A site where a structure is being constructed.
 *
 * Construction sites are temporary objects that represent structures currently
 * being built. Creeps with WORK body parts can build structures at construction
 * sites by moving adjacent to them and using the build action.
 *
 * @see https://docs.screeps.com/api/#ConstructionSite
 * @see RoomObject
 */
class ConstructionSite : public RoomObject
{
public:
	/**
	 * @brief Construct a ConstructionSite from a JavaScript value.
	 * @param value The JavaScript value representing the construction site.
	 */
	explicit ConstructionSite(JS::Value value);

	/**
	 * @brief Get the unique identifier of this construction site.
	 * @return The unique ID string.
	 * @see https://docs.screeps.com/api/#ConstructionSite.id
	 */
	std::string id() const;

	/**
	 * @brief Check if this construction site belongs to you.
	 * @return true if you own this construction site, false otherwise.
	 * @see https://docs.screeps.com/api/#ConstructionSite.my
	 */
	bool my() const;

	/**
	 * @brief Get the owner of this construction site.
	 * @return The username of the owner.
	 * @see https://docs.screeps.com/api/#ConstructionSite.owner
	 */
	std::string owner() const;

	/**
	 * @brief Get the current construction progress.
	 * @return The amount of work done on this construction site.
	 * @see https://docs.screeps.com/api/#ConstructionSite.progress
	 */
	int progress() const;

	/**
	 * @brief Get the total construction progress needed.
	 * @return The total amount of work required to complete this construction site.
	 * @see https://docs.screeps.com/api/#ConstructionSite.progressTotal
	 */
	int progressTotal() const;

	/**
	 * @brief Get the type of structure being constructed.
	 * @return The structure type string.
	 * @see https://docs.screeps.com/api/#ConstructionSite.structureType
	 * @see STRUCTURE_* constants in Constants.hpp
	 */
	std::string structureType() const;

	/**
	 * @brief Remove this construction site.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#ConstructionSite.remove
	 */
	int remove();

	/**
	 * @brief Find constant for construction sites.
	 * @see FIND_CONSTRUCTION_SITES
	 */
	static const int findConstant = Screeps::FIND_CONSTRUCTION_SITES;
};

} // namespace Screeps

#endif // SCREEPS_CONSTRUCTION_SITE_HPP
