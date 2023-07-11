#pragma once
#include "jhScene.h"

namespace jh
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
