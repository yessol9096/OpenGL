#include "stdafx.h"
#include "GameFramework.h"

int nSceneNum = 0;

CGameFramework::CGameFramework()
{
	for (int i = 0; i < 2; ++i)
		m_pScene[i] = NULL;
}

CGameFramework::~CGameFramework()
{
}

void CGameFramework::Init()
{
	m_pScene[0] = new LobbyScene;
	m_pScene[0]->Init();
	m_pScene[1] = new StageScene;
	m_pScene[1]->Init();
}

void CGameFramework::Update()
{
	m_pScene[nSceneNum]->Update();
}

void CGameFramework::Render()
{
	m_pScene[nSceneNum]->Render();
}

void CGameFramework::ProcessInput()
{
	m_pScene[nSceneNum]->ProcessInput();
}

void CGameFramework::FrameAdvance()
{
	ProcessInput();
	Update();
	Render();
}