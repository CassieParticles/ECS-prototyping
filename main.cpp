#include <iostream>
#include <vector>
#include <unordered_map>

#include "ECS/ECS.h"
#include "ECS/Entity.h"

#include "TestComp.h"



int main()
{
	Entity entityA = ECS::createEntity("Entity A");
	Entity entityB = ECS::createEntity("Entity B");
	Entity entityC = ECS::createEntity("Entity C");
	Entity entityD = ECS::createEntity("Entity D");

	entityB.addComponent<TestComp>(3.14159f);

	std::cout<<ECS::getRegistry()->getComponentArr<TestComp>(nullptr)->getEntity().getComponent<TagComponent>()->name<<'\n';

	return 0;
}

