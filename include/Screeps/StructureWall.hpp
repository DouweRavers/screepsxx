/**
 * @file StructureWall.hpp
 * @brief StructureWall class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureWall
 */
#ifndef SCREEPS_STRUCTURE_WALL_HPP
#define SCREEPS_STRUCTURE_WALL_HPP

#include "Structure.hpp"

namespace Screeps {

/**
 * @class StructureWall
 * @brief A defensive wall structure.
 *
 * Walls are defensive structures that block movement and provide protection
 * from attacks. Unlike ramparts, walls cannot be made public and always block
 * all creeps.
 *
 * @see https://docs.screeps.com/api/#StructureWall
 * @see Structure
 */
class StructureWall : public Structure
{
public:
	/**
	 * @brief Construct a StructureWall from a JavaScript value.
	 * @param value The JavaScript value representing the wall.
	 */
	explicit StructureWall(JS::Value value);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_WALL_HPP
