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
    // No need to do anything for now
}