/**
 * @file PathFinder.hpp
 * @brief PathFinder class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#PathFinder
 */
#ifndef SCREEPS_PATH_FINDER_HPP
#define SCREEPS_PATH_FINDER_HPP

#include "Object.hpp"

namespace Screeps {

/**
 * @class PathFinderObject
 * @brief Provides pathfinding utilities.
 *
 * PathFinder is a global object that provides advanced pathfinding capabilities
 * for finding paths between positions while considering terrain costs and
 * obstacle avoidance.
 *
 * @see https://docs.screeps.com/api/#PathFinder
 * @see Object
 */
class PathFinderObject : public Object
{
public:
	/**
	 * @brief Construct a PathFinderObject.
	 */
	PathFinderObject();
};

/** Global PathFinder object instance. */
extern PathFinderObject PathFinder;

} // namespace Screeps

#endif // SCREEPS_PATH_FINDER_HPP
