/**
 * @file OwnedStructure.hpp
 * @brief Base class for structures that have an owner.
 * 
 * This file defines the OwnedStructure class which is the base class for
 * all structures that can be owned by a player. This includes most player-built
 * structures like spawns, towers, walls, extensions, etc.
 */

#ifndef SCREEPS_OWNED_STRUCTURE_HPP
#define SCREEPS_OWNED_STRUCTURE_HPP

#include "Structure.hpp"

namespace Screeps {

/**
 * @class OwnedStructure
 * @brief Base class for structures that have an owner.
 * 
 * OwnedStructure extends @ref Structure to add ownership information.
 * Structures that inherit from OwnedStructure can be owned by a specific
 * player and have methods to check and retrieve the owner.
 * 
 * Owned structures can be found using Room::find() with:
 * - FIND_MY_STRUCTURES: Only structures owned by you
 * - FIND_HOSTILE_STRUCTURES: Only structures not owned by you
 * 
 * @see Structure, Game::structures()
 */
class OwnedStructure : public Structure
{
public:
	/**
	 * @brief Construct an OwnedStructure from a JavaScript value.
	 * @param value The JavaScript OwnedStructure value.
	 */
	explicit OwnedStructure(JS::Value value);

	/**
	 * @brief Check if this is your own structure.
	 * @return bool True if owned by you, false otherwise.
	 */
	bool my() const;

	/**
	 * @brief Get the username of the structure's owner.
	 * @return std::string The owner's username.
	 */
	std::string owner() const;
};

} // namespace Screeps

#endif // SCREEPS_OWNED_STRUCTURE_HPP
