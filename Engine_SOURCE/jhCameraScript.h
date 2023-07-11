#pragma once
#include "jhScript.h"

namespace jh
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

	private:
	};
}
