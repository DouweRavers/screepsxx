#ifndef SCREEPS_POWER_CREEP_HPP
#define SCREEPS_POWER_CREEP_HPP

#include "RoomObject.hpp"
#include "JSON.hpp"

#include <map>
#include <optional>
#include <string>

namespace Screeps {

class Store;
class Structure;
class StructurePowerSpawn;
class StructurePowerBank;
class StructureController;
class RoomObject;
class Resource;

class PowerCreep : public RoomObject
{
public:
	struct PowerInfo
	{
		int level;
		int cooldown;
	};

	explicit PowerCreep(JS::Value value);

	// Static method
	static int create(const std::string& name, const std::string& className);

	// Properties
	int carryCapacity() const;
	std::string className() const;
	int deleteTime() const;
	int hits() const;
	int hitsMax() const;
	std::string id() const;
	int level() const;
	JSON memory() const;
	void setMemory(const JSON& memory);
	bool my() const;
	std::string name() const;
	std::string owner() const;
	Store store() const;
	int spawnCooldownTime() const;
	int ticksToLive() const;

	// Methods
	int cancelOrder(const std::string& methodName);
	int deleteCreep(bool cancel = false);
	int drop(const std::string& resourceType, std::optional<int> amount = std::nullopt);
	int enableRoom(const StructureController& controller);
	int move(int direction);
	int move(const PowerCreep& direction);
	int moveByPath(const std::string& path);
	int moveTo(int x, int y, const std::optional<JSON>& options = std::nullopt);
	int moveTo(const RoomPosition& target, const std::optional<JSON>& options = std::nullopt);
	int moveTo(const RoomObject& target, const std::optional<JSON>& options = std::nullopt);
	int notifyWhenAttacked(bool enabled);
	int pickup(const Resource& target);
	int rename(const std::string& name);
	int renew(const StructurePowerSpawn& target);
	int renew(const StructurePowerBank& target);
	int say(const std::string& message, bool publicMessage = false);
	int spawn(const StructurePowerSpawn& powerSpawn);
	int suicide();
	int transfer(const PowerCreep& target, const std::string& resourceType, std::optional<int> amount = std::nullopt);
	int transfer(const Structure& target, const std::string& resourceType, std::optional<int> amount = std::nullopt);
	int upgrade(const std::string& power);
	int usePower(const std::string& power, const std::optional<RoomObject>& target = std::nullopt);
	int withdraw(const RoomObject& target, const std::string& resourceType, std::optional<int> amount = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_POWER_CREEP_HPP