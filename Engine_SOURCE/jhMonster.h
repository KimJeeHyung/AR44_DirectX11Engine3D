#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
