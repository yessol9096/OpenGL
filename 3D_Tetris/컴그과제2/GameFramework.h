#pragma once
#include "Scene.h"

class CGameFramework
{
private:
	Scene*		m_pScene[2];
public:
	CGameFramework();
	~CGameFramework();

	void Init();
	void ProcessInput();
	void Update();
	void Render();
	void FrameAdvance();
};