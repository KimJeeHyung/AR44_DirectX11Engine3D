#include "jhLarryScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	LarryScript::LarryScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	LarryScript::~LarryScript()
	{
	}

	void LarryScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void LarryScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

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
		}

		if (Input::GetKey(eKeyCode::N_1))
		{
			mAnimator->Play(L"LarryIdle", false);
		}
		if (Input::GetKey(eKeyCode::N_2))
		{
			mAnimator->Play(L"LarryIdleTalk", true);
		}
		if (Input::GetKey(eKeyCode::N_3))
		{
			mAnimator->Play(L"LarryConfidentIdle", true);
		}
	}

	void LarryScript::Render()
	{
	}

	void LarryScript::bindEvent()
	{
		mAnimator->GetCompleteEvent(L"LarryIdle") = std::bind(&LarryScript::blink, this);
		mAnimator->GetCompleteEvent(L"LarryIdleBlink") = std::bind(&LarryScript::returnIdle, this);
	}

	void LarryScript::returnIdle()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"LarryIdleBlink")
		{
			mAnimator->Play(L"LarryIdle", false);
		}
	}

	void LarryScript::blink()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"LarryIdle")
		{
			mAnimator->Play(L"LarryIdleBlink", false);
		}
	}
}
