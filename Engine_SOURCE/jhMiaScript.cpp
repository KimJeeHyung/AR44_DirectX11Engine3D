#include "jhMiaScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	MiaScript::MiaScript() :
		Script(),
		mAnimator(nullptr)
	{
	}

	MiaScript::~MiaScript()
	{
	}

	void MiaScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		bindEvent();
	}

	void MiaScript::Update()
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
			AnimFowardIdle();
		}
		if (Input::GetKey(eKeyCode::N_2))
		{
			AnimFowardIdleTalk();
		}
		if (Input::GetKey(eKeyCode::N_3))
		{
			AnimFowardGrin();
		}
		if (Input::GetKey(eKeyCode::N_4))
		{
			AnimFowardSmileIdle();
		}
		if (Input::GetKey(eKeyCode::N_5))
		{
			AnimFowardSmileIdleTalk();
		}
		if (Input::GetKey(eKeyCode::N_6))
		{
			AnimFowardShock();
		}
		if (Input::GetKey(eKeyCode::N_7))
		{
			AnimFowardShockTalk();
		}
		if (Input::GetKey(eKeyCode::N_8))
		{
			AnimCounselIdle();
		}
		if (Input::GetKey(eKeyCode::N_9))
		{
			AnimCounselIdleTalk();
		}
		if (Input::GetKey(eKeyCode::N_0))
		{
			AnimCounselShock();
		}
		if (Input::GetKey(eKeyCode::P))
		{
			AnimCounselShockTalk();
		}
		if (Input::GetKey(eKeyCode::O))
		{
			AnimCounselSad();
		}
		if (Input::GetKey(eKeyCode::I))
		{
			AnimCounselSadTalk();
		}
		if (Input::GetKey(eKeyCode::U))
		{
			AnimCounselExasperate();
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			AnimCounselExasperateTalk();
		}
	}

	void MiaScript::Render()
	{
	}

	void MiaScript::bindEvent()
	{
		mAnimator->GetCompleteEvent(L"MiaFowardIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaFowardIdleBlink") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaFowardGrin") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaFowardSmileIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaFowardSmileIdleBlink") = std::bind(&MiaScript::returnIdle, this);

		mAnimator->GetCompleteEvent(L"MiaCounselIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaCounselIdleBlink") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaCounselIdleSad") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaCounselIdleSadBlink") = std::bind(&MiaScript::returnIdle, this);
		
		mAnimator->GetCompleteEvent(L"MiaCounselExasperateIdle") = std::bind(&MiaScript::blink, this);
		mAnimator->GetCompleteEvent(L"MiaCounselExasperateIdleBlink") = std::bind(&MiaScript::returnIdle, this);
	}

	void MiaScript::returnIdle()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardIdleBlink")
		{
			mAnimator->Play(L"MiaFowardIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardGrin" ||
			mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardSmileIdleBlink")
		{
			mAnimator->Play(L"MiaFowardSmileIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdleBlink")
		{
			mAnimator->Play(L"MiaCounselIdle", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdleSadBlink")
		{
			mAnimator->Play(L"MiaCounselIdleSad", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselExasperateIdleBlink")
		{
			mAnimator->Play(L"MiaCounselExasperateIdle", false);
		}
	}

	void MiaScript::blink()
	{
		if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardIdle")
		{
			mAnimator->Play(L"MiaFowardIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaFowardSmileIdle")
		{
			mAnimator->Play(L"MiaFowardSmileIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdle")
		{
			mAnimator->Play(L"MiaCounselIdleBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselIdleSad")
		{
			mAnimator->Play(L"MiaCounselIdleSadBlink", false);
		}
		else if (mAnimator->GetActiveAnimation()->AnimationName() == L"MiaCounselExasperateIdle")
		{
			mAnimator->Play(L"MiaCounselExasperateIdleBlink", false);
		}
	}

	void MiaScript::AnimFowardIdle()
	{
		mAnimator->Play(L"MiaFowardIdle", false);
	}
	void MiaScript::AnimFowardIdleTalk()
	{
		mAnimator->Play(L"MiaFowardIdleTalk", true);
	}
	void MiaScript::AnimFowardGrin()
	{
		mAnimator->Play(L"MiaFowardGrin", false);
	}
	void MiaScript::AnimFowardSmileIdle()
	{
		mAnimator->Play(L"MiaFowardSmileIdle", false);
	}
	void MiaScript::AnimFowardSmileIdleTalk()
	{
		mAnimator->Play(L"MiaFowardSmileTalk", true);
	}
	void MiaScript::AnimFowardShock()
	{
		mAnimator->Play(L"MiaFowardShock", true);
	}
	void MiaScript::AnimFowardShockTalk()
	{
		mAnimator->Play(L"MiaFowardShockTalk", true);
	}
	void MiaScript::AnimCounselIdle()
	{
		mAnimator->Play(L"MiaCounselIdle", false);
	}
	void MiaScript::AnimCounselIdleTalk()
	{
		mAnimator->Play(L"MiaCounselIdleTalk", true);
	}
	void MiaScript::AnimCounselShock()
	{
		mAnimator->Play(L"MiaCounselShock", true);
	}
	void MiaScript::AnimCounselShockTalk()
	{
		mAnimator->Play(L"MiaCounselShockTalk", true);
	}
	void MiaScript::AnimCounselSad()
	{
		mAnimator->Play(L"MiaCounselIdleSad", false);
	}
	void MiaScript::AnimCounselSadTalk()
	{
		mAnimator->Play(L"MiaCounselIdleSadTalk", true);
	}
	void MiaScript::AnimCounselExasperate()
	{
		mAnimator->Play(L"MiaCounselExasperateIdle", false);
	}
	void MiaScript::AnimCounselExasperateTalk()
	{
		mAnimator->Play(L"MiaCounselExasperateTalk", true);
	}
}
