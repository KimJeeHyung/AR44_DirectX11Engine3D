#pragma once
#include "jhScript.h"
#include "jhCamera.h"

namespace jh
{
	class FadeScript : public Script
	{
	public:
		FadeScript();
		virtual ~FadeScript();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetCamera(Camera* camera) { mCamera = camera; }
		void SetFadeTime(float time) { mFadeTime = time; }

		void SetFadeComplete(bool complete) { mbFadeComplete = complete; }
		bool GetFadeComplete() { return mbFadeComplete; }

		void FadeIn();
		void FadeOut();

	private:
		Camera* mCamera;
		bool mIsFadeOut;
		float mDeltaTime;
		float mFadeTime;
		bool mbFadeStart;
		bool mbFadeComplete;
	};
}
