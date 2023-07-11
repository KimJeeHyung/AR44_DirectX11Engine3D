#include "jhMeshRenderer.h"
#include "jhGameObject.h"
#include "jhTransform.h"

namespace jh
{
	MeshRenderer::MeshRenderer() :
		BaseRenderer(eComponentType::MeshRenderer)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();
		
		GetMesh()->Render();
		
		GetMaterial()->Clear();
	}
}