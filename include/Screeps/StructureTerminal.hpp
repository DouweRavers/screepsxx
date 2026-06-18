/**
 * @file StructureTerminal.hpp
 * @brief StructureTerminal class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#StructureTerminal
 */
#ifndef SCREEPS_STRUCTURE_TERMINAL_HPP
#define SCREEPS_STRUCTURE_TERMINAL_HPP

#include "OwnedStructure.hpp"
#include "Store.hpp"

#include <optional>

namespace Screeps {

/**
 * @class StructureTerminal
 * @brief A structure that can send resources to other terminals.
 *
 * Terminals are structures that can store resources and send them to other
 * terminals in different rooms. They enable inter-room resource transfer and
 * are essential for managing resources across multiple rooms.
 *
 * @see https://docs.screeps.com/api/#StructureTerminal
 * @see OwnedStructure
 */
class StructureTerminal : public OwnedStructure
{
public:
	/**
	 * @brief Construct a StructureTerminal from a JavaScript value.
	 * @param value The JavaScript value representing the terminal.
	 */
	explicit StructureTerminal(JS::Value value);

	/**
	 * @brief Get the current cooldown of this terminal.
	 * @return The remaining cooldown ticks.
	 * @see https://docs.screeps.com/api/#StructureTerminal.cooldown
	 */
	int cooldown() const;

	/**
	 * @brief Get the store of this terminal.
	 * @return The Store object containing resources in this terminal.
	 * @see https://docs.screeps.com/api/#StructureTerminal.store
	 */
	Store store() const;

	/**
	 * @brief Send resources to another terminal.
	 * @param resourceType The type of resource to send.
	 * @param amount The amount of resource to send.
	 * @param destination The name of the destination room.
	 * @param description Optional description for the transaction.
	 * @return Result code (OK, ERR_NOT_OWNER, ERR_NOT_ENOUGH_RESOURCES, ERR_INVALID_TARGET, ERR_FULL, ERR_INVALID_ARGS, ERR_COOLDOWN).
	 * @see https://docs.screeps.com/api/#StructureTerminal.send
	 */
	int send(const std::string& resourceType,
	         int amount,
	         const std::string& destination,
	         const std::optional<std::string>& description = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_TERMINAL_HPP
