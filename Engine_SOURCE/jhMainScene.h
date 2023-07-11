#pragma once
#include "jhScene.h"

namespace jh
{
	class MainScene : public Scene
	{
	public:
		MainScene();
		virtual ~MainScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
