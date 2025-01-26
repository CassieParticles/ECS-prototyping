#pragma once
#include "ComponentRegistryAlloc.h"

#include "ComponentArray.h"

class FullCompRegistry final
{
public:
	FullCompRegistry() {}
	~FullCompRegistry() {}

	template<Component C, typename... Args>
	C* addComponent(EntityId entId, Args&&... args);
	

	template <Component C>
	bool hasComponent(EntityId entId);


	template<Component C>
	C* getComponent(EntityId entId);

	
	template<Component C>
	C* copyComponent(EntityId origEntId, EntityId copyEntId);

	template<Component C>
	void removeComponent(EntityId entId);

	template<Component C>
	ComponentArray<C> getComponentArr();

	void removeEntity(EntityId entId) 
	{
		for (auto& it : registries)
		{
			it.second->RemoveComponent(entId);
		}
	}

	void copyEntity(EntityId origEntId, EntityId newEntId)
	{
		for (auto& it : registries)
		{
			
		}
	}
	
protected:

	template<Component C>
	CompRegistryAlloc<C>* getRegistry();

	template<Component C>
	bool hasRegistry();

	//Key is hash of component typeid, 
	std::unordered_map<unsigned int, std::unique_ptr<ICompRegistry>> registries;

	friend class Entity;
};

template<Component C,typename... Args>
C* FullCompRegistry::addComponent(EntityId entId, Args&&... args)
{
	if (!hasRegistry<C>())
	{
		size_t type = typeid(C).hash_code();
		registries.insert({ type,std::unique_ptr<ICompRegistry>(new CompRegistryAlloc<C>()) });
	}


	C* component = getRegistry<C>()->EmplaceComponent(entId, std::forward<Args>(args)...);

	component->entityId = entId;
	component->OnComponentAdded();

	return component;
}

template<Component C>
bool FullCompRegistry::hasComponent(EntityId entId)
{
	if (CompRegistryAlloc<C>* registry = getRegistry<C>())
	{
		return registry->HasComponent(entId);
	}

	return false;
}

template<Component C>
C* FullCompRegistry::getComponent(EntityId entId)
{
	if (CompRegistryAlloc<C>* registry = getRegistry<C>())
	{
		return registry->GetComponent(entId);
	}
	return nullptr;
}

template<Component C>
inline C* FullCompRegistry::copyComponent(EntityId origEntId, EntityId copyEntId)
{
	if (CompRegistryAlloc<C>* registry = getRegistry<C>())
	{
		C* newComp = registry->CopyComponent(origEntId, copyEntId);
		newComp->entityId = copyEntId;
		newComp->OnComponentAdded();

		return newComp;
	}

	return nullptr;
}

template<Component C>
void FullCompRegistry::removeComponent(EntityId entId)
{
	if (CompRegistryAlloc<C>* registry = getRegistry<C>())
	{
		registry->RemoveComponent(entId);
	}
}

template<Component C>
inline ComponentArray<C> FullCompRegistry::getComponentArr()
{
	if (CompRegistryAlloc<C>* registry = getRegistry<C>())
	{
		return registry->GetComponentArr();
	}
	size_t type = typeid(C).hash_code();
	registries.insert({ type,std::unique_ptr<ICompRegistry>(new CompRegistryAlloc<C>()) });

	return getRegistry<C>()->GetComponentArr();
}


template<Component C>
CompRegistryAlloc<C>* FullCompRegistry::getRegistry()
{
	EntityId type = static_cast<EntityId>(typeid(C).hash_code());
	if (!registries.contains(type)) { return nullptr; }

	//Cast the interface registry into the desired registry (unsafe, but always works)
	return reinterpret_cast<CompRegistryAlloc<C>*>(registries.at(type).get());
}

template<Component C>
bool FullCompRegistry::hasRegistry()
{
	EntityId type = static_cast<EntityId>(typeid(C).hash_code());

	return registries.contains(type);
}