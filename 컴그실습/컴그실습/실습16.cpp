#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>
#define PI 3.141592

enum class Fig {
	sphere	// �� 
	,cube	//������ü
	,cone	// ����
	,teapot // ������
}fig;
float angle = 0.0;
bool rotateX = false;
bool rotateY = false;
bool rotateZ = false;
bool rotateL = false;
bool rotateR = false;
bool rotate = false;
int randoml;
int randomr;
class Floor {
public:
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	GLfloat size = 100.0;

	void draw() {
		glColor3f(1, 0.8, 0.0);
		glPushMatrix();
		glTranslatef(0, -100, 0);
		glScalef(1.0, 0.1, 1.0);
		glutSolidCube(300);
		glPopMatrix();
	}

}flr;

class Solidfigure {
public:

	void draw() {
		glColor3f(1, 0, 0.0);
		glPushMatrix();
		glTranslatef(70, -100, 0);
		if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
		else if (rotateY == true)glRotatef(angle, 0, 1, 0);
		else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		else if (rotateL == true)
		{
			if (randoml == 0)glRotatef(angle, 1, 0, 0);
			else if (randoml == 1)glRotatef(angle, 0, 1, 0);
			else if (randoml== 2)glRotatef(angle, 0, 0, 1);
		}
		if (fig == Fig::sphere) {
			glutSolidSphere(25, 50, 50);
		}
		else if (fig == Fig::cube) {
			glScalef(1.0, 2.0, 1.0);
			glutSolidCube(50);
		}
		else if (fig == Fig::cone) {
			glTranslatef(-35, 0, 0);
			glutSolidCone(25, 50, 30, 30);
		}
		else if (fig == Fig::teapot) {
			glutSolidTeapot(30);
		}
		glPopMatrix();
	}
}solid;

class Wirefigure {
public:
	void draw() {
		glColor3f(1, 0, 0.0);
		glPushMatrix();
		glTranslatef(-70, -100, 0);
		if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
		else if (rotateY == true)glRotatef(angle, 0, 1, 0);
		else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		else if (rotateR == true)
		{
			if(randomr == 0)glRotatef(angle, 1, 0, 0);
			else if (randomr == 1)glRotatef(angle, 0, 1, 0);
			else if (randomr == 2)glRotatef(angle, 0, 0, 1);
		}
		if (fig == Fig::sphere) {
			glutWireSphere(25, 30, 30);
		}
		else if (fig == Fig::cube) {
			glScalef(1.0, 2.0, 1.0);
			glutWireCube(50);
		}
		else if (fig == Fig::cone) {
			glTranslatef(35, 0, 0);
			glutWireCone(25, 50, 20, 20);
		}
		else if (fig == Fig::teapot) {
			glutWireTeapot(30);
		}
		glPopMatrix();
	}
}wire;

void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);

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
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�

	glPushMatrix();
	if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
	else if (rotateY == true)glRotatef(angle, 0, 1, 0);
	else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(-10, 0, 0);
		glScalef(1.0, 0.1, 0.1);
		glutSolidCube(20);
	glPopMatrix();	
	glPushMatrix();
	if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
	else if (rotateY == true)glRotatef(angle, 0, 1, 0);
	else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		glTranslatef(0, 0, 10);
		glColor3f(0.0, 0.0, 1.0);
		glScalef(0.1, 0.1, 1.0);
		glutSolidCube(20);
	glPopMatrix();
	glPushMatrix();
	if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
	else if (rotateY == true)glRotatef(angle, 0, 1, 0);
	else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		glTranslatef(0, 10, 0);
		glColor3f(0.0, 1.0, 0.0);
		glScalef(0.1, 1.0, 0.1);
		glutSolidCube(20);
	glPopMatrix();
													// �ʿ��� ��ȯ ����
	flr.draw();											// glPushMatrix �Լ��� ȣ���Ͽ� ������ ��ǥ �ý����� ����
	solid.draw();													// �ʿ��� ��� ��� �ʱ�ȭ ( glLoadIdentity ( ); )
	wire.draw();													// ��ȯ ����: �̵�, ȸ��, ���� �� �𵨿� ���� �� ��ȯ �Լ��� ȣ���Ѵ�.
																	// ��ȯ�� ���� �Ŀ��� ������ ��ǥ�ý����� �ٽ� �����ϱ� ���Ͽ� glPopMatrix �Լ� ȣ��
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
		0.0, 0.3, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}

// �ʿ��� �ݹ� �Լ� ����: Ű���� �Է�, ���콺 �Է�, Ÿ�̸� ��
void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1') fig = Fig::sphere;
	else if (key == '2') fig = Fig::cube;
	else if (key == '3') fig = Fig::cone;
	else if (key == '4') fig = Fig::teapot;

	if (key == 'x' || key == 'X') {
		rotateX = true;
		rotateY = false;
		rotateZ = false;
	}
	else if (key == 'y' || key == 'Y') {
		rotateX = false;
		rotateY = true;
		rotateZ = false;

	}
	else if (key == 'z' || key == 'Z') {
		rotateX = false;
		rotateY = false;
		rotateZ = true;
	}
	else if (key == 'l' || key == 'L') {
		rotateX = false;
		rotateY = false;
		rotateZ = false;
		randoml = rand() % 3;
		rotateL = true;
	}
	else if (key == 'r' || key == 'R') {
		rotateX = false;
		rotateY = false;
		rotateZ = false;
		
		rotateR = true; 
		randomr = rand() % 3;
	}
	srand((unsigned)time(NULL));
	
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
}

void TimerFunction(int value)
{
	angle -= 10;
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {
	glutPostRedisplay();
}