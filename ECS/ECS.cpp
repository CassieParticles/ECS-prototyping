#include "ECS.h"

#include "Entity.h"
#include "Component.h"

FullCompRegistry ECS::registry = FullCompRegistry();
EntityId ECS::nextFreeId = 0;

ECS::ECS()
{
}

Entity ECS::createEntity(const std::string& name)
{
	return Entity(nextFreeId++,name);
}

void ECS::destroyEntity(Entity entity)
{
	ECS::getRegistry()->removeEntity(entity.getEntityId());
}

Entity ECS::getEntityByName(const std::string& name)
{
	ComponentArray<TagComponent> tagArr = getRegistry()->getComponentArr<TagComponent>();

	for(int i=0;i<tagArr.getArrSize();++i)
	{
		if (tagArr.getComp(i).name == name)
		{
			return tagArr.getComp(i).getEntity();
		}
	}
	//There isn't an entity with this name, so create one
	return createEntity(name);
}


