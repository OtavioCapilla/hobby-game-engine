#pragma once

#include <engine/ecs/Entity.h>
#include <engine/ecs/EntityManager.h>
#include <engine/ecs/ComponentStorage.h>

#include <engine/ecs/components/Transform.h>
#include <engine/ecs/components/Velocity.h>
#include <engine/ecs/components/Sprite.h>
#include <engine/ecs/components/Collider.h>
#include <engine/ecs/components/CameraTarget.h>
#include <engine/ecs/components/CameraOffset.h>
#include <engine/ecs/components/InputIntent.h>

class World
{
public:
    // ===== ENTITIES =====
    EntityID createEntity()
    {
        return entities.create();
    }

    void destroyEntity(EntityID id)
    {
        entities.destroy(id);
        transforms.remove(id);
        velocities.remove(id);
        sprites.remove(id);
        colliders.remove(id);
        cameraTargets.remove(id);
        cameraOffsets.remove(id);
        inputIntents.remove(id);
    }

    // ===== COMPONENT API =====
    template <typename T>
    void add(EntityID entity, const T &component)
    {
        getStorage<T>().add(entity, component);
    }

    template <typename T>
    bool has(EntityID entity) const
    {
        return getStorage<T>().has(entity);
    }

    template <typename T>
    T &get(EntityID entity)
    {
        return getStorage<T>().get(entity);
    }

    // ===== STORAGES (EXPLICIT) =====
    ComponentStorage<Transform> transforms;
    ComponentStorage<Velocity> velocities;
    ComponentStorage<Sprite> sprites;
    ComponentStorage<Collider> colliders;
    ComponentStorage<CameraTarget> cameraTargets;
    ComponentStorage<CameraOffset> cameraOffsets;
    ComponentStorage<InputIntent> inputIntents;

private:
    EntityManager entities;

    // ===== STORAGE RESOLUTION =====
    template <typename T>
    ComponentStorage<T> &getStorage();

    template <typename T>
    const ComponentStorage<T> &getStorage() const;
};

// ===== TEMPLATE SPECIALIZATIONS =====

template <>
inline ComponentStorage<Transform> &
World::getStorage<Transform>() { return transforms; }

template <>
inline ComponentStorage<Velocity> &
World::getStorage<Velocity>() { return velocities; }

template <>
inline ComponentStorage<Sprite> &
World::getStorage<Sprite>() { return sprites; }

template <>
inline ComponentStorage<Collider> &
World::getStorage<Collider>() { return colliders; }

template <>
inline ComponentStorage<CameraTarget> &
World::getStorage<CameraTarget>() { return cameraTargets; }

template <>
inline ComponentStorage<CameraOffset> &
World::getStorage<CameraOffset>() { return cameraOffsets; }

template <>
inline ComponentStorage<InputIntent> &
World::getStorage<InputIntent>() { return inputIntents; }

template <>
inline const ComponentStorage<Transform> &
World::getStorage<Transform>() const { return transforms; }

template <>
inline const ComponentStorage<Velocity> &
World::getStorage<Velocity>() const { return velocities; }

template <>
inline const ComponentStorage<Sprite> &
World::getStorage<Sprite>() const { return sprites; }

template <>
inline const ComponentStorage<Collider> &
World::getStorage<Collider>() const { return colliders; }

template <>
inline const ComponentStorage<CameraTarget> &
World::getStorage<CameraTarget>() const { return cameraTargets; }

template <>
inline const ComponentStorage<CameraOffset> &
World::getStorage<CameraOffset>() const { return cameraOffsets; }

template <>
inline const ComponentStorage<InputIntent> &
World::getStorage<InputIntent>() const { return inputIntents; }