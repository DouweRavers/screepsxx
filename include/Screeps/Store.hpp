/**
 * @file Store.hpp
 * @brief Represents a container for resources.
 * 
 * This file defines the Store class which represents the inventory/cargo
 * of objects that can hold resources, such as creeps, containers, storages,
 * terminals, spawns, extensions, labs, and other structures.
 */

#ifndef SCREEPS_STORE_HPP
#define SCREEPS_STORE_HPP

#include "Object.hpp"

#include <optional>

namespace Screeps {

/**
 * @class Store
 * @brief A container for resources that can be stored and retrieved.
 * 
 * The Store class represents the inventory of objects that can carry or
 * store resources. There are two types of stores:
 * - General purpose stores: Can contain any resource within their capacity
 *   (e.g., creeps, containers, storages, terminals)
 * - Limited stores: Can only contain specific resource types needed for that
 *   object (e.g., spawns, extensions, labs, nukers)
 * 
 * Access specific resources using the array operator: store[RESOURCE_ENERGY]
 * 
 * @see Creep::store(), StructureContainer::store(), StructureStorage::store()
 */
class Store : public Object
{
public:
	/**
	 * @brief Construct a Store from a JavaScript value.
	 * @param value The JavaScript Store value.
	 */
	explicit Store(JS::Value value);

	/**
	 * @brief Get the total capacity for the store or a specific resource.
	 * 
	 * For general purpose stores, returns total capacity if no resource
	 * is specified. For limited stores, returns capacity for the specified
	 * resource if valid.
	 * 
	 * @param resource Optional resource type to get capacity for.
	 * @return std::optional<int> The capacity, or nullopt if the resource is
	 *   invalid for this store type.
	 * 
	 * @see getFreeCapacity, getUsedCapacity
	 */
	std::optional<int> getCapacity(const std::optional<std::string>& resource = std::nullopt);

	/**
	 * @brief Get the free capacity for the store or a specific resource.
	 * 
	 * Returns how much more of the resource can be stored.
	 * 
	 * @param resource Optional resource type to get free capacity for.
	 * @return std::optional<int> The free capacity, or nullopt if the resource
	 *   is invalid for this store type.
	 * 
	 * @see getCapacity, getUsedCapacity
	 */
	std::optional<int> getFreeCapacity(const std::optional<std::string>& resource = std::nullopt);

	/**
	 * @brief Get the used capacity for the store or a specific resource.
	 * 
	 * Returns how much of the resource is currently stored.
	 * 
	 * @param resource Optional resource type to get used capacity for.
	 * @return std::optional<int> The used capacity, or nullopt if the resource
	 *   is invalid for this store type.
	 * 
	 * @see getCapacity, getFreeCapacity
	 */
	std::optional<int> getUsedCapacity(const std::optional<std::string>& resource = std::nullopt);

	/**
	 * @brief Get the amount of a specific resource in the store.
	 * 
	 * @param resource The resource type to get the amount of.
	 * @return int The amount of the specified resource.
	 * 
	 * @usage
	 * @code
	 * Creep creep = ...;
	 * int energy = creep.store()[RESOURCE_ENERGY];
	 * if (energy < creep.store().getCapacity().value()) {
	 *     // Need more energy
	 * }
	 * @endcode
	 */
	int operator[](const std::string& resource);
};

} // namespace Screeps

#endif // SCREEPS_STORE_HPP
