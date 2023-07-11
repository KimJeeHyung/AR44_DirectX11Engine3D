#include "jhPhoenixScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	PhoenixScript::PhoenixScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	PhoenixScript::~PhoenixScript()
	{
	}

	void PhoenixScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void PhoenixScript::Update()
	{
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		
		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 10.f * Time::DeltaTime();
			tr->SetRotation(rot);
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos.y -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos.y += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}*/

		if (Input::GetKey(eKeyCode::N_1))
		{
			AnimIdle();
		}
		if (Input::GetKey(eKeyCode::N_2))
		{
			AnimIdleTalk();
		}
		if (Input::GetKey(eKeyCode::N_3))
		{
			AnimIdleNod();
		}
		if (Input::GetKey(eKeyCode::N_4))
		{
			AnimIdleShake();
		}
		if (Input::GetKey(eKeyCode::N_5))
		{
			AnimThink();
		}
		if (Input::GetKey(eKeyCode::N_6))
		{
			AnimThinkTalk();
		}
		if (Input::GetKey(eKeyCode::N_7))
		{
			AnimDeskHit();
		}
		if (Input::GetKey(eKeyCode::N_8))
		{
			AnimDeskTalk();
		}
		if (Input::GetKey(eKeyCode::N_9))
		{
			AnimPoint();
		}
		if (Input::GetKey(eKeyCode::N_0))
		{
			AnimPointTalk();
		}
		if (Input::GetKey(eKeyCode::P))
		{
			AnimDocumentTalk();
		}
		if (Input::GetKey(eKeyCode::O))
		{
			AnimSweatTalk();
		}
		if (Input::GetKey(eKeyCode::I))
		{
			AnimConfident();
		}
		if (Input::GetKey(eKeyCode::U))
		{
			AnimConfidentTalk();
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			AnimShocked();
		}
		if (Input::GetKey(eKeyCode::T))
		{
			AnimAbashedTalk();
		}
		if (Input::GetKey(eKeyCode::G))
		{
			AnimWig();
		}
	}

	void PhoenixScript::Render()
	{
	}

	void PhoenixScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void PhoenixScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PhoenixScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PhoenixScript::AnimIdle()
	{
		mAnimator->Play(L"PhoenixIdle", false);
	}
	void PhoenixScript::AnimIdleTalk()
	{
		mAnimator->Play(L"PhoenixIdleTalk", false);
	}
	void PhoenixScript::AnimIdleNod()
	{
		mAnimator->Play(L"PhoenixIdleNod", true);
	}
	void PhoenixScript::AnimIdleShake()
	{
		mAnimator->Play(L"PhoenixIdleShake", true);
	}
	void PhoenixScript::AnimThink()
	{
		mAnimator->Play(L"PhoenixThink", false);
	}
	void PhoenixScript::AnimThinkTalk()
	{
		mAnimator->Play(L"PhoenixThinkTalk", true);
	}
	void PhoenixScript::AnimDeskHit()
	{
		mAnimator->Play(L"PhoenixDeskHit", false);
	}
	void PhoenixScript::AnimDeskTalk()
	{
		mAnimator->Play(L"PhoenixDeskTalk", true);
	}
	void PhoenixScript::AnimPoint()
	{
		mAnimator->Play(L"PhoenixPoint", false);
	}
	void PhoenixScript::AnimPointTalk()
	{
		mAnimator->Play(L"PhoenixPointTalk", true);
	}
	void PhoenixScript::AnimDocument()
	{
	}
	void PhoenixScript::AnimDocumentTalk()
	{
		mAnimator->Play(L"PhoenixDocumentTalk", true);
	}
	void PhoenixScript::AnimSweat()
	{
	}
	void PhoenixScript::AnimSweatTalk()
	{
		mAnimator->Play(L"PhoenixSweatTalk", false);
	}
	void PhoenixScript::AnimConfident()
	{
		mAnimator->Play(L"PhoenixConfidentIdle", false);
	}
	void PhoenixScript::AnimConfidentTalk()
	{
		mAnimator->Play(L"PhoenixConfidentTalk", true);
	}
	void PhoenixScript::AnimShocked()
	{
		mAnimator->Play(L"PhoenixShocked", false);
	}
	void PhoenixScript::AnimAbashed()
	{
	}
	void PhoenixScript::AnimAbashedTalk()
	{
		mAnimator->Play(L"PhoenixAbashedTalk", false);
	}
	void PhoenixScript::AnimWig()
	{
		mAnimator->Play(L"PhoenixWig", false);
	}

	void PhoenixScript::bindEvent()
	{
		mAnimator->GetCompleteEvent(L"PhoenixIdle") = std::bind(&PhoenixScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleBlink") = std::bind(&PhoenixScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleTalk") = std::bind(&PhoenixScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleTalkBlink") = std::bind(&PhoenixScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"PhoenixIdleTalk2") = std::bind(&PhoenixScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"PhoenixThink") = std::bind(&PhoenixScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink2") = std::bind(&PhoenixScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink3") = std::bind(&PhoenixScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink4") = std::bind(&PhoenixScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink5") = std::bind(&PhoenixScript::think, this);
		mAnimator->GetCompleteEvent(L"PhoenixThink6") = std::bind(&PhoenixScript::think, this);

		mAnimator->GetCompleteEvent(L"PhoenixDeskHit") = std::bind(&PhoenixScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"PhoenixDeskIdle") = std::bind(&PhoenixScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixDeskIdleBlink") = std::bind(&PhoenixScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"PhoenixPoint") = std::bind(&PhoenixScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"PhoenixPointIdle") = std::bind(&PhoenixScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixPointIdleBlink") = std::bind(&PhoenixScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"PhoenixDocumentTalk") = std::bind(&PhoenixScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"PhoenixSweatTalk") = std::bind(&PhoenixScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"PhoenixConfidentIdle") = std::bind(&PhoenixScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixConfidentIdleBlink") = std::bind(&PhoenixScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"PhoenixAbashedIdle") = std::bind(&PhoenixScript::blink, this);
		mAnimator->GetCompleteEvent(L"PhoenixAbashedIdleBlink") = std::bind(&PhoenixScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"PhoenixAbashedTalk") = std::bind(&PhoenixScript::returnIdle, this);
	}

	void PhoenixScript::start()
	{
	}

	void PhoenixScript::end()
	{
	}

	void PhoenixScript::returnIdle()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleBlink")
		{
			mAnimator->Play(L"PhoenixIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleTalkBlink")
		{
			mAnimator->Play(L"PhoenixIdleTalk2", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleTalk2")
		{
			mAnimator->Play(L"PhoenixIdleTalk", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixDeskHit" ||
			mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixDeskIdleBlink")
		{
			mAnimator->Play(L"PhoenixDeskIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixPoint" ||
			mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixPointIdleBlink")
		{
			mAnimator->Play(L"PhoenixPointIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixDocumentTalk")
		{
			mAnimator->Play(L"PhoenixDocument", true);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixSweatTalk")
		{
			mAnimator->Play(L"PhoenixSweatIdle", true);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixConfidentIdleBlink")
		{
			mAnimator->Play(L"PhoenixConfidentIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixAbashedIdleBlink" ||
			mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixAbashedTalk")
		{
			mAnimator->Play(L"PhoenixAbashedIdle", false);
		}
	}

	void PhoenixScript::blink()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdle")
		{
			mAnimator->Play(L"PhoenixIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixIdleTalk")
		{
			mAnimator->Play(L"PhoenixIdleTalkBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixDeskIdle")
		{
			mAnimator->Play(L"PhoenixDeskIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixPointIdle")
		{
			mAnimator->Play(L"PhoenixPointIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixConfidentIdle")
		{
			mAnimator->Play(L"PhoenixConfidentIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixAbashedIdle")
		{
			mAnimator->Play(L"PhoenixAbashedIdleBlink", false);
		}
	}

	void PhoenixScript::think()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink")
		{
			mAnimator->Play(L"PhoenixThink2", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink2")
		{
			mAnimator->Play(L"PhoenixThink3", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink3")
		{
			mAnimator->Play(L"PhoenixThink4", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink4")
		{
			mAnimator->Play(L"PhoenixThink5", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink5")
		{
			mAnimator->Play(L"PhoenixThink6", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"PhoenixThink6")
		{
			mAnimator->Play(L"PhoenixThink", false);
		}
	}
}
