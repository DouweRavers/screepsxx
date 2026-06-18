/**
 * @file Tombstone.hpp
 * @brief Tombstone class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Tombstone
 */
#ifndef SCREEPS_TOMBSTONE_HPP
#define SCREEPS_TOMBSTONE_HPP

#include "RoomObject.hpp"
#include "JSON.hpp"

#include <memory>
#include <string>

namespace Screeps {

class Creep;
class PowerCreep;
class Store;

/**
 * @class Tombstone
 * @brief The remains of a dead creep.
 *
 * Tombstones are created when creeps or power creeps die. They contain the
 * resources that the creep was carrying and decay over time. Tombstones can be
 * accessed to retrieve the dead creep's information and remaining resources.
 *
 * @see https://docs.screeps.com/api/#Tombstone
 * @see RoomObject
 */
class Tombstone : public RoomObject
{
public:
	/**
	 * @brief Construct a Tombstone from a JavaScript value.
	 * @param value The JavaScript value representing the tombstone.
	 */
	explicit Tombstone(JS::Value value);

	/**
	 * @brief Get the creep that died to create this tombstone.
	 * @return A unique pointer to the dead creep, or nullptr if not a creep.
	 * @see https://docs.screeps.com/api/#Tombstone.creep
	 */
	std::unique_ptr<Creep> creep() const;

	/**
	 * @brief Get the power creep that died to create this tombstone.
	 * @return A unique pointer to the dead power creep, or nullptr if not a power creep.
	 * @see https://docs.screeps.com/api/#Tombstone.powerCreep
	 */
	std::unique_ptr<PowerCreep> powerCreep() const;

	/**
	 * @brief Get the time when the creep died.
	 * @return The game tick when the creep died.
	 * @see https://docs.screeps.com/api/#Tombstone.deathTime
	 */
	int deathTime() const;

	/**
	 * @brief Get the unique identifier of this tombstone.
	 * @return The unique ID string.
	 * @see https://docs.screeps.com/api/#Tombstone.id
	 */
	std::string id() const;

	/**
	 * @brief Get the store of this tombstone.
	 * @return The Store object containing the resources the dead creep was carrying.
	 * @see https://docs.screeps.com/api/#Tombstone.store
	 */
	Store store() const;

	/**
	 * @brief Get the ticks until this tombstone decays.
	 * @return The number of ticks until decay.
	 * @see https://docs.screeps.com/api/#Tombstone.ticksToDecay
	 */
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_TOMBSTONE_HPP