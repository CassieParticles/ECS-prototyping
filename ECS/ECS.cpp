#include "ECS.h"

#include "Entity.h"

FullCompRegistry ECS::registry = FullCompRegistry();
EntityId ECS::nextFreeId = 0;

ECS::ECS()
{
}

Entity ECS::createEntity(const std::string& name)
{
	return Entity(nextFreeId++,name);
}


