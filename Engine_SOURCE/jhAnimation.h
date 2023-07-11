#pragma once
#include "jhEntity.h"
#include "jhTexture.h"

using namespace jh::math;
using namespace jh::graphics;
namespace jh
{
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// 좌측 상단 좌표
			Vector2 size;		// 좌측 상단부터 잘라낼 가로 세로의 픽셀 길이
			Vector2 offset;		// 렌더링 위치를 조정하기 위한 좌표
			Vector2 atlasSize;	// 텍스처 이미지의 크기
			float duration;		// 프레임 간의 시간 간격

			Sprite() :
				leftTop(0.f, 0.f),
				size(0.f, 0.f),
				offset(0.f, 0.f),
				atlasSize(0.f),
				duration(0.1f)
			{
			}
		};

		Animation();
		~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteRowCount, UINT spriteColumnCount, float duration);
		void BindShader();
		void Reset();
		void Clear();

		bool IsComplete() { return mbComplete; }
		std::wstring& AnimationName() { return mAnimationName; }

	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}
