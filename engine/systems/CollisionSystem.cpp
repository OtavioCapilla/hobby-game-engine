#include "CollisionSystem.h"
#include <iostream>

bool CollisionSystem::checkAABB(const GameObject& a,
                                const GameObject& b)
{
    return (
        a.transform.position.x < b.transform.position.x + b.collider.size.x &&
        a.transform.position.x + a.collider.size.x > b.transform.position.x &&
        a.transform.position.y < b.transform.position.y + b.collider.size.y &&
        a.transform.position.y + a.collider.size.y > b.transform.position.y
    );
}

void CollisionSystem::resolveX(GameObject& mover,
                               const GameObject& other)
{
    if (mover.velocity.x > 0.0f) {
        mover.transform.position.x =
            other.transform.position.x - mover.collider.size.x;
    }
    else if (mover.velocity.x < 0.0f) {
        mover.transform.position.x =
            other.transform.position.x + other.collider.size.x;
    }

    mover.velocity.x = 0.0f;
}

void CollisionSystem::resolveY(GameObject& mover,
                               const GameObject& other)
{
    if (mover.velocity.y > 0.0f) {
        mover.transform.position.y =
            other.transform.position.y - mover.collider.size.y;
    }
    else if (mover.velocity.y < 0.0f) {
        mover.transform.position.y =
            other.transform.position.y + other.collider.size.y;
    }

    mover.velocity.y = 0.0f;
}