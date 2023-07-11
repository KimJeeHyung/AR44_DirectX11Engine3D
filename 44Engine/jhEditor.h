#pragma once
#include "jhDebugObject.h"
#include "jhEditorObject.h"
#include "jhWidget.h"
#include "jhGraphics.h"

namespace jh
{
	class Editor
	{
	public:
		void Initialize();
		void Run();

		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender(graphics::DebugMesh& mesh);

	private:
		std::vector<Widget*> mWidgets;
		std::vector<EditorObject*> mEditorObjects;
		std::vector<DebugObject*> mDebugObjects;
	};
}
