#include "Camera2D.h"

Camera2D::Camera2D() : position(0.0f, 0.0f) {}

void Camera2D::setPosition(const Vector2 &pos)
{
    position = pos;
}

const Vector2 &Camera2D::getPosition() const
{
    return position;
}