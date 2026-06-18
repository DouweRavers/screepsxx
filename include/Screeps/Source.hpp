/**
 * @file Source.hpp
 * @brief Represents an energy source in a room.
 * 
 * This file defines the Source class which represents an energy source
 * that can be harvested by creeps with WORK body parts.
 */

#ifndef SCREEPS_SOURCE_HPP
#define SCREEPS_SOURCE_HPP

#include "Constants.hpp"
#include "RoomObject.hpp"

namespace Screeps {

/**
 * @class Source
 * @brief An energy source that can be harvested by creeps.
 * 
 * A Source is a naturally occurring energy deposit in a room that can
 * be harvested by creeps with WORK body parts. Each room typically has
 * 2-3 sources depending on the room type.
 * 
 * Source properties:
 * - In center rooms: 4000 energy capacity
 * - In owned/reserved rooms: 3000 energy capacity
 * - In unreserved rooms: 1500 energy capacity
 * - Energy regenerates every 300 game ticks
 * 
 * When a source is empty, it appears as a small brown spot. When full,
 * it appears as a larger yellow spot.
 * 
 * All sources can be found using Room::find() with FIND_SOURCES or
 * FIND_SOURCES_ACTIVE (for sources with energy).
 * 
 * @see RoomObject, Creep::harvest(), Room::find()
 */
class Source : public RoomObject
{
public:
	/**
	 * @brief Construct a Source from a JavaScript value.
	 * @param value The JavaScript Source value.
	 */
	explicit Source(JS::Value value);

	/**
	 * @brief Get the current amount of energy in the source.
	 * @return int The remaining energy amount.
	 * 
	 * @see energyCapacity()
	 */
	int energy() const;

	/**
	 * @brief Get the total energy capacity of the source.
	 * @return int The maximum energy the source can hold.
	 * 
	 * @see energy()
	 */
	int energyCapacity() const;

	/**
	 * @brief Get the unique identifier of the source.
	 * @return std::string The unique ID.
	 * 
	 * @see Game::getObjectById
	 */
	std::string id() const;

	/**
	 * @brief Get the remaining ticks until the source regenerates energy.
	 * 
	 * When a source is harvested, it takes 300 ticks to regenerate
	 * back to full capacity.
	 * 
	 * @return int The ticks remaining until regeneration.
	 */
	int ticksToLive() const;

	/**
	 * @brief The find constant for sources.
	 * 
	 * Use with Room::find() to find all sources.
	 * 
	 * @see Room::find
	 */
	static const int findConstant = Screeps::FIND_SOURCES;
};

} // namespace Screeps

#endif // SCREEPS_SOURCE_HPP
