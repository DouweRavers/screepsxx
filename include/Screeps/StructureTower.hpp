/**
 * @file StructureTower.hpp
 * @brief StructureTower class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureTower
 */
#ifndef SCREEPS_STRUCTURE_TOWER_HPP
#define SCREEPS_STRUCTURE_TOWER_HPP

#include "OwnedStructure.hpp"

namespace Screeps {

class Creep;
class Store;
class Structure;

/**
 * @class StructureTower
 * @brief A structure that can attack, heal, and repair other objects.
 *
 * Towers are defensive structures that can attack hostile creeps and structures,
 * heal friendly creeps, and repair damaged structures. They use energy from
 * their store to perform these actions.
 *
 * @see https://docs.screeps.com/api/#StructureTower
 * @see OwnedStructure
 */
class StructureTower : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureTower from a JavaScript value.
	 * @param value The JavaScript value representing the tower.
	 */
	explicit StructureTower(JS::Value value);

	/**
	 * @brief Get the store of this tower.
	 * @return The Store object containing resources in this tower.
	 * @see https://docs.screeps.com/api/#StructureTower.store
	 */
	Store store() const;

	/**
	 * @brief Attack a target creep.
	 * @param target The creep to attack.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NO_PATH, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_TIRED, ERR_NOT_ENOUGH_ENERGY).
	 * @see https://docs.screeps.com/api/#StructureTower.attack
	 */
	int attack(const Creep& target);

	/**
	 * @brief Attack a target structure.
	 * @param target The structure to attack.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NO_PATH, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_TIRED, ERR_NOT_ENOUGH_ENERGY).
	 * @see https://docs.screeps.com/api/#StructureTower.attack
	 */
	int attack(const Structure& target);

	/**
	 * @brief Heal a target creep.
	 * @param target The creep to heal.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NO_PATH, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_TIRED, ERR_NOT_ENOUGH_ENERGY).
	 * @see https://docs.screeps.com/api/#StructureTower.heal
	 */
	int heal(const Creep& target);

	/**
	 * @brief Repair a target structure.
	 * @param target The structure to repair.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NO_PATH, ERR_INVALID_TARGET, ERR_NOT_IN_RANGE, ERR_TIRED, ERR_NOT_ENOUGH_ENERGY).
	 * @see https://docs.screeps.com/api/#StructureTower.repair
	 */
	int repair(const Structure& target);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_TOWER_HPP
