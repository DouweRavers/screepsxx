#ifndef SCREEPS_ROOM_HPP
#define SCREEPS_ROOM_HPP

#include "../nlohmann/json.hpp"
#include "Constants.hpp"
#include "Object.hpp"

namespace Screeps {
class RoomObject;
class RoomPosition;
class StructureController;
class StructureStorage;
class StructureTerminal;
class RoomVisual;
class RoomTerrain;

class Room : public Object
{
public:
    struct PathStep
    {
        int x;
        int y;
        int dx;
        int dy;
        int direction;
    };

    explicit Room(JS::Value value);

    // Properties
    std::optional<StructureController> controller() const;
    std::optional<StructureTerminal> terminal() const;
    std::optional<RoomVisual> visual() const;
    std::optional<StructureStorage> storage() const;

    // Energy
    int energyAvailable() const;
    int energyCapacityAvailable() const;

    // Memory
    JSON memory() const;
    void setMemory(const JSON& memory);

    // Metadata
    std::string name() const;

    // Pathfinding
    std::vector<PathStep> findPath(const RoomPosition& fromPos, const RoomPosition& toPos, const JSON& options = {});
    std::string serializePath(const std::vector<PathStep>& path) const;
    std::vector<PathStep> deserializePath(const std::string& path) const;

    // Position
    std::optional<RoomPosition> getPositionAt(int x, int y) const;
    RoomTerrain getTerrain() const;

    // Look
    std::vector<std::unique_ptr<RoomObject>> lookAt(int x, int y) const;
    std::vector<std::unique_ptr<RoomObject>> lookAt(const RoomPosition& target) const;
    std::vector<std::unique_ptr<RoomObject>> lookAtArea(int top, int left, int bottom, int right, const std::optional<bool>& asArray = std::nullopt) const;
    std::vector<std::unique_ptr<RoomObject>> lookForAt(const std::string& type, int x, int y) const;
    std::vector<std::unique_ptr<RoomObject>> lookForAt(const std::string& type, const RoomPosition& target) const;
    std::vector<std::unique_ptr<RoomObject>> lookForAtArea(const std::string& type, int top, int left, int bottom, int right, const std::optional<bool>& asArray = std::nullopt) const;

    // Construction
    int createConstructionSite(int x, int y, const std::string& structureType, const std::optional<std::string>& name = std::nullopt);
    int createConstructionSite(const RoomPosition& pos, const std::string& structureType, const std::optional<std::string>& name = std::nullopt);

    // Flags
    int createFlag(int x, int y, const std::optional<std::string>& name = std::nullopt, const std::optional<std::string>& color = std::nullopt, const std::optional<std::string>& secondaryColor = std::nullopt);
    int createFlag(const RoomPosition& pos, const std::optional<std::string>& name = std::nullopt, const std::optional<std::string>& color = std::nullopt, const std::optional<std::string>& secondaryColor = std::nullopt);

    // Find
    std::vector<std::unique_ptr<RoomObject>> find(int type, std::function<bool(const JS::Value&)> predicate = {}) const;
    template <class T>
    std::vector<std::unique_ptr<RoomObject>> find(std::function<bool(const T&)> predicate = {}) const
    {
        if (predicate)
        {
            auto p = [&](const JS::Value& value) { return predicate(T(value)); };
            return find(T::findConstant, p);
        }
        return find(T::findConstant);
    }

    // Exits
    int findExitTo(const std::string& room);
    int findExitTo(const Room& room);

    // Events
    std::vector<JSON> getEventLog(bool raw = false) const;

private:
    std::vector<std::unique_ptr<RoomObject>> createRoomObjects(const std::vector<JS::Value>& objects) const;
    std::vector<std::unique_ptr<RoomObject>> flattenAndCreateRoomObjects(JS::Value result) const;
};

} // namespace Screeps

#endif // SCREEPS_ROOM_HPP