#pragma once
#include "jhComponent.h"

namespace jh
{
	class AudioListener : public Component
	{
	public:
		AudioListener();
		~AudioListener();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}
