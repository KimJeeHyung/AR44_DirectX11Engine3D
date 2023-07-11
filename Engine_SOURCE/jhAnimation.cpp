#include "jhAnimation.h"
#include "jhTime.h"
#include "jhRenderer.h"

namespace jh
{
	Animation::Animation() :
		mAnimator(nullptr),
		mAtlas(nullptr),
		mSpriteSheet{},
		mIndex(-1),
		mTime(0.f),
		mbComplete(false)
	{
	}

	Animation::~Animation()
	{
	}

	UINT Animation::Update()
	{
		if (mbComplete)
			return -1;

		// �ð� üũ
		mTime += Time::DeltaTime();

		// ���� �ð��� �ش� �������� �����ð��� �Ѿ�� ���� ���������� �̵�
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			++mIndex;

			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;
			}

			return mIndex;
		}

		return -1;
	}

	void Animation::FixedUpdate()
	{
	}

	void Animation::Render()
	{
	}

	void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas,
		Vector2 leftTop, Vector2 size, Vector2 offset,
		UINT spriteRowCount, UINT spriteColumnCount, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < spriteColumnCount; i++)
		{
			for (size_t j = 0; j < spriteRowCount; j++)
			{
				// API�ʹ� �ٸ��� 0 ~ 1 ������ ������ǥ�� ��ġ�� ǥ���ؾ� �Ѵ�.
				Sprite sprite = {};
				sprite.leftTop = Vector2((leftTop.x + (size.x * (float)j)) / width, (leftTop.y + (size.y * (float)i)) / height);

				sprite.size = Vector2(size.x / width, size.y / height);
				sprite.offset = offset;
				sprite.duration = duration;
				sprite.atlasSize = Vector2(1700.f / width, 1700.f / height);

				mSpriteSheet.push_back(sprite);
			}
		}
	}

	void Animation::BindShader()
	{
		mAtlas->BindShaderResource(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.size = mSpriteSheet[mIndex].size;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}

	void Animation::Reset()
	{
		mTime = 0.f;
		mIndex = 0;
		mbComplete = false;
	}

	void Animation::Clear()
	{
		// �ؽ�ó Clear
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::None;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}
}
