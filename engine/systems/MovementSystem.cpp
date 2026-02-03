#include "MovementSystem.h"

void MovementSystem::moveX(Transform& transform,
                           float velocityX,
                           float deltaTime)
{
    transform.position.x += velocityX * deltaTime;
}

void MovementSystem::moveY(Transform& transform,
                           float velocityY,
                           float deltaTime)
{
    transform.position.y += velocityY * deltaTime;
}