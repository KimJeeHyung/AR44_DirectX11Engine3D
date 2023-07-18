#include "jhLight.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhRenderer.h"

namespace jh
{
	Light::Light() :
		Component(eComponentType::Light)
	{
	}

	Light::~Light()
	{
	}

	void Light::Initialize()
	{
	}

	void Light::Update()
	{
	}

	void Light::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 position = tr->GetPosition();
		mAttribute.position = Vector4(position.x, position.y, position.z, 1.f);
		mAttribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 0.f);

		renderer::PushLightAttribute(mAttribute);
	}

	void Light::Render()
	{
	}
}
