#pragma once
#include "jhScene.h"
#include "jhLayer.h"
#include "jhGameObject.h"
#include "jhSceneManager.h"
#include "jhTransform.h"

namespace jh::object
{
	template<typename T>
	static T* Instantiate(enums::eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);
		gameObj->Initialize();

		return gameObj;
	}

	template<typename T>
	static T* Instantiate(enums::eLayerType type, Scene* scene)
	{
		T* gameObj = new T();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		return gameObj;
	}

	template<typename T>
	static T* Instantiate(enums::eLayerType type, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetParent(parent);

		return gameObj;
	}

	template<typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);

		return gameObj;
	}

	template<typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation,
		Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetParent(parent);

		return gameObj;
	}

	static void Destroy(GameObject* gameObject)
	{
		gameObject->Death();
	}

	// 씬 이동 시 이 오브젝트는 삭제하지 않는다.
	static void DontDestroyOnLoad(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		gameObject->DontDestroy(true);
	}
}
