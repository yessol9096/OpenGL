#pragma once
class GameObject
{
protected:
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	GLint glWidth = 64, glHeight = 64;
	GLubyte *pBytes[TEXTURENUM];
	BITMAPINFO *info[TEXTURENUM];
	GLuint textures[TEXTURENUM];

public:
	GameObject();
	~GameObject();

	virtual void Init() = 0;
	virtual void render() = 0;
	GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);
	void InitTextureSetting();
};

class Map : public GameObject
{
public:

	float rotate_Y = 0;	// 회전 각도
	virtual void Init();
	virtual void render();
};

class Lobby : public GameObject
{
public:
	virtual void Init();
	virtual void render();
	void DrawUI(GLuint* textures, int textnum);
};