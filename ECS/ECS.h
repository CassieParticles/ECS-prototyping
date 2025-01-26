#pragma once

#include "ComponentRegistryFull.h"
#include "Component.h"

class Entity;

class ECS final
{
public:
	ECS();

	static FullCompRegistry* getRegistry() { return &registry; }

	static Entity createEntity(const std::string& name = "Entity");

	static Entity getEntityByName(const std::string& name);

private:
	static FullCompRegistry registry;

	static EntityId nextFreeId;
};