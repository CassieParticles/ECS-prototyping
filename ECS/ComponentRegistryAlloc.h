#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <new>

#include "ComponentArray.h"
#include "ComponentConcept.h"

typedef uint32_t EntityId;

class ICompRegistry
{
public:
	virtual void RemoveComponent(EntityId entityId) = 0;
};

template<Component C>
class CompRegistryAlloc final: public ICompRegistry
{
public:
	CompRegistryAlloc();
	~CompRegistryAlloc();

	template<typename... Args>
	C* EmplaceComponent(EntityId entId, Args&&... args);
	bool HasComponent(EntityId entId);
	C* GetComponent(EntityId entId);
	void RemoveComponent(EntityId entId);

	ComponentArray<C> GetComponentArr();

private:
	std::vector<char> compByteArray;
	unsigned int firstIndexFree = 0;
	void resizeArray();

	std::unordered_map<EntityId, unsigned int> entIndexMap;	//Get index component held by Entity is stored at, updates when components are moved
	std::unordered_map<unsigned int, EntityId> indexEntMap; //Get the entity a component belongs to from it's index in array, updates when components are moved
};

template<Component C>
inline CompRegistryAlloc<C>::CompRegistryAlloc()
{
	compByteArray.resize(sizeof(C) * 256);	//Reserve 256 components worth of space
}

template<Component C>
inline CompRegistryAlloc<C>::~CompRegistryAlloc()
{
}

template<Component C>
template<typename ...Args>
inline C* CompRegistryAlloc<C>::EmplaceComponent(EntityId entId, Args && ...args)
{
	//Return existing component if one already exists
	if (C* comp = GetComponent(entId)) { return comp; }

	//Create the component
	int firstByteFree = firstIndexFree * sizeof(C);
	C* comp = new(compByteArray.data() + firstByteFree)
		C(std::forward<Args>(args)...);

	//Add mappings in entIndexMap and indexEntMap
	entIndexMap.insert({ entId,firstIndexFree });
	indexEntMap.insert({ firstIndexFree,entId });

	firstIndexFree++;
	return comp;
}



template<Component C>
inline bool CompRegistryAlloc<C>::HasComponent(EntityId entId)
{
	return entIndexMap.contains(entId);
}

template<Component C>
inline C* CompRegistryAlloc<C>::GetComponent(EntityId entId)
{
	if (!HasComponent(entId)) { return nullptr; }
	
	char* compBytePtr = compByteArray.data() + entIndexMap.at(entId) * sizeof(C);
	return reinterpret_cast<C*>(compBytePtr);
}

template<Component C>
inline void CompRegistryAlloc<C>::RemoveComponent(EntityId entId)
{
	if (!HasComponent(entId)) { return; }

	//Get the pointer of the component to be removed and call component destructor
	unsigned int compRemoveIndex = entIndexMap.at(entId);
	char* compRemoveByte = compByteArray.data() + compRemoveIndex * sizeof(C);
	C* compRemove = reinterpret_cast<C*>(compRemoveByte);
	compRemove->OnComponentRemoved();
	compRemove->~C();

	//Get pointer to last component in array, and move it to compRemove
	char* compLastByte = compByteArray.data() + (firstIndexFree - 1) * sizeof(C);
	std::copy(compLastByte, compLastByte + sizeof(C), compRemoveByte);
	
	//Update entity/index maps to reflect moved/destroyed component
	EntityId lastCompEntity = indexEntMap.at(firstIndexFree - 1);

	entIndexMap.erase(entId);
	indexEntMap.erase(firstIndexFree - 1);

	//Do not move indices if component being destroyed is the last component in vector
	if (compRemoveIndex != firstIndexFree - 1)
	{
		//Last component moved to comRemoveIndex, update entId-Index map to reflect this
		entIndexMap.at(lastCompEntity) = compRemoveIndex;

		//Index of removed component now has component of last entity, update index-entId map to reflect this
		indexEntMap.at(compRemoveIndex) = lastCompEntity;
	}

	--firstIndexFree;
}

template<Component C>
inline ComponentArray<C> CompRegistryAlloc<C>::GetComponentArr()
{
	return ComponentArray(reinterpret_cast<C*>(compByteArray.data()), firstIndexFree);

}

template<Component C>
inline void CompRegistryAlloc<C>::resizeArray()
{
	compByteArray.resize(compByteArray.size * 2);
}
