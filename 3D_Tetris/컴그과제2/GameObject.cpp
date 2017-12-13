#include "stdafx.h"
#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::render()
{
}

GLubyte* GameObject::LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;

	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth * (*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);

	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}
void GameObject::InitTextureSetting()
{
	glGenTextures(TEXTURENUM, textures);
	// 타이틀 화면
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	pBytes[8] = LoadDIBitmap("tetris_main.bmp", &info[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 600, 800, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
///////////////////////////////////////////////////////////////////////////

void Map::Init()
{
	// 기본 맵 그리기
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		gluLookAt
		(
			0.0, 200.0, -300.0,
			1.0, 0.0, -1.0,
			0.0, 1.0, 0.0
		);
		glRotatef(45, 0, 1, 0);
		glRotatef(rotate_Y, 0, 1, 0);

		glBegin(GL_LINE_LOOP);
		glVertex3f(100, 100, -100); // 1
		glVertex3f(-100, 100, -100); // 2
		glVertex3f(-100, -100, -100);  // 3
		glVertex3f(100, -100, -100); // 4	// 앞 
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-100, 100, 100); // 1
		glVertex3f(-100, 100, -100); // 2
		glVertex3f(-100, -100, -100);  // 3
		glVertex3f(-100, -100, 100); // 4	// 오른쪽옆
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(100, 100, 100); // 1
		glVertex3f(100, 100, -100); // 2
		glVertex3f(100, -100, -100);  // 3
		glVertex3f(100, -100, 100); // 4	// 왼쪽옆
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(100, 100, 100); // 1
		glVertex3f(-100, 100, 100); // 2
		glVertex3f(-100, -100, 100);  // 3
		glVertex3f(100, -100, 100); // 4	// 뒤 
		glEnd();
	}
	glPopMatrix();
}

void Map::render()
{
}

///////////////////////////////////////////////////////////////////////////

void Lobby::Init()
{
}

void Lobby::render()
{
	glPushMatrix();
	gluLookAt
	(
		0.0, 200.0, -300.0,
		1.0, 0.0, -1.0,
		0.0, 1.0, 0.0
	);
	glTranslatef(0.0f, 0.0f, 30.0f);
	glScalef(80.0f, 80.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	DrawUI(textures, 8);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glPopMatrix();
}

GLvoid Lobby::DrawUI(GLuint* textures, int texnum)
{
	glEnable(GL_TEXTURE_2D);
	// Front
	glBindTexture(GL_TEXTURE_2D, textures[texnum]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}