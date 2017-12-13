#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#define PI 3.141592


void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);
void UpdateCam();
int culling = 1;
int shading = 1;
int depth = 1;
float open_up;
float move_x;
float move_y;

float move_fx;
float move_fz;
float open_front;
float move_z;
bool Open_front = false;
bool Open_up = false;
GLdouble cyRotate = 0.5;
GLdouble cxRotate = 0.0;
GLdouble czRotate = 0.0;

GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
GLuint texture_object[6];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);



void main()
{
	// ������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Points Drawing");

	// ���� ���� �ʱ�ȭ �Լ�
	SetupRC();

	// �ʿ��� �ݹ� �Լ� ����
	glutDisplayFunc(DrawScene); // ��� �ݹ� �Լ�
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ� �Լ�
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ���� �����ϱ�
}

void SetupRC() {
	glGenTextures(2, texture_object);

	// 1
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	pBytes = LoadDIBitmap("1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 2
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	// �ؽ�ó ���� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);

}
int rotateX = 0;
//-------------------------------------------------------------------------------------------------------------------------
// �������� ���� ���÷��� �ݹ� �Լ�: ��� �׸��� ����� �� �Լ����� ��κ� ó�� ��
void DrawScene()
{
	UpdateCam();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�


	glPushMatrix();
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);	// �ø�����
	//glShadeModel(GL_SMOOTH); // �Ǵ� glShadeModel (GL_FLAT)

	glPushMatrix();
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotateX, 0.0, 1.0, 0.0);

	if (culling == 1) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (shading == 1) {
		glShadeModel(GL_SMOOTH); // �Ǵ� glShadeModel (GL_FLAT)
	}
	else {
		glShadeModel(GL_FLAT);
	}

	if (depth == 1) {
		glEnable(GL_DEPTH_TEST);
	}

	else {
		glDisable(GL_DEPTH_TEST);
	}

	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);		// ����
	
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-50.0, 50.0, 50.0);   //1

	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-50.0, -50.0, 50.0);   //2

	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(50.0, -50.0, 50.0);   //3

	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(50.0, 50.0, 50.0);   //4

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);		// ������ ����
	
	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(50.0, 50.0, 50.0);   //4

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(50.0, -50.0, 50.0);   //3

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, -50.0, -50.0);   //7

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(50.0, 50.0, -50.0);   //6

	glEnd();




	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);		// �ո�

	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(-50.0, 50.0, -50.0);   //5

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(50.0, 50.0, -50.0);   //6

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, -50.0, -50.0);   //7

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(-50.0, -50.0, -50.0);   //8

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);		// ���ʸ�
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-50.0, 50.0, 50.0);   //1

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(-50.0, 50.0, -50.0);   //5

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(-50.0, -50.0, -50.0);   //8

	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-50.0, -50.0, 50.0);   //2

	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);		// ����

	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(-50.0, 50.0, -50.0);   //1

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(-50.0, 50.0, 50.0);   //4

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, 50.0, 50.0);   //5

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(50.0, 50.0, -50.0);   //6

	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);		// �Ʒ���

	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(-50.0, -50.0, 50.0);   //2

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(-50.0, -50.0, -50.0);   //8

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, -50.0, -50.0);   //7

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(50.0, -50.0, 50.0);   //3
	glEnd();

	glPopMatrix();
	glPopMatrix();
	//glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); // ��� ���
}

void Reshape(int w, int h)
{
	// ����Ʈ ��ȯ ����: ��� ȭ�� ����
	glViewport(0, 0, w, h);
	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ���� ������ ����ϴ� ���:
	gluPerspective(60.0, 600 / 400, 1.0, 1000.0);
	//glTranslatef(0.0, 0.0, -300.0);
	//glOrtho (0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����


	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'c' || key == 'C') {
		if (culling == 0)culling = 1;
		else if (culling == 1)culling = 0;
	}
	else if (key == 's' || key == 'S') {
		if (shading == 0)shading = 1;
		else if (shading == 1)shading = 0;
	}
	else if (key == 'd' || key == 'D') {
		if (depth == 0)depth = 1;
		else if (depth == 1)depth = 0;
	}
	else if (key == 'u') {
		if (Open_up == false) Open_up = true;
		else if (Open_up == true)Open_up = false;
	}
	else if (key == 'f') {
		if (Open_front == false) Open_front = true;
		else if (Open_front == true)Open_front = false;
	}
	else if (key == 'x') {
		if (cyRotate<1) cyRotate += 0.1;
	}
	else if (key == 'X') {
		if (cyRotate>-1) cyRotate -= 0.1;
	}
	else if (key == 'y') {
		if (cxRotate<1) cxRotate += 0.1;
	}
	else if (key == 'Y') {
		if (cxRotate>-1) cxRotate -= 0.1;
	}
	else if (key == 'z') {
		czRotate += 1;
	}
	else if (key == 'Z') {
		czRotate -= 1;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	rotateX += 10;
	if (Open_up == true && open_up < 40) { move_x = open_up * 0.6; open_up += 0.5; move_y = open_up*1.0; }
	else if (Open_up == false && open_up != 0) {
		move_x = open_up * 0.6; open_up -= 0.5; move_y = open_up*1.0;
	}
	if (Open_front == true && open_front > -40) { move_fx = open_front * 0.6; open_front -= 0.5; move_fz = open_front * 1.0; }
	else if (Open_front == false && open_front != 0) {
		move_fx = open_front * 0.6; open_front += 0.5; move_fz = open_front * 1.0;
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {

	glutPostRedisplay();
}

void UpdateCam() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ���� ������ ����ϴ� ���:
	gluPerspective(60.0, 600 / 400, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����

	glRotatef(czRotate, 0, 0, 1);
	gluLookAt
	(
		cxRotate, cyRotate, 0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glRotatef(-czRotate, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}



GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ������.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� ������ ����.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� ��������.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� ��������.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}