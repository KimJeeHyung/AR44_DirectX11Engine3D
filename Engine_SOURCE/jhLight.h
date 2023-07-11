#pragma once
#include "jhComponent.h"
#include "jhGraphics.h"

namespace jh
{
	class Light : public Component
	{
	public:
		Light();
		~Light();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		graphics::LightAttribute GetLightAttribute() { return mAttribute; }

		void SetDiffuse(Vector4 diffuse) { mAttribute.diffuse = diffuse; }
		void SetAmbient(Vector4 ambient) { mAttribute.ambient = ambient; }
		void SetType(eLightType type) { mAttribute.type = type; }
		void SetRadius(float radius) { mAttribute.radius = radius; }
		void SetAngle(float angle) { mAttribute.angle = angle; }

		Vector4 GetDiffuse() { return mAttribute.diffuse; }
		eLightType GetType() { return mAttribute.type; }
		float GetRadius() { return mAttribute.radius; }
		float GetAngle() { return mAttribute.angle; }

	private:
		graphics::LightAttribute mAttribute;
	};
}
