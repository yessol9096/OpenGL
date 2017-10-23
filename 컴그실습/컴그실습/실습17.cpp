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

class Bigplanet {
public:
	int x = 0;
	int y = 0;
	int r = 120;
	void draw() {
		glColor3f(0, 0, 1.0);
		glPushMatrix();
		glTranslatef(0, 0, 0);
		{
			if(fig == Fig::solid) glutSolidSphere(30, 50, 50);
			else if (fig == Fig::wire) glutWireSphere(30, 30, 30);
			for (int j = 0; j < 360; ++j) {
				glBegin(GL_POINTS);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(x + r*cos((j / 180.0)*3.14), 0,y + r * sin((j / 180.0)*3.14)); //v2
				glEnd();
			}
		}
		glPopMatrix();
	}
}big;

class Smallplanet {
private:
	int x = -300;
	int z = 0;
	int r = 0;
	int moveR = 120;
	int move1 = 0;
	int speed = 10;
	float r_color = 0;
	int size = 10;
public:
	void setX(int x1) { x = x1; }
	void setZ(int z1) { z = z1; }
	void setR(int r1) { r = r1; }
	void setSize(int n) { size = n; }
	void setspeed(int speed1) { speed = speed1; }
	void setmoveR(int moveR1) { moveR = moveR1; }
	void setcolor(int r) { r_color = r; }

	float getX() { return x; }
	float getZ() { return z; }

	void draw() {
		glPushMatrix();
		
		glTranslatef(x, 0, z);
		{
			for (int j = 0; j < 360; ++j) {
				glBegin(GL_POINTS);
				glVertex3f(r*cos((j / 180.0)*3.14), 0 ,r * sin((j / 180.0)*3.14)); //v2
				glEnd();
				glColor3f(r_color, 0.8f, 1.0f);
				if (fig == Fig::solid) glutSolidSphere(size, 20, 10);
			else if (fig == Fig::wire) glutWireSphere(size, 20, 10);
			}
		}
		glPopMatrix();
	}
	void move()
	{
		x = moveR * cos((move1 / 180.0)*3.14);
		z = moveR * sin((move1 / 180.0)*3.14);
		move1 += speed;
	}
}small[6];



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
	small[0].setX(-300);
	small[0].setZ(0);
	small[0].setR(20);
	small[0].setmoveR(120);
	small[0].setspeed(10);

	small[1].setR(0);
	small[1].setmoveR(20);
	small[1].setspeed(5);
	small[1].setcolor(1.0f);
	small[1].setSize(5);

	small[2].setX(-300);
	small[2].setZ(0);
	small[2].setR(20);
	small[2].setmoveR(120);
	small[2].setspeed(8);

	small[3].setR(0);
	small[3].setmoveR(20);
	small[3].setspeed(5);
	small[3].setcolor(1.0f);
	small[3].setSize(5);

	small[4].setX(-300);
	small[4].setZ(0);
	small[4].setR(20);
	small[4].setmoveR(120);
	small[4].setspeed(5);

	small[5].setR(0);
	small[5].setmoveR(20);
	small[5].setspeed(5);
	small[5].setcolor(1.0f);
	small[5].setSize(5);
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
		big.draw();
		small[0].draw();
		glPushMatrix();
			glTranslatef(small[0].getX(), 0, small[0].getZ());
			small[1].draw();
		glPopMatrix();
		glPushMatrix();
			glRotatef(45, 0, 1, 1);
			for (int j = 0; j < 360; ++j) {
				glBegin(GL_POINTS);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f( 120 *cos((j / 180.0)*3.14), 0,120 * sin((j / 180.0)*3.14)); //v2
				glEnd();
			}
			small[2].draw();
			glPushMatrix();
			glTranslatef(small[2].getX(), 0, small[2].getZ());
			small[3].draw();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glRotatef(-45, 0, 1, 1);
			for (int j = 0; j < 360; ++j) {
				glBegin(GL_POINTS);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(120 * cos((j / 180.0)*3.14),0,120 * sin((j / 180.0)*3.14)); //v2
				glEnd();
			}
			small[4].draw();
			glPushMatrix();
			glTranslatef(small[4].getX(), 0, small[4].getZ());
			small[5].draw();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
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
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
}

void TimerFunction(int value)
{
	small[0].move(); small[1].move();
	small[2].move(); small[3].move();
	small[4].move(); small[5].move();
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