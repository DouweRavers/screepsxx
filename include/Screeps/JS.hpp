/**
 * @file JS.hpp
 * @brief JavaScript interoperability utilities for Screeps C++ wrapper.
 *
 * This file provides utilities for interacting with JavaScript objects and values
 * from C++ code using Emscripten's val type. It includes functions for converting
 * between JavaScript and C++ types, accessing global JavaScript objects, and
 * console logging.
 */
#ifndef JS_HPP
#define JS_HPP

#include <emscripten/val.h>
#include <nlohmann/json_fwd.hpp>

#include <map>
#include <string>
#include <vector>

using JSON = nlohmann::json;

/**
 * @namespace JS
 * @brief JavaScript interoperability namespace.
 *
 * Provides utilities for working with JavaScript objects from C++.
 */
namespace JS {

/** @typedef Value
 * @brief JavaScript value type from Emscripten.
 */
using Value = emscripten::val;

// Global JS scope
const static Value gGlobal = Value::global();     /**< Global JavaScript scope */

// Global JS Object
const static Value gObject = Value::global("Object"); /**< Global JavaScript Object constructor */

/**
 * @brief Get a global JavaScript variable by name.
 * @param name The name of the global variable.
 * @return The JavaScript value.
 */
Value getGlobal(char const* name);

/**
 * @brief Get a global JavaScript variable by name.
 * @param name The name of the global variable.
 * @return The JavaScript value.
 */
Value getGlobal(const std::string& name);

/**
 * @brief Get a JavaScript constant by name.
 * @param name The name of the constant.
 * @return The JavaScript value.
 */
Value getConstant(const std::string& name);

/**
 * @brief Check if a value is an instance of a JavaScript class.
 * @param val The value to check.
 * @param name The name of the JavaScript class.
 * @return true if the value is an instance of the class, false otherwise.
 */
bool isInstanceOf(const Value& val, const char* name);

/**
 * @brief Convert a JavaScript array to a C++ vector.
 * @tparam T The type of elements in the array (default: Value).
 * @param array The JavaScript array to convert.
 * @return A vector containing the array elements.
 */
template <typename T = Value>
std::vector<T> jsArrayToVector(const Value& array)
{
	std::vector<T> result;
	int size = array["length"].as<int>();
	result.reserve(size);
	for (int i = 0; i < size; ++i)
		result.emplace_back(array[i].as<T>());
	return result;
}

/**
 * @brief Convert a JavaScript object to a C++ map.
 * @tparam T The type of values in the object (default: Value).
 * @param object The JavaScript object to convert.
 * @return A map containing the object properties.
 */
template <typename T = Value>
std::map<std::string, T> jsObjectToMap(const Value& object)
{
	std::map<std::string, T> result;
	Value keys = gObject.call<Value>("keys", object);
	int size = keys["length"].as<int>();
	for (int i = 0; i < size; ++i)
	{
		auto key = keys[i].as<std::string>();
		result.emplace_hint(result.end(), key, object[key].as<T>());
	}
	return result;
}

/**
 * @brief Convert a C++ vector to a JavaScript array.
 * @tparam T The type of elements in the vector.
 * @param vector The vector to convert.
 * @return A JavaScript array.
 */
template <typename T>
Value vectorToJSArray(const std::vector<T>& vector)
{
	Value array = Value::array();
	for (std::size_t i = 0; i < vector.size(); i++)
		array.set(i, static_cast<JS::Value>(vector[i]));
	return array;
}

/**
 * @brief Convert a C++ map to a JavaScript object.
 * @tparam K The key type of the map.
 * @tparam T The value type of the map.
 * @param map The map to convert.
 * @return A JavaScript object.
 */
template <typename K, typename T>
Value mapToJSObject(const std::map<K, T>& map)
{
	Value object = Value::object();
	for (const auto& pair : map)
		object.set(pair.first, pair.second);
	return object;
}

/**
 * @brief Convert a JSON object to a JavaScript value.
 * @param json The JSON object to convert.
 * @return A JavaScript value.
 */
Value fromJSON(const JSON& json);

/**
 * @brief Convert a JavaScript value to a JSON object.
 * @param value The JavaScript value to convert.
 * @return A JSON object.
 */
JSON toJSON(const Value& value);

/**
 * @class Console
 * @brief Provides access to the JavaScript console for logging.
 */
class Console
{
public:
	/**
	 * @brief Construct a Console object.
	 */
	Console();

	/**
	 * @brief Log a message to the console.
	 * @tparam Args Variadic template arguments for the log message.
	 * @param args The arguments to log.
	 */
	template <typename... Args>
	void log(Args&&... args)
	{
		object_.call<void>("log", std::forward<Args>(args)...);
	}

private:
	Value object_; /**< The JavaScript console object */
};

/** Global console instance for logging. */
extern Console console;

} // namespace JS

#endif // JS_HPP
