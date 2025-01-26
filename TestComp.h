#pragma once

#include "ECS/Component.h"

class TestComp : public BaseComponent
{
public:
	TestComp(float number) {}
	~TestComp() { std::cout << "Test comp OUT!\n"; }
};