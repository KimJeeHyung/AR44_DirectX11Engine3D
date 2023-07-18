#include "jhAudioListener.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhFmod.h"

namespace jh
{
	AudioListener::AudioListener() :
		Component(eComponentType::AudioListener)
	{
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::Initialize()
	{
	}

	void AudioListener::Update()
	{
	}

	void AudioListener::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Forward();
		Vector3 up = tr->Up();

		Vector3 vel = { 0.f, 0.f, 0.f };
		Fmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
	}

	void AudioListener::Render()
	{
	}
}