#include "RoomVisual.hpp"
#include "JS.hpp"
#include "JSON.hpp"

namespace Screeps {

RoomVisual::RoomVisual(JS::Value value) : Object(std::move(value)) {}

// --- Single Shape Methods ---
RoomVisual& RoomVisual::line(int x1, int y1, int x2, int y2, const JSON& style) const {
    value().call<void>("line", x1, y1, x2, y2, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::circle(int x, int y, const JSON& style) const {
    value().call<void>("circle", x, y, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::rect(int x, int y, int width, int height, const JSON& style) const {
    value().call<void>("rect", x, y, width, height, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::poly(const std::vector<RoomPosition>& points, const JSON& style) const {
    JS::Value jsPoints = JS::Value::array();
    for (size_t i = 0; i < points.size(); ++i) {
        jsPoints.set(i, points[i].value());
    }
    value().call<void>("poly", jsPoints, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::text(const std::string& text, int x, int y, const JSON& style) const {
    value().call<void>("text", text, x, y, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

// --- Multi-Shape Methods ---
RoomVisual& RoomVisual::mline(const std::vector<std::vector<int>>& points, const JSON& style) const {
    JS::Value jsPoints = JS::Value::array();
    for (size_t i = 0; i < points.size(); ++i) {
        JS::Value point = JS::Value::array();
        point.set(0, points[i][0]);
        point.set(1, points[i][1]);
        point.set(2, points[i][2]);
        point.set(3, points[i][3]);
        jsPoints.set(i, point);
    }
    value().call<void>("mline", jsPoints, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::mcircle(const std::vector<std::pair<int, int>>& points, const JSON& style) const {
    JS::Value jsPoints = JS::Value::array();
    for (size_t i = 0; i < points.size(); ++i) {
        JS::Value point = JS::Value::array();
        point.set(0, points[i].first);
        point.set(1, points[i].second);
        jsPoints.set(i, point);
    }
    value().call<void>("mcircle", jsPoints, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::mrect(const std::vector<std::vector<int>>& rects, const JSON& style) const {
    JS::Value jsRects = JS::Value::array();
    for (size_t i = 0; i < rects.size(); ++i) {
        JS::Value rect = JS::Value::array();
        rect.set(0, rects[i][0]);
        rect.set(1, rects[i][1]);
        rect.set(2, rects[i][2]);
        rect.set(3, rects[i][3]);
        jsRects.set(i, rect);
    }
    value().call<void>("mrect", jsRects, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::mpoly(const std::vector<std::vector<RoomPosition>>& polys, const JSON& style) const {
    JS::Value jsPolys = JS::Value::array();
    for (size_t i = 0; i < polys.size(); ++i) {
        JS::Value poly = JS::Value::array();
        for (size_t j = 0; j < polys[i].size(); ++j) {
            poly.set(j, polys[i][j].value());
        }
        jsPolys.set(i, poly);
    }
    value().call<void>("mpoly", jsPolys, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

RoomVisual& RoomVisual::mtext(const std::vector<std::tuple<std::string, int, int>>& texts, const JSON& style) const {
    JS::Value jsTexts = JS::Value::array();
    for (size_t i = 0; i < texts.size(); ++i) {
        JS::Value text = JS::Value::array();
        text.set(0, std::get<0>(texts[i]));
        text.set(1, std::get<1>(texts[i]));
        text.set(2, std::get<2>(texts[i]));
        jsTexts.set(i, text);
    }
    value().call<void>("mtext", jsTexts, JS::fromJSON(style));
    return const_cast<RoomVisual&>(*this);
}

// --- Utility ---
RoomVisual& RoomVisual::clear() const {
    value().call<void>("clear");
    return const_cast<RoomVisual&>(*this);
}

} // namespace Screeps