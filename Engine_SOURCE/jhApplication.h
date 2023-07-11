#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"
#include "jhGraphicDevice_DX11.h"

namespace jh
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Initialize();
		virtual void Update();	// 게임 로직, 캐릭터 이동 등등(CPU Update)
		virtual void FixedUpdate();	// GPU Update
		virtual void Render();
		virtual void Destroy();

		// Running main engine loop
		void Run();
		void Present();
		void Release();

		void SetWindow(HWND hwnd, UINT width, UINT height);
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool initialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}
