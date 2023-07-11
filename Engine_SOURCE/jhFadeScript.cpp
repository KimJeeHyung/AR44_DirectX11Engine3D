#include "jhFadeScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhApplication.h"
#include "jhConstantBuffer.h"
#include "jhRenderer.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhSceneManager.h"

extern jh::Application application;

namespace jh
{
	FadeScript::FadeScript() :
		Script(),
		mCamera(nullptr),
		mIsFadeOut(false),
		mDeltaTime(0.f),
		mFadeTime(1.f),
		mbFadeStart(false),
		mbFadeComplete(false)
	{
	}

	FadeScript::~FadeScript()
	{
	}

	void FadeScript::Initialize()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		mCamera = renderer::cameras[(UINT)type][0];
	}

	void FadeScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		if (Input::GetKeyState(eKeyCode::F) == eKeyState::DOWN)
		{
			FadeOut();
		}
		else if (Input::GetKeyState(eKeyCode::G) == eKeyState::DOWN)
		{
			FadeIn();
		}

		if (mIsFadeOut == true)
		{
			mDeltaTime += Time::DeltaTime() / mFadeTime;

			if (mDeltaTime >= 1.f)
			{
				mbFadeComplete = true;
				mbFadeStart = false;
			}
		}
		else
		{
			mDeltaTime -= Time::DeltaTime() / mFadeTime;

			if (mbFadeStart && mDeltaTime <= 0.f)
			{
				//mbFadeComplete = true;
				mbFadeStart = false;
			}
		}

		// »ó¼ö ¹öÆÛ
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
		renderer::FadeCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;
		data.deltaTime = mDeltaTime;
		data.padding = Vector3(0.f, 0.f, 0.f);

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void FadeScript::FixedUpdate()
	{
	}

	void FadeScript::Render()
	{
	}

	// ¹à¾ÆÁü
	void FadeScript::FadeIn()
	{
		mbFadeComplete = false;
		mbFadeStart = true;
		mIsFadeOut = false;
		mDeltaTime = 1.f;
	}

	// ¾îµÎ¿öÁü
	void FadeScript::FadeOut()
	{
		mbFadeComplete = false;
		mbFadeStart = true;
		mIsFadeOut = true;
		mDeltaTime = 0.f;
	}
}