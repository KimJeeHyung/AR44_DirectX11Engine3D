#pragma once
#include "CommonInclude.h"
#include "jhMath.h"
#include "jhGraphicDevice_DX11.h"

#include "jhMesh.h"
#include "jhShader.h"
#include "jhConstantBuffer.h"
#include "jhCamera.h"
#include "jhLight.h"
#include "jhStructedBuffer.h"

using namespace jh::math;
using namespace jh::graphics;

namespace jh::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
		Vector3 tangent;
		Vector3 biNormal;
		Vector3 normal;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(FadeCB, CBSLOT_FADE)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
		float deltaTime;
		Vector3 padding;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		Vector2 atlasSize;

		UINT type;
	};

	CBUFFER(LightCB, CBSLOT_NUMBEROFLIGHT)
	{
		UINT numberOfLight;
	};

	CBUFFER(ParticleSystemCB, CBSLOT_PARTICLESYSTEM)
	{
		Vector4 worldPosition;
		Vector4 startColor;
		Vector4 startSize;

		UINT maxParticles;
		UINT simulationSpace;
		float radius;
		float startSpeed;

		float startLifeTime;
		float deltaTime;
		float elapsedTime; //누적시간
		int padding;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 noiseSize;
	};

	// 정점 데이터
	extern Vertex vertexes[4];
	// 상수버퍼
	extern ConstantBuffer* constantBuffers[];
	// States
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern Camera* mainCamera;
	extern std::vector<Camera*> cameras[];
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;
	extern StructedBuffer* lightsBuffer;

	void Initialize();
	void Render();
	void Release();

	void PushLightAttribute(LightAttribute lightAttribute);
	void BindLights();
	void BindNoiseTexture();
}

