/**
 * @file RoomVisual.hpp
 * @brief RoomVisual class definition for Screeps game API wrapper.
 * @see https://docs.screeps.com/api/#RoomVisual
 */
#ifndef SCREEPS_ROOM_VISUAL_HPP
#define SCREEPS_ROOM_VISUAL_HPP

#include "Object.hpp"
#include "RoomPosition.hpp"
#include "../nlohmann/json.hpp"
#include <string>
#include <vector>

namespace Screeps {

/**
 * @class RoomVisual
 * @brief Allows drawing simple shapes and text in a room for visualization.
 *
 * RoomVisual provides methods to draw various shapes and text on the game map
 * for debugging and visualization purposes. These visualizations are only visible
 * to the player who created them.
 *
 * @see https://docs.screeps.com/api/#RoomVisual
 * @see Object
 */
class RoomVisual : public Object
{
public:
    /**
     * @brief Construct a RoomVisual from a JavaScript value.
     * @param value The JavaScript value representing the room visual.
     */
    explicit RoomVisual(JS::Value value);

    // --- Single Shape Methods ---

    /**
     * @brief Draw a line between two points.
     * @param x1 The x coordinate of the start point.
     * @param y1 The y coordinate of the start point.
     * @param x2 The x coordinate of the end point.
     * @param y2 The y coordinate of the end point.
     * @param style Style options for the line (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.line
     */
    RoomVisual& line(int x1, int y1, int x2, int y2, const JSON& style = {}) const;

    /**
     * @brief Draw a circle at a position.
     * @param x The x coordinate of the center.
     * @param y The y coordinate of the center.
     * @param style Style options for the circle (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.circle
     */
    RoomVisual& circle(int x, int y, const JSON& style = {}) const;

    /**
     * @brief Draw a rectangle at a position.
     * @param x The x coordinate of the top-left corner.
     * @param y The y coordinate of the top-left corner.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param style Style options for the rectangle (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.rect
     */
    RoomVisual& rect(int x, int y, int width, int height, const JSON& style = {}) const;

    /**
     * @brief Draw a polygon from a series of points.
     * @param points Vector of RoomPositions defining the polygon vertices.
     * @param style Style options for the polygon (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.poly
     */
    RoomVisual& poly(const std::vector<RoomPosition>& points, const JSON& style = {}) const;

    /**
     * @brief Draw text at a position.
     * @param text The text to draw.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param style Style options for the text (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.text
     */
    RoomVisual& text(const std::string& text, int x, int y, const JSON& style = {}) const;

    // --- Multi-Shape Methods ---

    /**
     * @brief Draw multiple lines at once.
     * @param points Vector of line definitions (each as [x1, y1, x2, y2]).
     * @param style Style options for the lines (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.mline
     */
    RoomVisual& mline(const std::vector<std::vector<int>>& points, const JSON& style = {}) const;

    /**
     * @brief Draw multiple circles at once.
     * @param points Vector of circle definitions (each as (x, y) pairs).
     * @param style Style options for the circles (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.mcircle
     */
    RoomVisual& mcircle(const std::vector<std::pair<int, int>>& points, const JSON& style = {}) const;

    /**
     * @brief Draw multiple rectangles at once.
     * @param rects Vector of rectangle definitions (each as [x, y, width, height]).
     * @param style Style options for the rectangles (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.mrect
     */
    RoomVisual& mrect(const std::vector<std::vector<int>>& rects, const JSON& style = {}) const;

    /**
     * @brief Draw multiple polygons at once.
     * @param polys Vector of polygon definitions (each as vector of RoomPositions).
     * @param style Style options for the polygons (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.mpoly
     */
    RoomVisual& mpoly(const std::vector<std::vector<RoomPosition>>& polys, const JSON& style = {}) const;

    /**
     * @brief Draw multiple text strings at once.
     * @param texts Vector of text definitions (each as tuple of text, x, y).
     * @param style Style options for the text (optional).
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.mtext
     */
    RoomVisual& mtext(const std::vector<std::tuple<std::string, int, int>>& texts, const JSON& style = {}) const;

    // --- Utility ---

    /**
     * @brief Clear all visualizations from this room.
     * @return Reference to this RoomVisual for chaining.
     * @see https://docs.screeps.com/api/#RoomVisual.clear
     */
    RoomVisual& clear() const;
};

} // namespace Screeps

#endif // SCREEPS_ROOM_VISUAL_HPP