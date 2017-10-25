#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>

#define PI 3.141592
void UpdateCam();

int culling = 1;

GLdouble cyRotate = 0.1;
GLdouble cxRotate = 0.0;
GLdouble czRotate = 0.0;
float angle = 0.0; 
float bangle = 0.0;

bool rotate_mX = false;
bool rotate_mY = false;

bool rotate_eZ = false;
bool rotate_eX = false;

bool stop = false;
bool rotate = false;

float transX = 0.0;
float transY = 0.0;
float transZ = 0.0;

bool rotateX = false;
bool rotateY = false;
bool rotateZ = false;

int random;



enum class b_Dir {
	x,
	z,
	y,
	stop
};
enum class Dir {
	right,
	left
};

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

class Crain {
public:
	GLfloat ctransX;
	GLfloat transZ;
	GLfloat angleY;
	GLfloat angle_mY;
	GLfloat angle_mX;
	GLfloat angle_eZ;
	GLfloat angle_eX;
	Dir dir = Dir::right;
public:
	void draw() {
		glColor3f(1, 0, 0.0);
		glPushMatrix();
		////////////�ؿ� ũ���� 
		glTranslatef(ctransX, -100, 100);
		glRotatef(angleY, 0, 1, 0);
		glutSolidCube(50);
		///////���� ũ���� 
		glPushMatrix();
		if (rotate_mY == true)glRotatef(angle_mY, 0, 1, 0);
		if (rotate_mX == true)glRotatef(angle_mX, 1, 0, 0);
		glTranslatef(0, 40, 0);
		glColor3f(0, 1, 0);
		glScalef(0.5, 1.0, 0.5);
		glutSolidCube(30);
		///////���� �簢��
		glPushMatrix();
		if (rotate_eZ == true)glRotatef(angle_eZ, 0, 0, 1);
		if (rotate_eX == true)glRotatef(angle_eX, 1, 0, 0);
		glTranslatef(0, 25, 0);
		glColor3f(0, 0, 1);
		glScalef(0.5, 0.5, 0.5);
		glutSolidCube(40);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}

	void move()
	{
		if (dir == Dir::right) { transX += 10; if (transX > 150)dir = Dir::left; }
		else if (dir == Dir::left) { transX -= 10; if (transX < -150) dir = Dir::right; }
	}

	void collision(int r)
	{

	}

}crain;
class Rectangle_Tree
{
public:
	GLfloat rotateY;
public:
	void draw() {

		glPushMatrix();
		glColor3f(0.8f, 0.4f, 0.04f);
		glTranslatef(150, -100, 300);
		glScalef(1.0f, 2.0f, 1.0f);
		glutSolidCube(50);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0f, 0.4f, 0.04f);
		glTranslatef(150, -25, 300);
		glRotatef(rotateY, 0, 1, 0);
		glScalef(3.0f, 1.0f, 1.0f);
		glutSolidCube(50);
		glPopMatrix();
	}

	void move()
	{
		rotateY += 10;
	}

}r_tree;

class Sphere_Tree
{
public:
	GLfloat size = 60;
public:
	void draw() {

		glPushMatrix();
		glColor3f(0.8f, 0.4f, 0.04f);
		glTranslatef(-150, -100, 300);
		glScalef(1.0f, 2.0f, 1.0f);
		glutSolidCube(50);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0f, 0.4f, 0.4f);
		glTranslatef(-150, -25, 300);
		glutWireSphere(size, 20, 10);
		glPopMatrix();
	}

	void move()
	{
		if (size == 60) size = 50;
		else if (size == 50) size = 60;
	}

}s_tree;

class Torus
{
public:
	GLfloat moveY;
	int dir = 0;
public:
	void draw() {



		glPushMatrix();
		glColor3f(1.0f, 0.4f, 0.04f);
		glTranslatef(150, -100, 100);
		glScalef(1.0f, 4.0f, 1.0f);
		glutSolidCube(50);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.3f, 0.8f, 0.4f);
		glRotatef(90, 1, 0, 0);
		glTranslatef(130, 50, moveY);
		glutWireTorus(25, 40, 20, 20);
		glPopMatrix();

	}

	void move()
	{
		if (dir == 0)
		{
			if (moveY > 100) dir = 1;
			moveY += 10;
		}
		else if (dir == 1)
		{
			if (moveY < 0) dir = 0;
			moveY -= 10;
		}
	}

}torus;

class Cone
{
public:
	float scale = 1.0f;
	int dir = 0;
public:
	void draw() {


		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(-150, -105, 50);
		glRotatef(90, 1, 0, 0);
		glScalef(scale, scale, scale);
		glutWireCone(25, 40, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(-150, -150, 50);
		glRotatef(-90, 1, 0, 0);
		glScalef(1.1 - scale, 1.1 - scale, 1.1 - scale);
		glutWireCone(25, 40, 20, 20);
		glPopMatrix();

	}

	void move()
	{
		if (dir == 0)
		{
			if (scale < 0) dir = 1;
			scale -= 0.1;
		}
		else if (dir == 1)
		{
			if (scale > 1) dir = 0;
			scale += 0.1;
		}
	}

}cone;

class Door {
public:
	float move = 25;
	float dir = 0;
	float roateY = 0;
	GLfloat rotateY;
public:
	void draw() {


		glPushMatrix();
		glColor3f(0.0f, 0.4f, 0.4f);
		glTranslatef(move, -100, 180);
		glRotatef(rotateY, 0, 1, 0);
		glScalef(0.5f, 2.0f, 0.5f);
		glutSolidCube(40);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0f, 0.4f, 0.4f);
		glTranslatef(-move, -100, 180);
		glRotatef(rotateY, 0, 1, 0);
		glScalef(0.5f, 2.0f, 0.5f);
		glutSolidCube(40);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0f, 0.4f, 0.4f);
		glTranslatef(0, -50, 180); glRotatef(rotateY*1.32, 0, 1, 0);
		glScalef(2.0f, 0.5f, 0.5f);
		glutSolidCube(40);
		glPopMatrix();

	}

	void open()
	{
		if (dir == 0)
		{
			if (move < 10) dir = 1;
			move -= 5;
		}
		else if (dir == 1)
		{
			if (move > 25) dir = 0;
			move += 5;
		}
		rotateY += 10;
	}

}door;

class Ball {
public:
	GLfloat btransX;
	GLfloat btransZ;
	float r;
	b_Dir dir = b_Dir::stop;
public:
	void draw() {
		glColor3f(1, 0, 0.0);
		glPushMatrix();
		glTranslatef(btransX, -100, btransZ);
		if (rotateX == true) { dir = b_Dir::x; glRotatef(bangle, 1, 0, 0); }
		else if (rotateY == true) { dir = b_Dir::y; glRotatef(bangle, 0, 1, 0); }
		else if (rotateZ == true) { dir = b_Dir::z;  glRotatef(bangle, 0, 0, 1); }
		else if (stop == true) { dir = b_Dir::stop; }
		glutWireSphere(25, 30, 30);
		glPopMatrix();
	}

	void collision() {
		
	}
}ball;


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
	UpdateCam();
	glPushMatrix();
	glTranslatef(transX, transY, transZ);
	// �ʿ��� ��ȯ ����
	flr.draw();											// glPushMatrix �Լ��� ȣ���Ͽ� ������ ��ǥ �ý����� ����
	r_tree.draw();
	s_tree.draw();												// �ʿ��� ��� ��� �ʱ�ȭ ( glLoadIdentity ( ); 
	
	door.draw();
	crain.draw();
	ball.draw();
	torus.draw();	
	cone.draw();
	

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
		0.0, 0.5, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}

// �ʿ��� �ݹ� �Լ� ����: Ű���� �Է�, ���콺 �Է�, Ÿ�̸� ��
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'l') {
		if (ball.btransX < 150) ball.btransX += 5;
		rotateX = true;
		rotateY = false;
		rotateZ = false;
		stop = false;
		bangle -= 10;
	}
	else if (key == 'L') {
		if (ball.btransX > -150) ball.btransX -= 5;
		rotateX = true;
		rotateY = false;
		rotateZ = false;
		stop = false;
		bangle -= 10;
	}
	else if (key == 'n' || key == 'N') {
		rotateX = false;
		rotateY = true;
		rotateZ = false;
		stop = false;
		bangle -= 10;
	}
	else if (key == 'm') {
		if (ball.btransZ < 150) ball.btransZ += 5;
		rotateX = false;
		rotateY = false;
		rotateZ = true;
		stop = false;
		bangle -= 10;
	}
	else if (key == 'M') {
		if (ball.btransZ > -150) ball.btransZ -= 5;
		rotateX = false;
		rotateY = false;
		rotateZ = true;
		stop = false;
		bangle -= 10;
	}
	else if (key == 'y') {
		crain.angleY -= 5;
	}
	else if (key == 'Y') {
		crain.angleY += 5;
	}
	else if (key == 'a') {
		rotate_mY = true;
		rotate_mX = false;
		crain.angle_mY -= 5;
	}
	else if (key == 'd') {
		rotate_mY = true;
		rotate_mX = false;
		crain.angle_mY += 5;
	}
	else if (key == 's') {
		rotate_mY = false;
		rotate_mX = true;
		crain.angle_mX -= 5;
	}
	else if (key == 'w') {
		rotate_mY = false;
		rotate_mX = true;
		crain.angle_mX += 5;
	}
	else if (key == 'i') {
		rotate_eZ = false;
		rotate_eX = true;
		crain.angle_eX += 5;
	}
	else if (key == 'k') {
		rotate_eZ = false;
		rotate_eX = true;
		crain.angle_eX -= 5;
	}
	else if (key == 'j') {
		rotate_eZ = true;
		rotate_eX = false;
		crain.angle_eZ -= 5;
	}
	else if (key == 'l') {
		rotate_eZ = true;
		rotate_eX = false;
		crain.angle_eZ += 5;
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

	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
}

void TimerFunction(int value)
{
	
	crain.move();
	cone.move();
	door.open();
	r_tree.move();
	s_tree.move();
	torus.move();
	
	angle -= 10;
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