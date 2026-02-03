#pragma once

#include <cmath>

struct Vector2
{
    float x{0.0f};
    float y{0.0f};

    Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &other) const
    {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2 &other) const
    {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(float scalar) const
    {
        return {x * scalar, y * scalar};
    }

    Vector2 &operator+=(const Vector2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2 normalized() const
    {
        float len = length();
        if (len == 0.0f)
        {
            return {0.0f, 0.0f};
        }
        return {x / len, y / len};
    }
};
