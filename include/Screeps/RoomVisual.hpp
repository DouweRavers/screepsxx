#ifndef SCREEPS_ROOM_VISUAL_HPP
#define SCREEPS_ROOM_VISUAL_HPP

#include "Object.hpp"
#include "RoomPosition.hpp"
#include "../nlohmann/json.hpp"
#include <string>
#include <vector>

namespace Screeps {

class RoomVisual : public Object
{
public:
    explicit RoomVisual(JS::Value value);

    // --- Single Shape Methods ---
    RoomVisual& line(int x1, int y1, int x2, int y2, const JSON& style = {}) const;
    RoomVisual& circle(int x, int y, const JSON& style = {}) const;
    RoomVisual& rect(int x, int y, int width, int height, const JSON& style = {}) const;
    RoomVisual& poly(const std::vector<RoomPosition>& points, const JSON& style = {}) const;
    RoomVisual& text(const std::string& text, int x, int y, const JSON& style = {}) const;

    // --- Multi-Shape Methods ---
    RoomVisual& mline(const std::vector<std::vector<int>>& points, const JSON& style = {}) const;
    RoomVisual& mcircle(const std::vector<std::pair<int, int>>& points, const JSON& style = {}) const;
    RoomVisual& mrect(const std::vector<std::vector<int>>& rects, const JSON& style = {}) const;
    RoomVisual& mpoly(const std::vector<std::vector<RoomPosition>>& polys, const JSON& style = {}) const;
    RoomVisual& mtext(const std::vector<std::tuple<std::string, int, int>>& texts, const JSON& style = {}) const;

    // --- Utility ---
    RoomVisual& clear() const;
};

} // namespace Screeps

#endif // SCREEPS_ROOM_VISUAL_HPP