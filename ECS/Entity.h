#pragma once
#include <string>

#include "ECS.h"

class Entity final
{
public:
	template<Component C,typename... Args>
	C* addComponent(Args... args);

	template<Component C>
	bool hasComponent();

	template<Component C>
	C* getComponent();

	template<Component C>
	void removeComponent();

	EntityId getEntityId() { return entityId; }
private:
	Entity(EntityId entityId, const std::string& name) :entityId{ entityId }
	{
		//Add default components
		ECS::getRegistry()->addComponent<TransformComponent>(entityId);
		ECS::getRegistry()->addComponent<TagComponent>(entityId, name);
	}

	//
	Entity(EntityId entityId) :entityId{ entityId }
	{

	}

	EntityId entityId;

	friend class BaseComponent;
	friend class ECS;
	friend class ComponentRegistryFull;
};

template<Component C, typename ...Args>
inline C* Entity::addComponent(Args... args)
{
	return ECS::getRegistry()->addComponent<C>(entityId,std::forward<Args>(args)...);
}

template<Component C>
inline bool Entity::hasComponent()
{
	return ECS::getRegistry()->hasComponent<C>(entityId);
}

template<Component C>
inline C* Entity::getComponent()
{
	return ECS::getRegistry()->getComponent<C>(entityId);
}

template<Component C>
inline void Entity::removeComponent()
{
	ECS::getRegistry()->removeComponent<C>(entityId);
}

