#pragma once
#include "jhScript.h"

namespace jh
{
	class LarryScript : public Script
	{
	public:
		LarryScript();
		~LarryScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		//virtual void OnCollisionEnter(Collider2D* collider) override;
		//virtual void OnCollisionStay(Collider2D* collider) override;
		//virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		void bindEvent();

		void returnIdle();
		void blink();

	private:
		class Animator* mAnimator;
	};
}
