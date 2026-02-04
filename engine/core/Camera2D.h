#pragma once

#include <engine/math/Vector2.h>

class Camera2D
{
public:
    Camera2D();

    void setPosition(const Vector2 &pos);
    const Vector2 &getPosition() const;

    void setZoom(float zoom);
    float getZoom() const;

    void reset();

private:
    Vector2 position;
    float zoom;
};