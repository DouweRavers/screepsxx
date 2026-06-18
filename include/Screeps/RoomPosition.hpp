#ifndef SCREEPS_ROOM_POSITION_HPP
#define SCREEPS_ROOM_POSITION_HPP

#include "Object.hpp"
#include "JSON.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace Screeps {

class RoomObject;

class RoomPosition : public Object
{
public:
	explicit RoomPosition(JS::Value value);
	RoomPosition(const std::string& roomName, int x, int y);

	std::string roomName() const;
	void setRoomName(const std::string& name);

	int x() const;
	void setX(int x);

	int y() const;
	void setY(int y);

	// Find methods
	std::unique_ptr<RoomObject>
	findClosestByPath(const std::vector<std::unique_ptr<RoomObject>>& objects);
	std::optional<JS::Value> findClosestByPath(const std::vector<JS::Value>& objects);
	
	std::unique_ptr<RoomObject>
	findClosestByRange(const std::vector<std::unique_ptr<RoomObject>>& objects, const JSON& options = {});
	std::optional<JS::Value> findClosestByRange(const std::vector<JS::Value>& objects, const JSON& options = {});
	
	std::vector<std::unique_ptr<RoomObject>>
	findInRange(const std::vector<std::unique_ptr<RoomObject>>& objects, int range, const JSON& options = {});
	std::vector<JS::Value>
	findInRange(const std::vector<JS::Value>& objects, int range, const JSON& options = {});

	// Path finding
	std::vector<JSON> findPathTo(int x, int y, const JSON& options = {});
	std::vector<JSON> findPathTo(const RoomPosition& target, const JSON& options = {});

	// Position utilities
	int getDirectionTo(int x, int y) const;
	int getDirectionTo(const RoomPosition& target) const;
	
	int getRangeTo(int x, int y) const;
	int getRangeTo(const RoomPosition& target) const;
	
	bool inRangeTo(int x, int y, int range) const;
	bool inRangeTo(const RoomPosition& target, int range) const;
	
	bool isEqualTo(int x, int y) const;
	bool isEqualTo(const RoomPosition& target) const;
	
	bool isNearTo(int x, int y) const;
	bool isNearTo(const RoomPosition& target) const;

	// Look methods
	std::vector<JS::Value> look() const;
	std::vector<JS::Value> lookFor(const std::string& type) const;

	// Creation methods
	int createConstructionSite(const std::string& structureType, const std::optional<std::string>& name = std::nullopt);
	std::string createFlag(const std::optional<std::string>& name = std::nullopt, 
	                     const std::optional<int>& color = std::nullopt, 
	                     const std::optional<int>& secondaryColor = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_ROOM_POSITION_HPP
