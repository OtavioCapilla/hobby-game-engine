#pragma once

#include "Entity.h"

class EntityManager
{
public:
    EntityManager();

    EntityID create();
    void destroy(EntityID id);

    void clear();

private:
    EntityID nextId;
};