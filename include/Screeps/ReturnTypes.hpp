#ifndef SCREEPS_RETURN_TYPES_HPP
#define SCREEPS_RETURN_TYPES_HPP

#include "Screeps/Object.hpp"

namespace Screeps {

// Return value for found paths
struct PathStep
{
public:
	int x;
	int y;
	int dx;
	int dy;
	int direction; // See Constants.hpp

	PathStep(int x, int y, int dx, int dy, int dir) : x(x), y(y), dx(dx), dy(dy), direction(dir) {}
};

} // namespace Screeps

#endif // SCREEPS_RETURN_TYPES_HPP
