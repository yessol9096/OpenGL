#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>
#define PI 3.141592

enum class Fig {
	solid,
	wire
}fig;
float angle = 0.0;
bool rotateX = false;
bool rotateY = false;
bool rotateZ = false;
bool rotateL = false;
bool rotateR = false;
bool rotate = false;

float transX = 0.0;
float transY = 0.0;
float transZ = 0.0;

int random;

class Plane {
public:
	int x = 0;
	int y = 0;
	int z = 0;
	float move1 = 0;
	float moveR = 120;
	int speed = 10;
	int r = 120;

	void draw() {
		glColor3f(0, 0, 1);
		glPushMatrix();
		glRotatef(move1, 0, 1, 0);
		glTranslatef(100, 0, 0);
		{
			glPushMatrix();	// ����
			glColor3f(1, 1, 0);
			glTranslatef(0, -5, 0);
			glScalef(8.0, 0.5, 3.0);
			glutSolidCube(10);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0, 0, 1,0.5);	// ����
			glScalef(1.0, 1.0, 2.0);
			glutSolidCube(25);
			glPopMatrix();

			glPushMatrix();	// ����
				glColor3f(1, 0, 1);
				glTranslatef(0, 0, 25);
				glScalef(1.0, 1.0, 4.0);
				glutSolidCube(5);
				glTranslatef(0, 5, 1.5);
				glScalef(0.5, 2.0, 0.25);
				glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();	// �����緯
			glColor3f(1, 0, 0);
			glTranslatef(0, 0, -28);
			glRotatef(move1, 0, 0, 1);
			glScalef(4.0, 1.0, 1.0);
			glutSolidCube(5);
			
			glPopMatrix();

			glPushMatrix();	// �����緯
			glColor3f(0, 1, 1);
			glTranslatef(0, 0, -28);
			glRotatef(move1, 0, 0, 1);
			glScalef(1.0, 4.0, 1.0);
			glutSolidCube(5);

			glPopMatrix();
			
		}
		glPopMatrix();
	}

	
	void move()
	{
		x = moveR * cos((move1 / 180.0)*3.14);
		z = moveR * sin((move1 / 180.0)*3.14);
		move1 += speed;
	}
}plane;



void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);
void UpdateCam();
int culling = 1;
GLdouble cyRotate = 0.1;
GLdouble cxRotate = 0.0;
GLdouble czRotate = 0.0;
void main()
{
	// ������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
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

// �ʱ�ȭ �Լ� (Optional): �ʿ��� ��쿡 �ۼ�, �ʱ�ȭ�ؾ� �� �������� ���� ���� ����� ���� ����
void SetupRC() {
	// �ʿ��� ������, ��ǥ�� ���� �ʱ�ȭ
	// ��� ���� �ʱ�ȭ


}

//-------------------------------------------------------------------------------------------------------------------------
// �������� ���� ���÷��� �ݹ� �Լ�: ��� �׸��� ����� �� �Լ����� ��κ� ó�� ��
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�
	UpdateCam();
	glPushMatrix();
	glTranslatef(transX, transY, transZ);
	plane.draw();
	glPopMatrix();
	glutSwapBuffers(); // ��� ���
}

// �ٽñ׸��� �ݹ� �Լ�
// ó�� �����츦 �� ��, ������ ��ġ�� �ű�ų� ũ�⸦ ������ �� ȣ��
// ����Ʈ ����, ���� ��ǥ�� ����, ���� ��ǥ ���� ���� �Ѵ�.
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
	glTranslatef(0.0, 0.0, -300.0);
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����
	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)
	gluLookAt
	(
		0.0, 0.1, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}
bool flag = false;
// �ʿ��� �ݹ� �Լ� ����: Ű���� �Է�, ���콺 �Է�, Ÿ�̸� ��
void Keyboard(unsigned char key, int x, int y)
{

	if (key == '1') fig = Fig::solid;
	else if (key == '2') fig = Fig::wire;

	if (key == 'a') {
		transX += 5;
	}
	else if (key == 'd') {
		transX -= 5;
	}
	else if (key == 'w') {
		transY += 5;
	}
	else if (key == 's') {
		transY -= 5;
	}
	else if (key == '+') {
		transZ += 5;
	}
	else if (key == '-') {
		transZ -= 5;
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
	else if (key == 'i')
	{
		cyRotate = 0.1;
		cxRotate = 0.0;
		czRotate = 0.0;
		transX = 0;
		transY = 0;
		transZ = 0;
	}

	else if (key == 'p') {
		plane.speed = 10;
	}
	else if (key == 'm') {
		plane.speed = -10;
	}
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
}

void TimerFunction(int value)
{
	plane.move();
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
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