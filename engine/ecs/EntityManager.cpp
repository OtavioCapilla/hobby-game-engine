#include "EntityManager.h"

EntityManager::EntityManager()
    : nextId(1)
{
}

EntityID EntityManager::create()
{
    return nextId++;
}

void EntityManager::destroy(EntityID id)
{
    // In a more complete implementation, you might want to recycle IDs
    // or manage a pool of free IDs. For now, this is a no-op.
}