#include "stdafx.h"
#include "Scene.h"
extern int nSceneNum;

Scene::Scene()
{
}

Scene::~Scene()
{
}

////////////////////////////////////////////////////////
Lobby lobby;
LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
	lobby.render();
}

void LobbyScene::glDrawScene()
{

	
	glutSwapBuffers();
}

void LobbyScene::glReshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, 1.0f, 1.0f, 1000.0f);
	glTranslatef(0.0f, 0.0f, -100.0f);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);

	// 모델링 변환 설정: 디스플레이 콜벡 함수에서 모델 변환 적용을 위해
	// 매트릭스 모드를 저장.
	glMatrixMode(GL_MODELVIEW);
}

void LobbyScene::ProcessInput()
{
	/*if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		nSceneNum = 1; printf("현재 씬값: %d\n", nSceneNum);
	}*/
}

void LobbyScene::Update()
{}

void LobbyScene::Render()
{
	glutDisplayFunc(glDrawScene);
	glutReshapeFunc(glReshape);
	glutPostRedisplay();
}

////////////////////////////////////////////////////////

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
}

void StageScene::Init()
{
}

void StageScene::ProcessInput()
{
}

void StageScene::Update()
{
}

Map mapInfo;	// 스테이지 맵 생성자

void StageScene::glDrawScene()
{
	
	mapInfo.Init();
	
	std::cout << mapInfo.rotate_Y << std::endl;
	glutSwapBuffers();

}

void StageScene::glReshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, 1.0f, 1.0f, 1000.0f);
	glTranslatef(0.0f, 0.0f, -100.0f);

	// 모델링 변환 설정: 디스플레이 콜벡 함수에서 모델 변환 적용을 위해
	// 매트릭스 모드를 저장.
	glMatrixMode(GL_MODELVIEW);
}

GLvoid StageScene::glKeyboard(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A')
	{
		mapInfo.rotate_Y -= 10;
	}
	else if (key == 'd' || key == 'D')
	{
		mapInfo.rotate_Y += 10;
	}
	glutPostRedisplay();
}

GLvoid StageScene::glKeyboardUp(unsigned char key, int x, int y)
{
}

GLvoid StageScene::glSpecialKeyboard(int key, int x, int y)
{
	
}

GLvoid StageScene::glSpecialKeyboardUp(int key, int x, int y)
{
	
}

GLvoid StageScene::glTimerFunc(int value)
{
}

GLvoid StageScene::Render()
{
	glutDisplayFunc(glDrawScene);
	glutReshapeFunc(glReshape);
	glutKeyboardFunc(glKeyboard);
	glutKeyboardUpFunc(glKeyboardUp);
	glutSpecialFunc(glSpecialKeyboard);
	glutSpecialUpFunc(glSpecialKeyboardUp);
}