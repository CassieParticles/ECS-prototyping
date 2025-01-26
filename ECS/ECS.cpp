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

Entity ECS::getEntityByName(const std::string& name)
{
	int entCount;
	TagComponent* tagArr = getRegistry()->getComponentArr<TagComponent>(&entCount);

	for (int i = 0; i < entCount; ++i)
	{
		if (tagArr->name == name)
		{
			return tagArr->getEntity();
		}
	}
	//There isn't an entity with this name, so create one
	return createEntity(name);
}


