#include "jhPayneScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	PayneScript::PayneScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	PayneScript::~PayneScript()
	{
	}

	void PayneScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void PayneScript::Update()
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
			AnimSweat();
		}
		if (Input::GetKey(eKeyCode::N_4))
		{
			AnimSweatTalk();
		}
	}

	void PayneScript::Render()
	{
	}

	void PayneScript::AnimIdle()
	{
		mAnimator->Play(L"PayneIdle", false);
	}
	void PayneScript::AnimIdleTalk()
	{
		mAnimator->Play(L"PayneIdleTalk", true);
	}
	void PayneScript::AnimSweat()
	{
		mAnimator->Play(L"PayneSweat", true);
	}
	void PayneScript::AnimSweatTalk()
	{
		mAnimator->Play(L"PayneSweatTalk", true);
	}

	void PayneScript::bindEvent()
	{
	}

	void PayneScript::returnIdle()
	{
	}

	void PayneScript::blink()
	{
	}
}
