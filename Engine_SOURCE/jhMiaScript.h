#pragma once
#include "jhScript.h"

namespace jh
{
	class MiaScript : public Script
	{
	public:
		MiaScript();
		~MiaScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		//virtual void OnCollisionEnter(Collider2D* collider) override;
		//virtual void OnCollisionStay(Collider2D* collider) override;
		//virtual void OnCollisionExit(Collider2D* collider) override;

	public:
		void AnimFowardIdle();
		void AnimFowardIdleTalk();
		void AnimFowardGrin();
		void AnimFowardSmileIdle();
		void AnimFowardSmileIdleTalk();
		void AnimFowardShock();
		void AnimFowardShockTalk();

		void AnimCounselIdle();
		void AnimCounselIdleTalk();
		void AnimCounselShock();
		void AnimCounselShockTalk();
		void AnimCounselSad();
		void AnimCounselSadTalk();
		void AnimCounselExasperate();
		void AnimCounselExasperateTalk();

	private:
		void bindEvent();

		void returnIdle();
		void blink();

	private:
		class Animator* mAnimator;
	};
}
