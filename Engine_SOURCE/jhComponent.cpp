#include "jhComponent.h"

namespace jh
{
	Component::Component(eComponentType type) :
		mType(type),
		mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}
}
