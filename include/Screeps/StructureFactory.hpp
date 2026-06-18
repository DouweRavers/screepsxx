/**
 * @file StructureFactory.hpp
 * @brief StructureFactory class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureFactory
 */
#ifndef SCREEPS_STRUCTURE_FACTORY_HPP
#define SCREEPS_STRUCTURE_FACTORY_HPP

#include "OwnedStructure.hpp"
#include "JSON.hpp"

#include <string>

namespace Screeps {

class Store;

/**
 * @class StructureFactory
 * @brief A structure that can produce composite resources.
 *
 * Factories are structures that can combine basic resources to create composite
 * resources. They have a cooldown period between productions and can store
 * both input resources and output products.
 *
 * @see https://docs.screeps.com/api/#StructureFactory
 * @see OwnedStructure
 */
class StructureFactory : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureFactory from a JavaScript value.
	 * @param value The JavaScript value representing the factory.
	 */
	explicit StructureFactory(JS::Value value);

	/**
	 * @brief Get the current cooldown of this factory.
	 * @return The remaining cooldown ticks.
	 * @see https://docs.screeps.com/api/#StructureFactory.cooldown
	 */
	int cooldown() const;

	/**
	 * @brief Get the level of this factory.
	 * @return The factory level.
	 * @see https://docs.screeps.com/api/#StructureFactory.level
	 */
	int level() const;

	/**
	 * @brief Get the store of this factory.
	 * @return The Store object containing resources in this factory.
	 * @see https://docs.screeps.com/api/#StructureFactory.store
	 */
	Store store() const;

	/**
	 * @brief Get the store capacity of this factory.
	 * @return The maximum store capacity.
	 * @see https://docs.screeps.com/api/#StructureFactory.storeCapacity
	 */
	int storeCapacity() const;

	/**
	 * @brief Produce a resource.
	 * @param resourceType The type of resource to produce.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_ARGS, ERR_BUSY).
	 * @see https://docs.screeps.com/api/#StructureFactory.produce
	 */
	int produce(const std::string& resourceType);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_FACTORY_HPP