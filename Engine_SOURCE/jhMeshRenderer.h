#pragma once
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhBaseRenderer.h"

using namespace jh::graphics;
namespace jh
{
	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}
