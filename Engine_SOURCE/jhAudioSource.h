#pragma once
#include "jhComponent.h"
#include "jhAudioClip.h"

namespace jh
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void Play();
		void Stop();
		void SetLoop(bool loop);

		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }
		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }

	private:
		std::shared_ptr<AudioClip> mAudioClip;
	};
}
