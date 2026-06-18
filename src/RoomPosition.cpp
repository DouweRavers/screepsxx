#include "RoomPosition.hpp"

#include "RoomObject.hpp"
#include "JS.hpp"
#include "JSON.hpp"

#include <iostream>

namespace Screeps {

RoomPosition::RoomPosition(JS::Value value) : Object(std::move(value))
{
}

RoomPosition::RoomPosition(const std::string& roomName, int x, int y)
    : Object(JS::getGlobal("RoomPosition").new_(x, y, roomName))
{
}

std::string RoomPosition::roomName() const
{
	return value()["roomName"].as<std::string>();
}

void RoomPosition::setRoomName(const std::string& name)
{
	value().set("roomName", name);
}

int RoomPosition::x() const
{
	return value()["x"].as<int>();
}

void RoomPosition::setX(int x)
{
	value().set("x", x);
}

int RoomPosition::y() const
{
	return value()["y"].as<int>();
}

void RoomPosition::setY(int y)
{
	value().set("y", y);
}

std::unique_ptr<RoomObject>
RoomPosition::findClosestByPath(const std::vector<std::unique_ptr<RoomObject>>& objects)
{
	std::vector<JS::Value> values;
	values.reserve(objects.size());
	for (const auto& object : objects)
		values.push_back(object->value());

	auto object = findClosestByPath(values);
	if (object)
		return createRoomObject(std::move(*object));
	else
		return nullptr;
}

std::optional<JS::Value> RoomPosition::findClosestByPath(const std::vector<JS::Value>& objects)
{
	auto array = JS::vectorToJSArray(objects);
	auto object = value().call<JS::Value>("findClosestByPath", array);
	if (object.isUndefined())
		return std::nullopt;
	else
		return object;
}

std::unique_ptr<RoomObject>
RoomPosition::findClosestByRange(const std::vector<std::unique_ptr<RoomObject>>& objects, const JSON& options)
{
	std::vector<JS::Value> values;
	values.reserve(objects.size());
	for (const auto& object : objects)
		values.push_back(object->value());

	auto object = findClosestByRange(values, options);
	if (object)
		return createRoomObject(std::move(*object));
	else
		return nullptr;
}

std::optional<JS::Value> RoomPosition::findClosestByRange(const std::vector<JS::Value>& objects, const JSON& options)
{
	auto array = JS::vectorToJSArray(objects);
	JS::Value jsOptions = options.empty() ? JS::Value::undefined() : JS::fromJSON(options);
	auto object = value().call<JS::Value>("findClosestByRange", array, jsOptions);
	if (object.isUndefined())
		return std::nullopt;
	else
		return object;
}

std::vector<std::unique_ptr<RoomObject>>
RoomPosition::findInRange(const std::vector<std::unique_ptr<RoomObject>>& objects, int range, const JSON& options)
{
	std::vector<JS::Value> values;
	values.reserve(objects.size());
	for (const auto& object : objects)
		values.push_back(object->value());

	auto result = findInRange(values, range, options);
	std::vector<std::unique_ptr<RoomObject>> roomObjects;
	roomObjects.reserve(result.size());
	for (const auto& obj : result)
		if (auto roomObj = createRoomObject(obj))
			roomObjects.push_back(std::move(roomObj));
	return roomObjects;
}

std::vector<JS::Value>
RoomPosition::findInRange(const std::vector<JS::Value>& objects, int range, const JSON& options)
{
	auto array = JS::vectorToJSArray(objects);
	JS::Value jsOptions = options.empty() ? JS::Value::undefined() : JS::fromJSON(options);
	return JS::jsArrayToVector(value().call<JS::Value>("findInRange", array, range, jsOptions));
}

std::vector<JSON> RoomPosition::findPathTo(int x, int y, const JSON& options)
{
	JS::Value jsOptions = options.empty() ? JS::Value::undefined() : JS::fromJSON(options);
	return JS::jsArrayToVector<JSON>(value().call<JS::Value>("findPathTo", x, y, jsOptions));
}

std::vector<JSON> RoomPosition::findPathTo(const RoomPosition& target, const JSON& options)
{
	JS::Value jsOptions = options.empty() ? JS::Value::undefined() : JS::fromJSON(options);
	return JS::jsArrayToVector<JSON>(value().call<JS::Value>("findPathTo", target.value(), jsOptions));
}

int RoomPosition::getDirectionTo(int x, int y) const
{
	return value().call<int>("getDirectionTo", x, y);
}

int RoomPosition::getDirectionTo(const RoomPosition& target) const
{
	return value().call<int>("getDirectionTo", target.value());
}

int RoomPosition::getRangeTo(int x, int y) const
{
	return value().call<int>("getRangeTo", x, y);
}

int RoomPosition::getRangeTo(const RoomPosition& target) const
{
	return value().call<int>("getRangeTo", target.value());
}

bool RoomPosition::inRangeTo(int x, int y, int range) const
{
	return value().call<bool>("inRangeTo", x, y, range);
}

bool RoomPosition::inRangeTo(const RoomPosition& target, int range) const
{
	return value().call<bool>("inRangeTo", target.value(), range);
}

bool RoomPosition::isEqualTo(int x, int y) const
{
	return value().call<bool>("isEqualTo", x, y);
}

bool RoomPosition::isEqualTo(const RoomPosition& target) const
{
	return value().call<bool>("isEqualTo", target.value());
}

bool RoomPosition::isNearTo(int x, int y) const
{
	return value().call<bool>("isNearTo", x, y);
}

bool RoomPosition::isNearTo(const RoomPosition& target) const
{
	return value().call<bool>("isNearTo", target.value());
}

std::vector<JS::Value> RoomPosition::look() const
{
	return JS::jsArrayToVector(value().call<JS::Value>("look"));
}

std::vector<JS::Value> RoomPosition::lookFor(const std::string& type) const
{
	return JS::jsArrayToVector(value().call<JS::Value>("lookFor", type));
}

int RoomPosition::createConstructionSite(const std::string& structureType, const std::optional<std::string>& name)
{
	if (name)
		return value().call<int>("createConstructionSite", structureType, *name);
	else
		return value().call<int>("createConstructionSite", structureType);
}

std::string RoomPosition::createFlag(const std::optional<std::string>& name, 
                                  const std::optional<int>& color, 
                                  const std::optional<int>& secondaryColor)
{
	if (name && color && secondaryColor)
		return value().call<std::string>("createFlag", *name, *color, *secondaryColor);
	else if (name && color)
		return value().call<std::string>("createFlag", *name, *color);
	else if (name)
		return value().call<std::string>("createFlag", *name);
	else
		return value().call<std::string>("createFlag");
}

} // namespace Screeps
