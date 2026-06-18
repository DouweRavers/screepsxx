/**
 * @file Deposit.hpp
 * @brief Deposit class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#Deposit
 */
#ifndef SCREEPS_DEPOSIT_HPP
#define SCREEPS_DEPOSIT_HPP

#include "RoomObject.hpp"

namespace Screeps {

/**
 * @class Deposit
 * @brief A resource deposit that can be harvested.
 *
 * Deposits are special resource nodes that contain power resource. They appear
 * randomly in rooms and can be harvested by creeps with WORK body parts.
 * Deposits have a cooldown period after being harvested.
 *
 * @see https://docs.screeps.com/api/#Deposit
 * @see RoomObject
 */
class Deposit : public RoomObject
{
public:
	/**
	 * @brief Construct a Deposit from a JavaScript value.
	 * @param value The JavaScript value representing the deposit.
	 */
	explicit Deposit(JS::Value value);

	/**
	 * @brief Get the current cooldown of this deposit.
	 * @return The remaining cooldown ticks.
	 * @see https://docs.screeps.com/api/#Deposit.cooldown
	 */
	int cooldown() const;

	/**
	 * @brief Get the type of deposit.
	 * @return The deposit type string.
	 * @see https://docs.screeps.com/api/#Deposit.depositType
	 */
	std::string depositType() const;

	/**
	 * @brief Get the unique identifier of this deposit.
	 * @return The unique ID string.
	 * @see https://docs.screeps.com/api/#Deposit.id
	 */
	std::string id() const;

	/**
	 * @brief Get the last cooldown time of this deposit.
	 * @return The number of ticks since the last harvest.
	 * @see https://docs.screeps.com/api/#Deposit.lastCooldown
	 */
	int lastCooldown() const;

	/**
	 * @brief Get the ticks until this deposit decays.
	 * @return The number of ticks until decay.
	 * @see https://docs.screeps.com/api/#Deposit.ticksToDecay
	 */
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_DEPOSIT_HPP
