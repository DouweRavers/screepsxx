/**
 * @file Context.hpp
 * @brief Context class definition for Screeps game API wrapper.
 *
 * This file provides the Context singleton that manages the global game objects
 * and their connection to JavaScript.
 */
#ifndef SCREEPS_CONTEXT_HPP
#define SCREEPS_CONTEXT_HPP

#include "Game.hpp"
#include "Memory.hpp"
#include "PathFinder.hpp"
#include "RawMemory.hpp"

namespace Screeps {

/**
 * @class Context
 * @brief Singleton class that manages global game context and JavaScript bindings.
 *
 * The Context class provides a centralized way to access and update the global
 * game objects (Game, Memory, RawMemory, PathFinder). It uses the singleton
 * pattern to ensure there's only one instance.
 */
class Context
{
public:
	/**
	 * @brief Get the singleton Context instance.
	 * @return Reference to the Context instance.
	 */
	static Context& getInstance()
	{
		static Context context;
		return context;
	}

	/**
	 * @brief Update all global objects with their JavaScript counterparts.
	 *
	 * This method should be called at the beginning of each game tick to
	 * synchronize the C++ objects with the current JavaScript state.
	 */
	static void update()
	{
		Game.setValue(JS::getGlobal("Game"));
		Memory.setValue(JS::getGlobal("Memory"));
		RawMemory.setValue(JS::getGlobal("RawMemory"));
		PathFinder.setValue(JS::getGlobal("PathFinder"));
	}

private:
	/** @brief Private constructor to enforce singleton pattern. */
	Context() = default;
};

} // namespace Screeps

#endif // SCREEPS_CONTEXT_HPP
