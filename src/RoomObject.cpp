#include "RoomObject.hpp"

#include "ConstructionSite.hpp"
#include "Creep.hpp"
#include "Deposit.hpp"
#include "Effect.hpp"
#include "Flag.hpp"
#include "Mineral.hpp"
#include "Nuke.hpp"
#include "PowerCreep.hpp"
#include "Resource.hpp"
#include "Room.hpp"
#include "RoomPosition.hpp"
#include "Ruin.hpp"
#include "Source.hpp"
#include "StructureContainer.hpp"
#include "StructureController.hpp"
#include "StructureExtension.hpp"
#include "StructureExtractor.hpp"
#include "StructureFactory.hpp"
#include "StructureInvaderCore.hpp"
#include "StructureKeeperLair.hpp"
#include "StructureLink.hpp"
#include "StructureNuker.hpp"
#include "StructureObserver.hpp"
#include "StructurePowerBank.hpp"
#include "StructurePowerSpawn.hpp"
#include "StructurePortal.hpp"
#include "StructureRampart.hpp"
#include "StructureRoad.hpp"
#include "StructureSpawn.hpp"
#include "StructureStorage.hpp"
#include "StructureTerminal.hpp"
#include "StructureTower.hpp"
#include "StructureWall.hpp"
#include "Tombstone.hpp"

namespace Screeps {

RoomObject::RoomObject(JS::Value value) : Object(std::move(value))
{
}

RoomObject::~RoomObject() = default;

std::vector<Effect> RoomObject::effects() const
{
	std::vector<Effect> list;
	for (const auto& elem : JS::jsArrayToVector(value()["effects"]))
	{
		Effect effect;
		effect.effect = elem["effect"].as<int>();
		if (!elem["level"].isUndefined())
			effect.level = elem["level"].as<int>();
		effect.ticksRemaining = elem["ticksRemaining"].as<int>();
		list.push_back(std::move(effect));
	}
	return list;
}

RoomPosition RoomObject::pos() const
{
	return RoomPosition(value()["pos"]);
}

Room RoomObject::room() const
{
	return Room(value()["room"]);
}

std::unique_ptr<RoomObject> createRoomObject(JS::Value object)
{
	auto is = [&](const char* type)
	{
		return JS::isInstanceOf(object, type);
	};

	// FIXME: sort by rarity
	if (is("Structure"))
	{
		std::string type = object["structureType"].as<std::string>();
		if (type == Screeps::STRUCTURE_ROAD)
			return std::make_unique<StructureRoad>(std::move(object));
		else if (type == Screeps::STRUCTURE_WALL)
			return std::make_unique<StructureWall>(std::move(object));
		else if (type == Screeps::STRUCTURE_RAMPART)
			return std::make_unique<StructureRampart>(std::move(object));
		else if (type == Screeps::STRUCTURE_EXTENSION)
			return std::make_unique<StructureExtension>(std::move(object));
		else if (type == Screeps::STRUCTURE_CONTAINER)
			return std::make_unique<StructureContainer>(std::move(object));
		else if (type == Screeps::STRUCTURE_TOWER)
			return std::make_unique<StructureTower>(std::move(object));
		else if (type == Screeps::STRUCTURE_LINK)
			return std::make_unique<StructureLink>(std::move(object));
		else if (type == Screeps::STRUCTURE_SPAWN)
			return std::make_unique<StructureSpawn>(std::move(object));
		else if (type == Screeps::STRUCTURE_CONTROLLER)
			return std::make_unique<StructureController>(std::move(object));
		else if (type == Screeps::STRUCTURE_STORAGE)
			return std::make_unique<StructureStorage>(std::move(object));
		else if (type == Screeps::STRUCTURE_EXTRACTOR)
			return std::make_unique<StructureExtractor>(std::move(object));
		else if (type == Screeps::STRUCTURE_TERMINAL)
			return std::make_unique<StructureTerminal>(std::move(object));
		else if (type == Screeps::STRUCTURE_FACTORY)
			return std::make_unique<StructureFactory>(std::move(object));
		else if (type == Screeps::STRUCTURE_INVADER_CORE)
			return std::make_unique<StructureInvaderCore>(std::move(object));
		else if (type == Screeps::STRUCTURE_KEEPER_LAIR)
			return std::make_unique<StructureKeeperLair>(std::move(object));
		else if (type == Screeps::STRUCTURE_NUKER)
			return std::make_unique<StructureNuker>(std::move(object));
		else if (type == Screeps::STRUCTURE_OBSERVER)
			return std::make_unique<StructureObserver>(std::move(object));
		else if (type == Screeps::STRUCTURE_POWER_BANK)
			return std::make_unique<StructurePowerBank>(std::move(object));
		else if (type == Screeps::STRUCTURE_POWER_SPAWN)
			return std::make_unique<StructurePowerSpawn>(std::move(object));
		else if (type == Screeps::STRUCTURE_PORTAL)
			return std::make_unique<StructurePortal>(std::move(object));
		else
			return nullptr;
	}
	else if (is("Creep"))
		return std::make_unique<Creep>(std::move(object));
	else if (is("Source"))
		return std::make_unique<Source>(std::move(object));
	else if (is("ConstructionSite"))
		return std::make_unique<ConstructionSite>(std::move(object));
	else if (is("Ruin"))
		return std::make_unique<Ruin>(std::move(object));
	else if (is("Deposit"))
		return std::make_unique<Deposit>(std::move(object));
	else if (is("Flag"))
		return std::make_unique<Flag>(std::move(object));
	else if (is("Resource"))
		return std::make_unique<Resource>(std::move(object));
	else if (is("Mineral"))
		return std::make_unique<Mineral>(std::move(object));
	else if (is("Nuke"))
		return std::make_unique<Nuke>(std::move(object));
	else if (is("Tombstone"))
		return std::make_unique<Tombstone>(std::move(object));
	else if (is("PowerCreep"))
		return std::make_unique<PowerCreep>(std::move(object));
	else
		return nullptr;
}

} // namespace Screeps
