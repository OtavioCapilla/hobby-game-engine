#pragma once

#include <engine/math/Vector2.h>

class Camera2D
{
public:
    Camera2D();

    void setPosition(const Vector2 &pos);
    const Vector2 &getPosition() const;

private:
    Vector2 position;
};