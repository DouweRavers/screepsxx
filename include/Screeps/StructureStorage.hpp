/**
 * @file StructureStorage.hpp
 * @brief StructureStorage class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureStorage
 */
#ifndef SCREEPS_STRUCTURE_STORAGE_HPP
#define SCREEPS_STRUCTURE_STORAGE_HPP

#include "OwnedStructure.hpp"

namespace Screeps {

class Store;

/**
 * @class StructureStorage
 * @brief A structure that can store large amounts of resources.
 *
 * Storage is a large structure that can store various resources. It has a very
 * high capacity compared to other storage structures and is typically used as
 * the main storage facility in a room.
 *
 * @see https://docs.screeps.com/api/#StructureStorage
 * @see OwnedStructure
 */
class StructureStorage : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureStorage from a JavaScript value.
	 * @param value The JavaScript value representing the storage.
	 */
	explicit StructureStorage(JS::Value value);

	/**
	 * @brief Get the store of this storage.
	 * @return The Store object containing resources in this storage.
	 * @see https://docs.screeps.com/api/#StructureStorage.store
	 */
	Store store() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_STORAGE_HPP
