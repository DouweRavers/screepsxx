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

class Tombstone : public RoomObject
{
public:
	explicit Tombstone(JS::Value value);

	std::unique_ptr<Creep> creep() const;
	std::unique_ptr<PowerCreep> powerCreep() const;
	int deathTime() const;
	std::string id() const;
	Store store() const;
	int ticksToDecay() const;
};

} // namespace Screeps

#endif // SCREEPS_TOMBSTONE_HPP