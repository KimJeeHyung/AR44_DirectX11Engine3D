#include "jhTransform.h"
#include "jhRenderer.h"
#include "jhCamera.h"

namespace jh
{
	Transform::Transform() :
		Component(eComponentType::Transform),
		mFoward(Vector3::Forward),
		mRight(Vector3::Right),
		mUp(Vector3::Up),
		mScale(Vector3::One),
		mRotation(Vector3::Zero),
		mPosition(Vector3::Zero),
		mParent(nullptr)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		// ���� ���� �� ĳ���� �̵� ó��
	}

	void Transform::FixedUpdate()
	{
		// �������� ���� ��ġ������ ������Ʈ

		// ���� ��� ����

		// ũ�� ��ȯ ���
		Matrix scale = Matrix::CreateScale(mScale);

		// ȸ�� ��ȯ ���
		Matrix rotation;

		Vector3 radian(mRotation.x * (XM_PI / 180), mRotation.y * (XM_PI / 180),
			mRotation.z * (XM_PI / 180));

		rotation = Matrix::CreateRotationX(radian.x);
		rotation *= Matrix::CreateRotationY(radian.y);
		rotation *= Matrix::CreateRotationZ(radian.z);

		// �̵� ��ȯ ���
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);

		// ī�޶� ������Ʈ���� �������ش�.
		// ����� ����
		// ������� ����

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.world = mWorld;
		trCB.view = Camera::GetGpuViewMatrix();
		trCB.projection = Camera::GetGpuProjectionMatrix();
		
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}
}