#ifndef SCREEPS_NUKE_HPP
#define SCREEPS_NUKE_HPP

#include "RoomObject.hpp"

#include <string>

namespace Screeps {

class Nuke : public RoomObject
{
public:
	explicit Nuke(JS::Value value);

	std::string launchRoomName() const;
	int timeToLand() const;
};

} // namespace Screeps

#endif // SCREEPS_NUKE_HPP