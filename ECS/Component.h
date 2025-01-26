#pragma once

#include "ComponentRegistryFull.h"

#include <string>

class Entity;


class BaseComponent
{
public:
	EntityId getEntityId() { return entityId; }
	Entity getEntity();	//Needs to be defined in separate translation unit
	virtual ~BaseComponent() {}

	virtual void OnComponentAdded() {}
	virtual void OnComponentRemoved() {}
	
protected:
	EntityId entityId{};

	friend class FullCompRegistry;
};

class TransformComponent final: public BaseComponent
{
public:
	TransformComponent(float position = 0, float rotation = 0) :position{ position }, rotation{ rotation } {}
	float position;
	float rotation;
private:
};

class TagComponent final : public BaseComponent
{
public:
	TagComponent(const std::string& name = "") :name{name} {}

	std::string name;
private:
};