#pragma once
#include "jhResource.h"
#include "jhFmod.h"

namespace jh
{
	using namespace jh::math;
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		~AudioClip();

		virtual HRESULT Load(const std::wstring& path);

		void Play();
		void Stop();
		void Set3DAttributes(const Vector3 pos, const Vector3 vel);
		void SetLoop(bool loop) { mbLoop = loop; }

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
	};
}
