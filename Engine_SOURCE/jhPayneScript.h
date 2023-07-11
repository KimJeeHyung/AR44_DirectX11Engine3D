#pragma once
#include "jhScript.h"

namespace jh
{
	class PayneScript : public Script
	{
	public:
		PayneScript();
		~PayneScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		//virtual void OnCollisionEnter(Collider2D* collider) override;
		//virtual void OnCollisionStay(Collider2D* collider) override;
		//virtual void OnCollisionExit(Collider2D* collider) override;

	public:
		void AnimIdle();
		void AnimIdleTalk();
		void AnimSweat();
		void AnimSweatTalk();

	private:
		void bindEvent();

		void returnIdle();
		void blink();

	private:
		class Animator* mAnimator;
	};
}
