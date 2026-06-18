/**
 * @file Object.hpp
 * @brief Base class for all Screeps game objects.
 * 
 * This file defines the Object class which serves as the base class for all
 * Screeps game objects in the C++ wrapper. It provides the fundamental
 * interface for accessing the underlying JavaScript values from the Screeps
 * game engine.
 */

#ifndef SCREEPS_OBJECT_HPP
#define SCREEPS_OBJECT_HPP

#include "JS.hpp"

namespace Screeps {

/**
 * @class Object
 * @brief Base class for all Screeps game objects.
 * 
 * The Object class is the fundamental base class that all Screeps game objects
 * inherit from. It wraps a JavaScript value from the Screeps game engine and
 * provides the basic interface for accessing and manipulating that value.
 * 
 * This class is used internally by the C++ wrapper to interact with the
 * Screeps JavaScript API. All game objects (Creep, Room, Structure, etc.)
 * derive from this class.
 * 
 * @see RoomObject, RoomPosition, GameObject
 */
class Object
{
public:
	/**
	 * @typedef Error
	 * @brief Type alias for error codes.
	 * 
	 * Error codes are integers that represent various error conditions
	 * that can occur when performing game operations. These correspond to
	 * the Screeps JavaScript API error constants (OK, ERR_NOT_OWNER, etc.).
	 */
	using Error = int;

	/**
	 * @brief Get a reference to the underlying JavaScript value.
	 * @return JS::Value& Reference to the stored JavaScript value.
	 */
	JS::Value& value();

	/**
	 * @brief Get a const reference to the underlying JavaScript value.
	 * @return const JS::Value& Const reference to the stored JavaScript value.
	 */
	const JS::Value& value() const;

	/**
	 * @brief Set the underlying JavaScript value.
	 * @param value The new JavaScript value to store.
	 */
	void setValue(JS::Value value);

	/**
	 * @brief Conversion operator to JS::Value reference.
	 * @return JS::Value& Reference to the stored JavaScript value.
	 */
	operator JS::Value&();

	/**
	 * @brief Const conversion operator to JS::Value reference.
	 * @return const JS::Value& Const reference to the stored JavaScript value.
	 */
	operator const JS::Value&() const;

protected:
	/**
	 * @brief Default constructor.
	 * 
	 * Creates an Object with a default-constructed JavaScript value.
	 * This is typically used by derived classes that initialize their
	 * own JavaScript values.
	 */
	Object();

	/**
	 * @brief Construct an Object from a JavaScript value.
	 * @param value The JavaScript value to wrap.
	 */
	explicit Object(JS::Value value);

	/**
	 * @brief Destructor.
	 * 
	 * Virtual destructor to ensure proper cleanup of derived classes.
	 */
	~Object();

private:
	/**
	 * @brief The stored JavaScript value.
	 * 
	 * This member holds the JavaScript value that this object wraps.
	 * All operations on the C++ object ultimately interact with this value.
	 */
	JS::Value value_;
};

} // namespace Screeps

#endif // SCREEPS_OBJECT_HPP
