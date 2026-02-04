#pragma once

#include "Entity.h"

class EntityManager
{
public:
    EntityManager();

    EntityID create();
    void destroy(EntityID id);

private:
    EntityID nextId;
};