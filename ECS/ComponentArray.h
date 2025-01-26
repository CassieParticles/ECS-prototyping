#pragma once

#include <iterator>
#include <cassert>

#include "ComponentConcept.h"

template<Component C>
class ComponentArray final
{
public:
	ComponentArray(C* compArray, int arraySize);
	~ComponentArray() {}

	C& getComp(int index);
	int getArrSize() { return arraySize; }
private:
	C* compArray;
	int arraySize;
	
};

template<Component C>
inline ComponentArray<C>::ComponentArray(C* compArray, int arraySize) :compArray{ compArray },arraySize{arraySize}
{
}

template<Component C>
inline C& ComponentArray<C>::getComp(int index)
{
	assert("Index is out of bounds: ",index > 0 && index < arraySize);
	return compArray[index];
}