#include "jhJudgeScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	JudgeScript::JudgeScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	JudgeScript::~JudgeScript()
	{
	}

	void JudgeScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void JudgeScript::Update()
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
			AnimNod();
		}
		if (Input::GetKey(eKeyCode::N_4))
		{
			AnimShake();
		}
		if (Input::GetKey(eKeyCode::N_5))
		{
			AnimSurprisedIdle();
		}
		if (Input::GetKey(eKeyCode::N_6))
		{
			AnimSurprisedIdleTalk();
		}
		if (Input::GetKey(eKeyCode::N_7))
		{
			AnimSternIdle();
		}
		if (Input::GetKey(eKeyCode::N_8))
		{
			AnimSternIdleTalk();
		}
		if (Input::GetKey(eKeyCode::N_9))
		{
			AnimThink();
		}
	}

	void JudgeScript::Render()
	{
	}

	void JudgeScript::bindEvent()
	{
		mAnimator->GetCompleteEvent(L"JudgeNod") = std::bind(&JudgeScript::returnIdle, this);
		mAnimator->GetCompleteEvent(L"JudgeShake") = std::bind(&JudgeScript::returnIdle, this);
		//mAnimator->GetCompleteEvent(L"MiaFowardIdleBlink") = std::bind(&MiaScript::returnIdle, this);
	}

	void JudgeScript::returnIdle()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"JudgeNod" ||
			mAnimator->GetActiveAnimation()->AnimationName() == L"JudgeShake")
		{
			mAnimator->Play(L"JudgeIdle", true);
		}
	}

	void JudgeScript::blink()
	{
	}

	void JudgeScript::AnimIdle()
	{
		mAnimator->Play(L"JudgeIdle", true);
	}
	void JudgeScript::AnimIdleTalk()
	{
		mAnimator->Play(L"JudgeIdleTalk", true);
	}
	void JudgeScript::AnimNod()
	{
		mAnimator->Play(L"JudgeNod", false);
	}
	void JudgeScript::AnimShake()
	{
		mAnimator->Play(L"JudgeShake", false);
	}
	void JudgeScript::AnimSurprisedIdle()
	{
		mAnimator->Play(L"JudgeSurprisedIdle", true);
	}
	void JudgeScript::AnimSurprisedIdleTalk()
	{
		mAnimator->Play(L"JudgeSurprisedTalk", true);
	}
	void JudgeScript::AnimSternIdle()
	{
		mAnimator->Play(L"JudgeSternIdle", true);
	}
	void JudgeScript::AnimSternIdleTalk()
	{
		mAnimator->Play(L"JudgeSternTalk", true);
	}
	void JudgeScript::AnimThink()
	{
		mAnimator->Play(L"JudgeThink", false);
	}
}
