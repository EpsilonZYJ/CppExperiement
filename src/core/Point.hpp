#pragma once

namespace adas{

    class Point final {
    public:
        Point(const int x, const int y) noexcept;

        Point(const Point& rhs) noexcept;
        Point& operator=(const Point& rhs) noexcept;

        Point& operator+=(const Point& rhs) noexcept;
        Point& operator-=(const Point& rhs) noexcept;

    public:
        int GetX(void) const noexcept;
        int GetY(void) const noexcept;

    private:
        int x;
        int y;
    };
}