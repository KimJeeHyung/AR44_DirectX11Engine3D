#include "jhCameraScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"

namespace jh
{
	CameraScript::CameraScript() :
		Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyDown(eKeyCode::W))
		{
			pos = Vector3(0.f, 9.f, -7.8f);
		}
		else if (Input::GetKeyDown(eKeyCode::A))
		{
			pos = Vector3(-28.7f, 0.f, -7.8f);
		}
		else if (Input::GetKeyDown(eKeyCode::S))
		{
			pos = Vector3(0.f, 0.f, -7.8f);
		}
		else if (Input::GetKeyDown(eKeyCode::D))
		{
			pos = Vector3(28.f, 0.f, -7.8f);
		}

		/*if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos += 10.f * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos += 10.f * -tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos += 10.f * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos += 10.f * -tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos += 10.f * tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos += 10.f * -tr->Foward() * Time::DeltaTime();
		}*/

		tr->SetPosition(pos);
	}

	void CameraScript::Render()
	{
	}
}

