#include <iostream>
#include <vector>
#include <unordered_map>

#include "ECS/ECS.h"
#include "ECS/Entity.h"




int main()
{
	ECS::createEntity("Entity A").getComponent<TransformComponent>()->position = 5;
	Entity entity = ECS::getEntityByName("Entity A");
	std::cout << entity.getComponent<TransformComponent>()->position << '\n';

	ECS::destroyEntity(entity);

	return 0;
}

