/**
 * @file StructurePowerSpawn.hpp
 * @brief StructurePowerSpawn class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructurePowerSpawn
 */
#ifndef SCREEPS_STRUCTURE_POWER_SPAWN_HPP
#define SCREEPS_STRUCTURE_POWER_SPAWN_HPP

#include "OwnedStructure.hpp"
#include "JSON.hpp"

#include <string>

namespace Screeps {

class Store;

/**
 * @class StructurePowerSpawn
 * @brief A structure that can spawn Power Creeps.
 *
 * Power Spawns are structures that can create Power Creeps using power resource.
 * They can also process power resource to create energy. Power Spawns have
 * separate capacities for energy and power resources.
 *
 * @see https://docs.screeps.com/api/#StructurePowerSpawn
 * @see OwnedStructure
 */
class StructurePowerSpawn : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructurePowerSpawn from a JavaScript value.
	 * @param value The JavaScript value representing the power spawn.
	 */
	explicit StructurePowerSpawn(JS::Value value);

	/**
	 * @brief Get the current energy in this power spawn.
	 * @return The amount of energy.
	 * @see https://docs.screeps.com/api/#StructurePowerSpawn.energy
	 */
	int energy() const;

	/**
	 * @brief Get the energy capacity of this power spawn.
	 * @return The maximum energy capacity.
	 * @see https://docs.screeps.com/api/#StructurePowerSpawn.energyCapacity
	 */
	int energyCapacity() const;

	/**
	 * @brief Get the current power in this power spawn.
	 * @return The amount of power resource.
	 * @see https://docs.screeps.com/api/#StructurePowerSpawn.power
	 */
	int power() const;

	/**
	 * @brief Get the power capacity of this power spawn.
	 * @return The maximum power capacity.
	 * @see https://docs.screeps.com/api/#StructurePowerSpawn.powerCapacity
	 */
	int powerCapacity() const;

	/**
	 * @brief Get the store of this power spawn.
	 * @return The Store object containing resources in this power spawn.
	 * @see https://docs.screeps.com/api/#StructurePowerSpawn.store
	 */
	Store store() const;

	/**
	 * @brief Process power into energy.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_RESOURCES, ERR_FULL).
	 * @see https://docs.screeps.com/api/#StructurePowerSpawn.processPower
	 */
	int processPower();
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_POWER_SPAWN_HPP