/**
 * @file StructureContainer.hpp
 * @brief StructureContainer class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureContainer
 */
#ifndef SCREEPS_STRUCTURE_CONTAINER_HPP
#define SCREEPS_STRUCTURE_CONTAINER_HPP

#include "Structure.hpp"

namespace Screeps {

class Store;

/**
 * @class StructureContainer
 * @brief A structure that can store resources.
 *
 * Containers are structures that can store various resources. They are often
 * used for temporary storage near harvesting sites or construction sites.
 * Containers decay over time if not owned.
 *
 * @see https://docs.screeps.com/api/#StructureContainer
 * @see Structure
 */
class StructureContainer : public Structure
{
public:
	/**
	 * @brief Construct a StructureContainer from a JavaScript value.
	 * @param value The JavaScript value representing the container.
	 */
	explicit StructureContainer(JS::Value value);

	/**
	 * @brief Get the store of this container.
	 * @return The Store object containing resources in this container.
	 * @see https://docs.screeps.com/api/#StructureContainer.store
	 */
	Store store() const;

	/**
	 * @brief Get the ticks until this container decays.
	 * @return The number of ticks until decay (for unowned containers).
	 * @see https://docs.screeps.com/api/#StructureContainer.ticksToDecay
	 */
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_CONTAINER_HPP
