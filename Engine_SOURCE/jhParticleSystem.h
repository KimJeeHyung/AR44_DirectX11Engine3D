#pragma once
#include "jhBaseRenderer.h"
#include "jhParticleShader.h"

namespace jh
{
	enum class eSimulationSpace
	{
		Local,
		World,
	};

	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructedBuffer* mBuffer;
		class StructedBuffer* mSharedBuffer;

		std::shared_ptr<graphics::ParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		Vector4 mStartSize;
		Vector4 mStartColor;

		eSimulationSpace mSimulationSpace;
		UINT mMaxParticles;
		float mStartLifeTime;
		float mFrequency;
		float mRadius;

		float mStartSpeed;
		float mTime;
		float mElapsedTime;	// �����ð�
	};
}
