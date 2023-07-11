#pragma once
#include "jhScript.h"

namespace jh
{
	class TextScript : public Script
	{
	public:
		TextScript();
		~TextScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetText(const wchar_t* str, float x, float y, float size, UINT rgba);

	private:
		const wchar_t* mString;
		float mPosX;
		float mPosY;
		float mSize;
		UINT mRGBA;
	};
}
