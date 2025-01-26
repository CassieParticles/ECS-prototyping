#include <iostream>
#include <vector>
#include <unordered_map>
//
#include "ECS/ECS.h"
#include "ECS/Entity.h"



int main()
{
	Entity entityA = ECS::createEntity("Entity A");
	Entity entityB = ECS::createEntity("Entity B");

	std::cout << entityA.getComponent<TagComponent>()->name << '\n';
	std::cout << entityA.hasComponent<TagComponent>() << '\n';
	entityA.removeComponent<TagComponent>();
	std::cout << entityA.hasComponent<TagComponent>() << '\n';
	std::cout << entityB.getComponent<TagComponent>()->name << '\n';

	

	return 0;
}

