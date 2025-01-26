#pragma once

#include "ECS/ECS.h"
#include "ECS/Entity.h"

class TestCompB : public BaseComponent
{
public:
	void OnComponentAdded() override
	{
		std::cout << "Added component B\n";
	}

	void OnComponentRemoved() override
	{
		std::cout << "Removed component B\n";
	}
};

class TestCompA : public BaseComponent
{
public:
	void OnComponentAdded() override
	{
		Entity entity = getEntity();
		entity.addComponent<TestCompB>();
	}
};

