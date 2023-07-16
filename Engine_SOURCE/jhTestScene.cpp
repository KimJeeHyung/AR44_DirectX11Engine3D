#include "jhTestScene.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhTexture.h"
#include "jhPlayerScript.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhSpriteRenderer.h"
#include "jhGridScript.h"
#include "jhObject.h"
#include "jhFadeScript.h"
#include "jhInput.h"
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhMonster.h"
#include "jhCollisionManager.h"
#include "jhAnimator.h"
#include "jhLight.h"
#include "jhPaintShader.h"
#include "jhParticleSystem.h"

namespace jh
{
	TestScene::TestScene() :
		Scene(eSceneType::Test)
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		// 메인 카메라 오브젝트
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		cameraObj->SetName(L"MainCamera");
		cameraObj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		// 3D Object
		GameObject* player = object::Instantiate<GameObject>(eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		//player->GetComponent<Transform>()->SetRotation(Vector3(15.0f, 45.0f, 0.0f));
		player->SetName(L"Player");
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMaterial(Resources::Find<Material>(L"BasicMaterial"));
		//mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
		mr->SetMesh(Resources::Find<Mesh>(L"SphereMesh"));
		player->AddComponent<PlayerScript>();

		// Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->SetName(L"DirectionalLight");

			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -100.f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));
		}

		// Point Light
		/*{
			GameObject* pointLight = object::Instantiate<GameObject>(eLayerType::Player);
			pointLight->GetComponent<Transform>()->SetPosition(Vector3(3.f, 0.f, 0.f));
			Light* lightComp = pointLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(10.f);
			lightComp->SetDiffuse(Vector4(1.f, 0.f, 0.f, 1.f));
		}*/

		// UI 카메라 오브젝트
		/*GameObject* UICameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* UICameraComp = UICameraObj->AddComponent<Camera>();
		UICameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		UICameraComp->DisableLayerMasks();
		UICameraComp->TurnLayerMask(eLayerType::UI, true);*/

		// PaintShader
		/*std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTexture);
		paintShader->OnExcute();*/

		// Light Object
		//GameObject* spriteObj = object::Instantiate<GameObject>(eLayerType::Player);
		//spriteObj->SetName(L"LIGHT");
		//Transform* spriteTr = spriteObj->GetComponent<Transform>();
		//spriteTr->SetPosition(Vector3(5.f, 0.f, 10.f));
		//spriteTr->SetScale(Vector3(5.f, 5.f, 1.f));
		//
		//SpriteRenderer* sr = spriteObj->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
		//sr->SetMaterial(spriteMaterial);
		//sr->SetMesh(mesh);

		// Particle
		/*{
			Player* obj = object::Instantiate<Player>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.f, 0.f, 100.f));
			obj->AddComponent<ParticleSystem>();
		}*/

		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);

		Scene::Initialize();
	}

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TestScene::Render()
	{
		Scene::Render();
	}

	void TestScene::OnEnter()
	{
	}

	void TestScene::OnExit()
	{
	}
}
