#include "CollisionSystem.h"
#include <iostream>

bool CollisionSystem::checkAABB(const Vector2 &posA, const Vector2 &sizeA,
                                const Vector2 &posB, const Vector2 &sizeB)
{
    return posA.x < posB.x + sizeB.x &&
           posA.x + sizeA.x > posB.x &&
           posA.y < posB.y + sizeB.y &&
           posA.y + sizeA.y > posB.y;
}

void CollisionSystem::resolve(World& world,
                              Tilemap& tilemap)
{
    for (auto& [entity, collider] : world.colliders) {

        if (!world.transforms.has(entity))
            continue;

        auto& transform = world.transforms.get(entity);
        {
            Vector2 pos = transform.position;

            int minX = (int)(pos.x / tilemap.getTileSize());
            int maxX = (int)((pos.x + collider.size.x) / tilemap.getTileSize());
            int minY = (int)(pos.y / tilemap.getTileSize());
            int maxY = (int)((pos.y + collider.size.y) / tilemap.getTileSize());

            for (int y = minY; y <= maxY; ++y) {
                for (int x = minX; x <= maxX; ++x) {

                    if (!tilemap.isInside(x, y))
                        continue;

                    if (tilemap.getTile("solid", x, y) == 0)
                        continue;

                    Vector2 tilePos = tilemap.tileToWorld(x, y);
                    Vector2 tileSize{
                        (float)tilemap.getTileSize(),
                        (float)tilemap.getTileSize()
                    };

                    if (checkAABB(pos, collider.size,
                                  tilePos, tileSize))
                    {
                        // empurra para fora no X
                        if (pos.x < tilePos.x)
                            transform.position.x =
                                tilePos.x - collider.size.x;
                        else
                            transform.position.x =
                                tilePos.x + tileSize.x;
                    }
                }
            }
        }

        {
            Vector2 pos = transform.position;

            int minX = (int)(pos.x / tilemap.getTileSize());
            int maxX = (int)((pos.x + collider.size.x) / tilemap.getTileSize());
            int minY = (int)(pos.y / tilemap.getTileSize());
            int maxY = (int)((pos.y + collider.size.y) / tilemap.getTileSize());

            for (int y = minY; y <= maxY; ++y) {
                for (int x = minX; x <= maxX; ++x) {

                    if (!tilemap.isInside(x, y))
                        continue;

                    if (tilemap.getTile("solid", x, y) == 0)
                        continue;

                    Vector2 tilePos = tilemap.tileToWorld(x, y);
                    Vector2 tileSize{
                        (float)tilemap.getTileSize(),
                        (float)tilemap.getTileSize()
                    };

                    if (checkAABB(pos, collider.size,
                                  tilePos, tileSize))
                    {
                        if (pos.y < tilePos.y)
                            transform.position.y =
                                tilePos.y - collider.size.y;
                        else
                            transform.position.y =
                                tilePos.y + tileSize.y;
                    }
                }
            }
        }
    }
}

