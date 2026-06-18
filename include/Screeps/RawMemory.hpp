/**
 * @file RawMemory.hpp
 * @brief RawMemory class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#RawMemory
 */
#ifndef SCREEPS_RAW_MEMORY_HPP
#define SCREEPS_RAW_MEMORY_HPP

#include "Object.hpp"

namespace Screeps {

/**
 * @class RawMemoryObject
 * @brief Provides access to raw memory data.
 *
 * RawMemory is similar to Memory but provides direct access to the underlying
 * memory data without automatic serialization/deserialization. It's useful
 * for inter-shard communication and advanced memory management.
 *
 * @see https://docs.screeps.com/api/#RawMemory
 * @see Object
 */
class RawMemoryObject : public Object
{
public:
	/**
	 * @brief Construct a RawMemoryObject.
	 */
	RawMemoryObject();
};

/** Global RawMemory object instance. */
extern RawMemoryObject RawMemory;

} // namespace Screeps

#endif // SCREEPS_RAW_MEMORY_HPP
