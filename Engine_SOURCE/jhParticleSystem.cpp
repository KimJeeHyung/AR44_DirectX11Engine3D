#include "jhParticleSystem.h"
#include "jhMesh.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhStructedBuffer.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhTexture.h"
#include "jhTime.h"

namespace jh
{
	ParticleSystem::ParticleSystem() :
		BaseRenderer(eComponentType::ParticleSystem),
		mMaxParticles(100),
		mStartSize(Vector4(50.f, 50.f, 1.f, 1.f)),
		mStartColor(Vector4(1.f, 0.2f, 0.2f, 1.f)),
		mStartLifeTime(3.f),
		mFrequency(1.f),
		mTime(0.f),
		mCBData{},
		mSimulationSpace(eSimulationSpace::World),
		mRadius(500.f),
		mStartSpeed(200.f),
		mElapsedTime(0.f)
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;

		delete mSharedBuffer;
		mSharedBuffer = nullptr;
	}

	void ParticleSystem::Initialize()
	{
		mCS = Resources::Find<ParticleShader>(L"ParticleCS");

		std::shared_ptr<Mesh> point = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(point);

		// Material 세팅
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<Texture> tex = Resources::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		Vector4 startPos = Vector4(0.f, 0.f, 0.f, 0.f);
		for (size_t i = 0; i < mMaxParticles; i++)
		{
			particles[i].position = Vector4(0.f, 0.f, 20.f, 1.f);
			particles[i].active = 0;
			particles[i].direction = Vector4(cosf((float)i * (XM_2PI / (float)mMaxParticles)),
				sinf((float)i * (XM_2PI / (float)mMaxParticles)), 0.f, 1.f);

			particles[i].speed = 100.f;
		}

		mBuffer = new StructedBuffer();
		mBuffer->Create(sizeof(Particle), mMaxParticles, eSRVType::UAV, particles);

		mSharedBuffer = new StructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eSRVType::UAV, nullptr, true);
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::FixedUpdate()
	{
		// 파티클 생성 시간
		float aliveTime = 1.f / mFrequency;
		// 누적 시간
		mTime += Time::DeltaTime();
		if (aliveTime < mTime)
		{
			float f = (mTime / aliveTime);
			UINT iAliveCount = (UINT)f;
			mTime = f - std::floor(f);

			ParticleShared shared = { 5, };
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {};
			mSharedBuffer->SetData(&shared, 1);
		}

		mMaxParticles = mBuffer->GetStride();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mCBData.worldPosition = Vector4(pos.x, pos.y, pos.z, 1.f);
		mCBData.maxParticles = mMaxParticles;
		mCBData.radius = mRadius;
		mCBData.simulationSpace = (UINT)mSimulationSpace;
		mCBData.startSpeed = mStartSpeed;
		mCBData.startSize = mStartSize;
		mCBData.startColor = mStartColor;
		mCBData.startLifeTime = mStartLifeTime;
		mCBData.deltaTime = Time::DeltaTime();
		mCBData.elapsedTime += Time::DeltaTime();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&mCBData);
		cb->Bind(eShaderStage::ALL);

		mCS->SetSharedStructedBuffer(mSharedBuffer);
		mCS->SetStructedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::GS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mMaxParticles);

		mBuffer->Clear();
	}
}