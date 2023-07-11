#pragma once
#include "jhScript.h"
#include "jhCamera.h"

namespace jh
{
	class GridScript : public Script
	{
	public:
		GridScript();
		virtual ~GridScript();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetCamera(Camera* camera) { mCamera = camera; }

	private:
		Camera* mCamera;
	};
}
