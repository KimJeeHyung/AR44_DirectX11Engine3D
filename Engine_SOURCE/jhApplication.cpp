#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhSceneManager.h"
#include "jhResources.h"
#include "jhCollisionManager.h"
#include "jhFmod.h"
#include "jhFontWrapper.h"

namespace jh
{
	using namespace graphics;

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();
		Fmod::Initialize();
		FontWrapper::Initialize();

		CollisionManager::Initialize();
		renderer::Initialize();
		SceneManager::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::FixedUpdate()
	{
		CollisionManager::FixedUpdate();
		SceneManager::FixedUpdate();
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		//SceneManager::Render();
		renderer::Render();
		CollisionManager::Render();
	}

	void Application::Destroy()
	{
	}

	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
		Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::Release()
	{
		//Resources::
		Fmod::Release();
		FontWrapper::Release();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;

			ValidationMode validationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			//graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
