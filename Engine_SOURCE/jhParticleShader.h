#pragma once
#include "jhComputeShader.h"
#include "jhStructedBuffer.h"

namespace jh::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetStructedBuffer(StructedBuffer* buffer) { mBuffer = buffer; }
		void SetSharedStructedBuffer(StructedBuffer* buffer) { mSharedBuffer = buffer; }

	private:
		StructedBuffer* mBuffer;
		StructedBuffer* mSharedBuffer;
	};
}
