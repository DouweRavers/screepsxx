#ifndef SCREEPS_STRUCTURE_NUKER_HPP
#define SCREEPS_STRUCTURE_NUKER_HPP

#include "OwnedStructure.hpp"
#include "JSON.hpp"

#include <string>

namespace Screeps {

class RoomPosition;
class Store;

class StructureNuker : public OwnedStructure
{
public:
	explicit StructureNuker(JS::Value value);

	int cooldown() const;
	Store store() const;

	int launchNuke(const RoomPosition& pos);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_NUKER_HPP