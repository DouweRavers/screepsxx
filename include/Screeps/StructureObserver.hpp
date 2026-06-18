#ifndef SCREEPS_STRUCTURE_OBSERVER_HPP
#define SCREEPS_STRUCTURE_OBSERVER_HPP

#include "OwnedStructure.hpp"

#include <string>

namespace Screeps {

class StructureObserver : public OwnedStructure
{
public:
	explicit StructureObserver(JS::Value value);

	int observeRoom(const std::string& roomName);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_OBSERVER_HPP