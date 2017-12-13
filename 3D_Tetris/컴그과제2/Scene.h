#pragma once
#include"GameObject.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	static void glDrawScene();
	static void glReshape(int w, int h);
	static void glKeyboard(unsigned char key, int x, int y);
	static void glKeyboardUp(unsigned char key, int x, int y);
	static void glSpecialKeyboard(int key, int x, int y) {}
	static void glSpecialKeyboardUp(int key, int x, int y) {}
	static void glTimerFunc(int value);

};

class LobbyScene : public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	virtual void Init();
	virtual void Update();
	virtual void ProcessInput();
	virtual void Render();
	static void glDrawScene();
	static void glReshape(int w, int h);
};

class StageScene : public Scene
{
public:
	StageScene();
	~StageScene();

	virtual void Init();
	virtual void Update();
	virtual void ProcessInput();
	virtual void Render();
	static void glDrawScene();
	static void glReshape(int w, int h);
	static void glKeyboard(unsigned char key, int x, int y);
	static void glKeyboardUp(unsigned char key, int x, int y);
	static void glSpecialKeyboard(int key, int x, int y);
	static void glSpecialKeyboardUp(int key, int x, int y);
	static void glTimerFunc(int value);

};