/**
 * @file Memory.hpp
 * @brief Memory class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Memory
 */
#ifndef SCREEPS_MEMORY_HPP
#define SCREEPS_MEMORY_HPP

#include "Object.hpp"

#include <string_view>

namespace Screeps {

/**
 * @class MemoryObject
 * @brief Provides access to the global Memory object in Screeps.
 *
 * The Memory object is a global persistent storage that can be used to store
 * custom data between game ticks. It's automatically saved and loaded by the
 * game engine.
 *
 * @see https://docs.screeps.com/api/#Memory
 * @see Object
 */
class MemoryObject : public Object
{
public:
	/**
	 * @brief Construct a MemoryObject.
	 */
	MemoryObject();

	/**
	 * @brief Get a value from memory by key.
	 * @param key The key to retrieve.
	 * @return The JSON value associated with the key.
	 * @see https://docs.screeps.com/api/#Memory
	 */
	JSON operator[](const std::string_view& key);

	/**
	 * @brief Set a value in memory by key.
	 * @param key The key to set.
	 * @param value The JSON value to store.
	 * @see https://docs.screeps.com/api/#Memory
	 */
	void set(const std::string_view& key, const JSON& value);
};

/** Global Memory object instance. */
extern MemoryObject Memory;

} // namespace Screeps

#endif // SCREEPS_MEMORY_HPP
