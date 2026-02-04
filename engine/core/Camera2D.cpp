#include "Camera2D.h"

Camera2D::Camera2D() : position(0.0f, 0.0f)
{
    reset();
}

void Camera2D::reset()
{
    position = Vector2(0.0f, 0.0f);
    zoom = 1.0f;
}

void Camera2D::setPosition(const Vector2 &pos)
{
    position = pos;
}

const Vector2 &Camera2D::getPosition() const
{
    return position;
}

void Camera2D::setZoom(float z)
{
    if (z <= 0.0f)
        return;

    zoom = z;
}

float Camera2D::getZoom() const
{
    return zoom;
}