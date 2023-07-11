#pragma once
#include "jhGameObject.h"

namespace jh
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;

	private:
	};
}
