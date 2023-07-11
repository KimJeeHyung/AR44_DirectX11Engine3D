#include "jhTextScript.h"
#include "jhFontWrapper.h"

namespace jh
{
	TextScript::TextScript() :
		Script(),
		mString(nullptr),
		mPosX(0.f),
		mPosY(0.f),
		mSize(0.f),
		mRGBA(FONT_RGBA(0, 0, 0, 255))
	{
	}

	TextScript::~TextScript()
	{
	}

	void TextScript::Initialize()
	{
	}

	void TextScript::Update()
	{
	}

	void TextScript::Render()
	{
		FontWrapper::DrawFont(mString, mPosX, mPosY, mSize, mRGBA);
	}

	void TextScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void TextScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TextScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void TextScript::SetText(const wchar_t* str, float x, float y, float size, UINT rgba)
	{
		mString = str;
		mPosX = x;
		mPosY = y;
		mSize = size;
		mRGBA = rgba;
	}
}