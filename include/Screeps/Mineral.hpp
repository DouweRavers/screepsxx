#ifndef SCREEPS_MINERAL_HPP
#define SCREEPS_MINERAL_HPP

#include "RoomObject.hpp"

#include <string>

namespace Screeps {

class Mineral : public RoomObject
{
public:
	explicit Mineral(JS::Value value);

	int density() const;
	int mineralAmount() const;
	std::string mineralType() const;
	int ticksToRegeneration() const;
};

} // namespace Screeps

#endif // SCREEPS_MINERAL_HPP