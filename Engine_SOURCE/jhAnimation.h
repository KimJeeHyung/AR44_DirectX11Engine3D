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
			Vector2 leftTop;	// ���� ��� ��ǥ
			Vector2 size;		// ���� ��ܺ��� �߶� ���� ������ �ȼ� ����
			Vector2 offset;		// ������ ��ġ�� �����ϱ� ���� ��ǥ
			Vector2 atlasSize;	// �ؽ�ó �̹����� ũ��
			float duration;		// ������ ���� �ð� ����

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
