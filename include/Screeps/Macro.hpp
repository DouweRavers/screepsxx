/**
 * @file Macro.hpp
 * @brief Macro definitions for Screeps game API wrapper.
 *
 * This file contains various assertion macros used throughout the Screeps C++
 * wrapper for debugging and error checking.
 */
#ifndef SCREEPS_MACRO_HPP
#define SCREEPS_MACRO_HPP

#include <cassert>

/**
 * @def SCREEPS_ASSERT(expr)
 * @brief Assert that an expression is true.
 * @param expr The expression to assert.
 */
#define SCREEPS_ASSERT(expr) assert(expr)

/**
 * @def SCREEPS_ASSERT_MSG(expr, msg)
 * @brief Assert that an expression is true with a custom message.
 * @param expr The expression to assert.
 * @param msg The message to display if the assertion fails.
 */
#define SCREEPS_ASSERT_MSG(expr, msg) assert(expr&& msg)

/**
 * @def SCREEPS_ASSERT_FALSE(msg)
 * @brief Assert false with a message (always fails).
 * @param msg The message to display when the assertion fails.
 */
#define SCREEPS_ASSERT_FALSE(msg) SCREEPS_ASSERT_MSG(false, msg)

/**
 * @def SCREEPS_PRECONDITION(expr)
 * @brief Assert that a precondition is true.
 * @param expr The precondition expression to assert.
 */
#define SCREEPS_PRECONDITION(expr) SCREEPS_ASSERT_MSG(expr, "precondition failed")

/**
 * @def SCREEPS_POSTCONDITION(expr)
 * @brief Assert that a postcondition is true.
 * @param expr The postcondition expression to assert.
 */
#define SCREEPS_POSTCONDITION(expr) SCREEPS_ASSERT_MSG(expr, "postcondition failed")

#endif // SCREEPS_MACRO_HPP
