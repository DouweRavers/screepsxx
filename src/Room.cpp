#include "Room.hpp"

#include "Creep.hpp"
#include "JS.hpp"
#include "JSON.hpp"
#include "RoomObject.hpp"
#include "RoomPosition.hpp"
#include "StructureController.hpp"
#include "StructureStorage.hpp"
#include "StructureTerminal.hpp"
#include "RoomVisual.hpp"
#include "RoomTerrain.hpp"

#include <algorithm>
#include <optional>
#include <vector>

namespace Screeps {

Room::Room(JS::Value value) : Object(std::move(value)) {}

// --- Properties ---
std::optional<StructureController> Room::controller() const {
    if (value()["controller"].isUndefined()) return std::nullopt;
    return StructureController(value()["controller"]);
}

std::optional<StructureTerminal> Room::terminal() const {
    if (value()["terminal"].isUndefined()) return std::nullopt;
    return StructureTerminal(value()["terminal"]);
}

std::optional<RoomVisual> Room::visual() const {
    if (value()["visual"].isUndefined()) return std::nullopt;
    return RoomVisual(value()["visual"]);
}

std::optional<StructureStorage> Room::storage() const {
    if (value()["storage"].isUndefined()) return std::nullopt;
    return StructureStorage(value()["storage"]);
}

// --- Energy ---
int Room::energyAvailable() const {
    return value()["energyAvailable"].as<int>();
}

int Room::energyCapacityAvailable() const {
    return value()["energyCapacityAvailable"].as<int>();
}

// --- Memory ---
JSON Room::memory() const {
    return JS::toJSON(value()["memory"]);
}

void Room::setMemory(const JSON& memory) {
    value().set("memory", JS::fromJSON(memory));
}

// --- Metadata ---
std::string Room::name() const {
    return value()["name"].as<std::string>();
}

// --- Pathfinding ---
std::vector<Room::PathStep> Room::findPath(const RoomPosition& fromPos, const RoomPosition& toPos, const JSON& options) {
    std::vector<PathStep> path;
    auto steps = JS::jsArrayToVector(value().call<JS::Value>("findPath", fromPos.value(), toPos.value(), JS::fromJSON(options)));
    for (const auto& step : steps) {
        path.push_back({
            step["x"].as<int>(),
            step["y"].as<int>(),
            step["dx"].as<int>(),
            step["dy"].as<int>(),
            step["direction"].as<int>()
        });
    }
    return path;
}

std::string Room::serializePath(const std::vector<PathStep>& path) const {
    JS::Value jsPath = JS::Value::array();
    for (size_t i = 0; i < path.size(); ++i) {
        JS::Value step = JS::Value::object();
        step.set("x", path[i].x);
        step.set("y", path[i].y);
        step.set("dx", path[i].dx);
        step.set("dy", path[i].dy);
        step.set("direction", path[i].direction);
        jsPath.set(i, step);
    }
    return JS::getGlobal("Room").call<std::string>("serializePath", jsPath);
}

std::vector<Room::PathStep> Room::deserializePath(const std::string& path) const {
    std::vector<PathStep> result;
    auto steps = JS::jsArrayToVector(JS::getGlobal("Room").call<JS::Value>("deserializePath", path));
    for (const auto& step : steps) {
        result.push_back({
            step["x"].as<int>(),
            step["y"].as<int>(),
            step["dx"].as<int>(),
            step["dy"].as<int>(),
            step["direction"].as<int>()
        });
    }
    return result;
}

// --- Position ---
std::optional<RoomPosition> Room::getPositionAt(int x, int y) const {
    JS::Value pos = value().call<JS::Value>("getPositionAt", x, y);
    if (pos.isUndefined()) return std::nullopt;
    return RoomPosition(pos);
}

RoomTerrain Room::getTerrain() const {
    return RoomTerrain(value().call<JS::Value>("getTerrain"));
}

// --- Look ---
std::vector<std::unique_ptr<RoomObject>> Room::lookAt(int x, int y) const {
    auto objects = JS::jsArrayToVector(value().call<JS::Value>("lookAt", x, y));
    return createRoomObjects(objects);
}

std::vector<std::unique_ptr<RoomObject>> Room::lookAt(const RoomPosition& target) const {
    auto objects = JS::jsArrayToVector(value().call<JS::Value>("lookAt", target.value()));
    return createRoomObjects(objects);
}

std::vector<std::unique_ptr<RoomObject>> Room::lookAtArea(int top, int left, int bottom, int right, const std::optional<bool>& asArray) const {
    JS::Value result = asArray ?
        value().call<JS::Value>("lookAtArea", top, left, bottom, right, *asArray) :
        value().call<JS::Value>("lookAtArea", top, left, bottom, right);
    return flattenAndCreateRoomObjects(result);
}

std::vector<std::unique_ptr<RoomObject>> Room::lookForAt(const std::string& type, int x, int y) const {
    auto objects = JS::jsArrayToVector(value().call<JS::Value>("lookForAt", type, x, y));
    return createRoomObjects(objects);
}

std::vector<std::unique_ptr<RoomObject>> Room::lookForAt(const std::string& type, const RoomPosition& target) const {
    auto objects = JS::jsArrayToVector(value().call<JS::Value>("lookForAt", type, target.value()));
    return createRoomObjects(objects);
}

std::vector<std::unique_ptr<RoomObject>> Room::lookForAtArea(const std::string& type, int top, int left, int bottom, int right, const std::optional<bool>& asArray) const {
    JS::Value result = asArray ?
        value().call<JS::Value>("lookForAtArea", type, top, left, bottom, right, *asArray) :
        value().call<JS::Value>("lookForAtArea", type, top, left, bottom, right);
    return flattenAndCreateRoomObjects(result);
}

// --- Construction ---
int Room::createConstructionSite(int x, int y, const std::string& structureType, const std::optional<std::string>& name) {
    if (name) {
        return value().call<int>("createConstructionSite", x, y, structureType, *name);
    }
    return value().call<int>("createConstructionSite", x, y, structureType);
}

int Room::createConstructionSite(const RoomPosition& pos, const std::string& structureType, const std::optional<std::string>& name) {
    if (name) {
        return value().call<int>("createConstructionSite", pos.value(), structureType, *name);
    }
    return value().call<int>("createConstructionSite", pos.value(), structureType);
}

// --- Flags ---
int Room::createFlag(int x, int y, const std::optional<std::string>& name, const std::optional<std::string>& color, const std::optional<std::string>& secondaryColor) {
    if (name && color && secondaryColor) {
        return value().call<int>("createFlag", x, y, *name, *color, *secondaryColor);
    } else if (name && color) {
        return value().call<int>("createFlag", x, y, *name, *color);
    } else if (name) {
        return value().call<int>("createFlag", x, y, *name);
    }
    return value().call<int>("createFlag", x, y);
}

int Room::createFlag(const RoomPosition& pos, const std::optional<std::string>& name, const std::optional<std::string>& color, const std::optional<std::string>& secondaryColor) {
    if (name && color && secondaryColor) {
        return value().call<int>("createFlag", pos.value(), *name, *color, *secondaryColor);
    } else if (name && color) {
        return value().call<int>("createFlag", pos.value(), *name, *color);
    } else if (name) {
        return value().call<int>("createFlag", pos.value(), *name);
    }
    return value().call<int>("createFlag", pos.value());
}

// --- Find ---
std::vector<std::unique_ptr<RoomObject>> Room::find(int type, std::function<bool(const JS::Value&)> predicate) const {
    auto objects = JS::jsArrayToVector(value().call<JS::Value>("find", type));
    if (predicate) {
        objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                          [&](const JS::Value& v) { return !predicate(v); }),
            objects.end());
    }
    return createRoomObjects(objects);
}

// --- Exits ---
int Room::findExitTo(const std::string& room) {
    return value().call<int>("findExitTo", room);
}

int Room::findExitTo(const Room& room) {
    return findExitTo(room.name());
}

// --- Events ---
std::vector<JSON> Room::getEventLog(bool raw) const {
    return JS::jsArrayToVector<JSON>(value().call<JS::Value>("getEventLog", raw));
}

// --- Helpers ---
std::vector<std::unique_ptr<RoomObject>> Room::createRoomObjects(const std::vector<JS::Value>& objects) const {
    std::vector<std::unique_ptr<RoomObject>> result;
    for (const auto& obj : objects) {
        if (auto roomObj = createRoomObject(obj)) {
            result.push_back(std::move(roomObj));
        }
    }
    return result;
}

std::vector<std::unique_ptr<RoomObject>> Room::flattenAndCreateRoomObjects(JS::Value result) const {
    std::vector<JS::Value> objects;
    if (result.isArray()) {
        int resultLength = result["length"].as<int>();
        if (resultLength > 0 && result[0].isArray()) {
            // Flatten 2D array
            for (uint32_t i = 0; i < resultLength; ++i) {
                JS::Value row = result[i];
                if (row.isArray()) {
                    int rowLength = row["length"].as<int>();
                    for (uint32_t j = 0; j < rowLength; ++j) {
                        objects.push_back(row[j]);
                    }
                }
            }
        } else {
            objects = JS::jsArrayToVector(result);
        }
    }
    return createRoomObjects(objects);
}

} // namespace Screeps