/**
 * @file StructureExtension.hpp
 * @brief StructureExtension class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureExtension
 */
#ifndef SCREEPS_STRUCTURE_EXTENSION_HPP
#define SCREEPS_STRUCTURE_EXTENSION_HPP

#include "Structure.hpp"

namespace Screeps {

class Store;

/**
 * @class StructureExtension
 * @brief A structure that extends a spawn's spawning capability.
 *
 * Extensions are structures that allow spawns to spawn larger creeps by providing
 * additional energy capacity. The number of extensions available depends on the
 * room controller level.
 *
 * @see https://docs.screeps.com/api/#StructureExtension
 * @see Structure
 */
class StructureExtension : public Structure
{
public:
	/**
	 * @brief Construct a StructureExtension from a JavaScript value.
	 * @param value The JavaScript value representing the extension.
	 */
	explicit StructureExtension(JS::Value value);

	/**
	 * @brief Get the store of this extension.
	 * @return The Store object containing energy in this extension.
	 * @see https://docs.screeps.com/api/#StructureExtension.store
	 */
	Store store() const;
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_EXTENSION_HPP
