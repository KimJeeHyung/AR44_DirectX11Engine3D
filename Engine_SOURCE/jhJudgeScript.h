#pragma once
#include "jhScript.h"

namespace jh
{
	class JudgeScript : public Script
	{
	public:
		JudgeScript();
		~JudgeScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		//virtual void OnCollisionEnter(Collider2D* collider) override;
		//virtual void OnCollisionStay(Collider2D* collider) override;
		//virtual void OnCollisionExit(Collider2D* collider) override;

	public:
		void AnimIdle();
		void AnimIdleTalk();
		void AnimNod();
		void AnimShake();
		void AnimSurprisedIdle();
		void AnimSurprisedIdleTalk();
		void AnimSternIdle();
		void AnimSternIdleTalk();
		void AnimThink();

	private:
		void bindEvent();

		void returnIdle();
		void blink();

	private:
		class Animator* mAnimator;
	};
}
