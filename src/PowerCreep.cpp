#include "PowerCreep.hpp"

#include "Store.hpp"
#include "JS.hpp"
#include "Resource.hpp"
#include "Structure.hpp"
#include "RoomPosition.hpp"
#include "StructureController.hpp"
#include "StructurePowerSpawn.hpp"
#include "StructurePowerBank.hpp"

namespace Screeps {

PowerCreep::PowerCreep(JS::Value value) : RoomObject(std::move(value))
{
}

int PowerCreep::create(const std::string& name, const std::string& className)
{
	return JS::getGlobal("PowerCreep").call<int>("create", name, className);
}

int PowerCreep::carryCapacity() const
{
	return value()["carryCapacity"].as<int>();
}

std::string PowerCreep::className() const
{
	return value()["className"].as<std::string>();
}

int PowerCreep::deleteTime() const
{
	if (value()["deleteTime"].isUndefined())
		return 0;
	return value()["deleteTime"].as<int>();
}

int PowerCreep::hits() const
{
	return value()["hits"].as<int>();
}

int PowerCreep::hitsMax() const
{
	return value()["hitsMax"].as<int>();
}

std::string PowerCreep::id() const
{
	return value()["id"].as<std::string>();
}

int PowerCreep::level() const
{
	return value()["level"].as<int>();
}

JSON PowerCreep::memory() const
{
	return JS::toJSON(value()["memory"]);
}

void PowerCreep::setMemory(const JSON& memory)
{
	value().set("memory", JS::fromJSON(memory));
}

bool PowerCreep::my() const
{
	return value()["my"].as<bool>();
}

std::string PowerCreep::name() const
{
	return value()["name"].as<std::string>();
}

std::string PowerCreep::owner() const
{
	return value()["owner"]["username"].as<std::string>();
}

Store PowerCreep::store() const
{
	return Store(value()["store"]);
}

int PowerCreep::spawnCooldownTime() const
{
	if (value()["spawnCooldownTime"].isUndefined())
		return 0;
	return value()["spawnCooldownTime"].as<int>();
}

int PowerCreep::ticksToLive() const
{
	if (value()["ticksToLive"].isUndefined())
		return 0;
	return value()["ticksToLive"].as<int>();
}

int PowerCreep::cancelOrder(const std::string& methodName)
{
	return value().call<int>("cancelOrder", methodName);
}

int PowerCreep::deleteCreep(bool cancel)
{
	return value().call<int>("delete", cancel);
}

int PowerCreep::drop(const std::string& resourceType, std::optional<int> amount)
{
	if (amount)
		return value().call<int>("drop", resourceType, *amount);
	else
		return value().call<int>("drop", resourceType);
}

int PowerCreep::enableRoom(const StructureController& controller)
{
	return value().call<int>("enableRoom", controller.value());
}

int PowerCreep::move(int direction)
{
	return value().call<int>("move", direction);
}

int PowerCreep::move(const PowerCreep& direction)
{
	return value().call<int>("move", direction.value());
}

int PowerCreep::moveByPath(const std::string& path)
{
	return value().call<int>("moveByPath", path);
}

int PowerCreep::moveTo(int x, int y, const std::optional<JSON>& options)
{
	if (options)
		return value().call<int>("moveTo", x, y, JS::fromJSON(*options));
	else
		return value().call<int>("moveTo", x, y);
}

int PowerCreep::moveTo(const RoomPosition& target, const std::optional<JSON>& options)
{
	if (options)
		return value().call<int>("moveTo", target.value(), JS::fromJSON(*options));
	else
		return value().call<int>("moveTo", target.value());
}

int PowerCreep::moveTo(const RoomObject& target, const std::optional<JSON>& options)
{
	if (options)
		return value().call<int>("moveTo", target.value(), JS::fromJSON(*options));
	else
		return value().call<int>("moveTo", target.value());
}

int PowerCreep::notifyWhenAttacked(bool enabled)
{
	return value().call<int>("notifyWhenAttacked", enabled);
}

int PowerCreep::pickup(const Resource& target)
{
	return value().call<int>("pickup", target.value());
}

int PowerCreep::rename(const std::string& name)
{
	return value().call<int>("rename", name);
}

int PowerCreep::renew(const StructurePowerSpawn& target)
{
	return value().call<int>("renew", target.value());
}

int PowerCreep::renew(const StructurePowerBank& target)
{
	return value().call<int>("renew", target.value());
}

int PowerCreep::say(const std::string& message, bool publicMessage)
{
	return value().call<int>("say", message, publicMessage);
}

int PowerCreep::spawn(const StructurePowerSpawn& powerSpawn)
{
	return value().call<int>("spawn", powerSpawn.value());
}

int PowerCreep::suicide()
{
	return value().call<int>("suicide");
}

int PowerCreep::transfer(const PowerCreep& target, const std::string& resourceType, std::optional<int> amount)
{
	if (amount)
		return value().call<int>("transfer", target.value(), resourceType, *amount);
	else
		return value().call<int>("transfer", target.value(), resourceType);
}

int PowerCreep::transfer(const Structure& target, const std::string& resourceType, std::optional<int> amount)
{
	if (amount)
		return value().call<int>("transfer", target.value(), resourceType, *amount);
	else
		return value().call<int>("transfer", target.value(), resourceType);
}

int PowerCreep::upgrade(const std::string& power)
{
	return value().call<int>("upgrade", power);
}

int PowerCreep::usePower(const std::string& power, const std::optional<RoomObject>& target)
{
	if (target)
		return value().call<int>("usePower", power, target->value());
	else
		return value().call<int>("usePower", power);
}

int PowerCreep::withdraw(const RoomObject& target, const std::string& resourceType, std::optional<int> amount)
{
	if (amount)
		return value().call<int>("withdraw", target.value(), resourceType, *amount);
	else
		return value().call<int>("withdraw", target.value(), resourceType);
}

} // namespace Screeps