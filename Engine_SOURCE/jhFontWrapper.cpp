#include "jhFontWrapper.h"
#include "jhGraphicDevice_DX11.h"

namespace jh
{
	IFW1Factory* FontWrapper::mFW1Factory = nullptr;
	IFW1FontWrapper* FontWrapper::mFontWrapper = nullptr;

	bool FontWrapper::Initialize()
	{
		if (FAILED(FW1CreateFactory(FW1_VERSION, &mFW1Factory)))
			return false;

		ID3D11Device* pDevice = graphics::GetDevice()->GetID3D11Device();
		if (FAILED(mFW1Factory->CreateFontWrapper(pDevice, L"Batang", &mFontWrapper)))
			return false;

		return true;
	}

	void FontWrapper::DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb)
	{
		ID3D11DeviceContext* pContext = graphics::GetDevice()->GetID3D11DeviceContext();
		mFontWrapper->DrawString(
			pContext,
			str,	// String
			size,	// Font Size
			x,		// X position
			y,		// Y position
			rgb,	// Text Color, 0xAaBbGgRr
			0		// Flags (for example FW1_RESTORESTATE to keep context states unchanged)
		);
	}

	void FontWrapper::Release()
	{
		mFW1Factory->Release();
		mFW1Factory = nullptr;

		mFontWrapper->Release();
		mFontWrapper = nullptr;
	}
}
