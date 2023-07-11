#pragma once
#include "jhScript.h"

namespace jh
{
	class PhoenixScript : public Script
	{
	public:
		PhoenixScript();
		~PhoenixScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	public:
		void AnimIdle();
		void AnimIdleTalk();
		void AnimIdleNod();
		void AnimIdleShake();
		void AnimThink();
		void AnimThinkTalk();
		void AnimDeskHit();
		void AnimDeskTalk();
		void AnimPoint();
		void AnimPointTalk();
		void AnimDocument();
		void AnimDocumentTalk();
		void AnimSweat();
		void AnimSweatTalk();
		void AnimConfident();
		void AnimConfidentTalk();
		void AnimShocked();
		void AnimAbashed();
		void AnimAbashedTalk();
		void AnimWig();

	private:
		void bindEvent();

		void start();
		void end();
		void returnIdle();
		void blink();
		void think();

	private:
		class Animator* mAnimator;
	};
}
