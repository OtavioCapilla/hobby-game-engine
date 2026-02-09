#pragma once

#include <unordered_map>
#include <engine/ecs/Entity.h>

template <typename T>
class ComponentStorage
{
public:
    void add(EntityID entity, const T &component)
    {
        components[entity] = component;
    }

    bool has(EntityID entity) const
    {
        return components.find(entity) != components.end();
    }

    T &get(EntityID entity)
    {
        return components.at(entity);
    }

    const T &get(EntityID entity) const
    {
        return components.at(entity);
    }

    void remove(EntityID entity)
    {
        components.erase(entity);
    }

    void clear()
    {
        components.clear();
    }

    auto begin() { return components.begin(); }
    auto end()   { return components.end(); }

    auto begin() const { return components.begin(); }
    auto end()   const { return components.end(); }

    size_t size() const
    {
        return components.size();
    }

private:
    std::unordered_map<EntityID, T> components;
};