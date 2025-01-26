#include <iostream>
#include <vector>
#include <unordered_map>

#include "ECS/ECS.h"
#include "ECS/Entity.h"

#include "TestComp.h"


int main()
{
	Entity entity = ECS::createEntity("Entity A");

	entity.addComponent<TestCompA>();

	std::cout<<ECS::getEntityByName("Entity A").hasComponent<TestCompB>();

	ECS::destroyEntity(entity);

	return 0;
}

