#include "Component.h"

#include "Entity.h"

Entity BaseComponent::getEntity()
{
	return Entity(entityId);
}
