#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>

#define PI 3.141592

int culling = 1;
// ����
void Light1();
void Light2();
void Light3();
void Light4();

float L1_Ambient = 0.5;
float L1_Ambient2 = 0.5;
float L1_Ambient3 = 0.5;

float L1_DiffuseLight1 = 1.0;
float L1_DiffuseLight2 = 0.0;
float L1_DiffuseLight3 = 0.0;

float L2_Ambient = 0.5;
float L2_Ambient2 = 0.5;
float L2_Ambient3 = 0.5;

float L2_DiffuseLight1 = 0.0;
float L2_DiffuseLight2 = 1.0;
float L2_DiffuseLight3 = 0.0;

float fDiffuse = 0.1;
float fSpecular = 0.1;

GLfloat lightpos[] = { -300, -180, 300, 1 };
GLfloat lightpos2[] = { 300, -180, 300, 1 };
GLfloat lightpos3[] = { 300, -180, 800, 1 };
GLfloat lightpos4[] = { -300, -180, 800, 1 };

GLfloat L1_AmbientLight[] = { L1_Ambient, L1_Ambient2, L1_Ambient3, 1.0f };
GLfloat L1_DiffuseLight[] = { L1_DiffuseLight1, L1_DiffuseLight2, L1_DiffuseLight3, 1.0f };

GLfloat L2_AmbientLight[] = { L2_Ambient, L2_Ambient2, L2_Ambient3, 1.0f };
GLfloat L2_DiffuseLight[] = { L2_DiffuseLight1, L2_DiffuseLight2, L2_DiffuseLight3, 1.0f };


GLfloat L3_AmbientLight[] = { L2_Ambient, L2_Ambient2, L2_Ambient3, 1.0f };
GLfloat L3_DiffuseLight[] = { L2_DiffuseLight1, L2_DiffuseLight2, L2_DiffuseLight3, 1.0f };


GLfloat L4_AmbientLight[] = { L2_Ambient, L2_Ambient2, L2_Ambient3, 1.0f };
GLfloat L4_DiffuseLight[] = { L2_DiffuseLight1, L2_DiffuseLight2, L2_DiffuseLight3, 1.0f };

GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };


float rotate_y;
float angle = 0.0;
float bangle = 0.0;

bool rotate_mX = false;
bool rotate_mY = false;

bool stop = false;
bool rotate = false;

bool L1_switch = false;
bool L2_switch = false;
bool L3_switch = false;
bool L4_switch = false;

bool vector_switch = false;
bool light_turn = false;

float viewZ = 0.0;

float MapX;
float MapY;
float MapZ;

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
		glColor3f(1, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(0, -200, 500);
		glScalef(1.0, 0.1, 1.0);
		glutSolidCube(500);
		glPopMatrix();
	}

}flr;

class Light_Cone
{
public:
	float scale = 1.0f;
	int dir = 0;

public:
	void draw() {
		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(lightpos[0], lightpos[1], lightpos[2]);
		glRotatef(90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix();	// ������ ��

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(lightpos2[0], lightpos2[1], lightpos2[2]);
		glRotatef(-90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix();	// ���� ��

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(lightpos3[0], lightpos3[1], lightpos3[2]);
		glRotatef(-90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix(); //  ���� ��

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(lightpos4[0], lightpos4[1], lightpos4[2]);
		glRotatef(90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix(); // ������ ��
	}
}L_Cone;

class Pyramid {

public:
	void draw() {
		glPushMatrix();
		glBegin(GL_TRIANGLES);	//��
		glColor3f(0.3f, 0.3f, 0.2f);
		if(vector_switch)
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0, -50, 150);   //1
		glVertex3f(50, -200, 100);   //2
		glVertex3f(-50, -200, 100);   //3
		glEnd();

		glBegin(GL_TRIANGLES);	// ��
		if (vector_switch)
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0, -50, 150);   //1
		glVertex3f(-50, -200, 200);   //4
		glVertex3f(50, -200, 200);   //5
		glEnd();

		glBegin(GL_TRIANGLES);	//��
		if (vector_switch)
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0, -50, 150);   //1
		glVertex3f(50, -200, 100);   //5
		glVertex3f(50, -200, 200);   //5
		glEnd();

		glBegin(GL_TRIANGLES);	//��
		if (vector_switch)
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0, -50, 150);   //1
		glVertex3f(-50, -200, 100);   //5
		glVertex3f(-50, -200, 200);   //5
		glEnd();
		glPopMatrix();
	}
}pyramid, pyramid2;

class Smallplanet {
private:
	int x = 0;
	int z = 0;
	int r = 0;
	int moveR = 40;
	int move1 = 0;
	int speed = 10;
	float r_color = 0;
	int size = 8;
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

		glTranslatef(x, -80, z);
		{
			for (int j = 0; j < 360; ++j) {
				glBegin(GL_POINTS);
				glVertex3f(r*cos((j / 180.0)*3.14), 0, r * sin((j / 180.0)*3.14)); //v2
				glEnd();
				glColor3f(r_color, 0.8f, 1.0f);
				glutSolidSphere(size, 20, 10);
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
}small[4];

class Snow {
public:
	GLfloat stransY;
	GLfloat stransX;
	GLfloat stransZ;
	float r;
	float speed;
	b_Dir dir = b_Dir::stop;
public:
	void draw() {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(stransX, stransY, stransZ);
		glutSolidSphere(5, 5, 5);
		glPopMatrix();
	}

	void snowing() {
		if (stransY > -200) stransY -= speed;
		else stransY = 500 + rand() % 100;
	}
}snow[100];
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
	glutInitWindowPosition(100, 100);
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
	small[1].setR(0);
	small[1].setmoveR(15);
	small[1].setspeed(5);
	small[1].setcolor(1.0f);
	small[1].setSize(2);

	small[2].setR(0);
	small[2].setmoveR(40);
	small[2].setspeed(5);
	small[2].setcolor(0.0f);
	small[2].setSize(8);

	small[3].setR(0);
	small[3].setmoveR(15);
	small[3].setspeed(5);
	small[3].setcolor(1.0f);
	small[3].setSize(2);

	for (int i = 0; i < 100; ++i)
	{
		snow[i].stransX = (i*-1)*rand() % 500;
		snow[i].stransZ = 300 + rand() % 300;
		snow[i].stransY = 500 + rand() % 100;
		snow[i].speed = rand() % 20;
	}

}
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//-------------------------------------------------------------------------------------------------------------------------
// �������� ���� ���÷��� �ݹ� �Լ�: ��� �׸��� ����� �� �Լ����� ��κ� ó�� ��
void DrawScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);      // ���� Ȱ��ȭ
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glPushMatrix();
	
	if (L1_switch)
	{
		glEnable(GL_LIGHT0);
		glPushMatrix(); //Save
		Light1();
		glPopMatrix();
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	if (L2_switch)
	{
		glEnable(GL_LIGHT1);
		glPushMatrix(); //Save
		Light2();
		glPopMatrix();
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
	if (L3_switch)
	{
		glEnable(GL_LIGHT2);
		glPushMatrix(); //Save
		Light3();
		glPopMatrix();
	}
	else
	{
		glDisable(GL_LIGHT2);
	}
	if (L4_switch)
	{
		glEnable(GL_LIGHT3);
		glPushMatrix(); //Save
		Light4();
		glPopMatrix();
	}
	else
	{
		glDisable(GL_LIGHT3);
	}
	
	glRotated(MapZ, 0, 0, 1.0);

	glRotated(MapX, 1.0, 0, 0);
	
	glRotated(MapY, 0, 1.0, 0);

	gluLookAt(0, 0, viewZ, 0, 0, -1, 0, 1, 0);
	
	//glRotated(rotateY, 0, 1.0, 0);
	// �ʿ��� ��ȯ ����
	flr.draw();											// glPushMatrix �Լ��� ȣ���Ͽ� ������ ��ǥ �ý����� ����
	
	L_Cone.draw();

	//�� . 
	glPushMatrix();
	glTranslatef(200, 0, 0);
	for (int i = 0; i < 100; ++i)
		snow[i].draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-120, 0, 330);
	pyramid.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120, 0, 330);
	pyramid2.draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-120, 0, 460);
	small[0].draw();
		glPushMatrix();
		glTranslatef(small[0].getX(), 0, small[0].getZ());
		small[1].draw();
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(120, 0, 460);
	small[2].draw();
	glPushMatrix();
	glTranslatef(small[2].getX(), 0, small[2].getZ());
	small[3].draw();
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
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����
	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)
	gluLookAt
	(
		0.0, 25.0, -500.0,
		0.0, -1.0, 0.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}

// �ʿ��� �ݹ� �Լ� ����: Ű���� �Է�, ���콺 �Է�, Ÿ�̸� ��
void Keyboard(unsigned char key, int x, int y)
{

	if (key == '1') {
		if (L1_switch == true) L1_switch = false;
		else if (L1_switch == false)L1_switch = true;
	}
	else if (key == '2') {
		if (L2_switch == true) L2_switch = false;
		else if (L2_switch == false)L2_switch = true;
	}
	else if (key == '3') {
		if (L3_switch == true) L3_switch = false;
		else if (L3_switch == false)L3_switch = true;
	}
	else if (key == '4') {
		if (L4_switch == true) L4_switch = false;
		else if (L4_switch == false)L4_switch = true;
	}
	else if (key == 'a') {
		L1_switch = true;
		L2_switch = true;
		L3_switch = true;
		L4_switch = true;
	}
	else if (key == 'A') {
		L1_switch = false;
		L2_switch = false;
		L3_switch = false;
		L4_switch = false;
	}
	else if (key == 'd') {
		L1_DiffuseLight1 += 0.1;
		L1_DiffuseLight2 += 0.1;
		L1_DiffuseLight3 += 0.1;
	}
	else if (key == 'D') {
		L1_DiffuseLight1 -= 0.1;
		L1_DiffuseLight2 -= 0.1;
		L1_DiffuseLight3 -= 0.1;
	}
	else if (key == '+')
	{
		viewZ += 10;
	}
	else if (key == 'n')
	{
		if (vector_switch == true) vector_switch = false;
		else if (vector_switch == false)vector_switch = true;
	}
	else if (key == 'y')
	{
		if (rotateY == true) rotateY = false;
		else if (rotateY == false)rotateY = true;
	}
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
}
float move_x1 = -300;
float move_x2 = 300;
float move_x3 = 300;
float move_x4 = -300;

float move_z1 = 300;
float move_z2 = 300;
float move_z3 = 800;
float move_z4 = 800;

void TimerFunction(int value)
{
	if (viewZ > 450 && MapY < 360 * 2)
		MapY += 5;
	else if (MapY == 360 * 2 && viewZ > 0)
	{
		viewZ -= 10;
	}
	
	////if (light_turn)
	//{
	//	lightpos[0] = -200 + 500 * cos((move_x1+=5 / 180.0)*3.14);
	//	lightpos[2] = 600 + 500 * sin((move_z1+=5 / 180.0)*3.14);

	//	/*lightpos2[0] = 300 + 400 * cos((move_x2 += 5 / 180.0)*3.14);
	//	lightpos2[2] = 500 + 400 * sin((move_z2 += 5 / 180.0)*3.14);*/

	//	//lightpos3[0] = 400 * cos((move_x3 += 5 / 180.0)*3.14);
	//	//lightpos3[2] =400 * sin((move_z3 += 5 / 180.0)*3.14);

	//	//lightpos4[0] = 400 * cos((move_x4 += 5 / 180.0)*3.14);
	//	//lightpos4[2] = 400 * sin((move_z4 += 5 / 180.0)*3.14);
	//}
	small[0].move();
	small[1].move();
	small[2].move();
	small[3].move();
	for (int i = 0; i < 100; ++i)
		snow[i].snowing();
	angle -= 10;
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {
	glutPostRedisplay();
}


void Light1() {

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glLightfv(GL_LIGHT0, GL_AMBIENT, L1_AmbientLight);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, L1_DiffuseLight);

	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);

}



void Light2() {

	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);

	glLightfv(GL_LIGHT1, GL_AMBIENT, L2_AmbientLight);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, L2_DiffuseLight);

	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);

}

void Light3() {

	glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);

	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_AmbientLight);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_DiffuseLight);

	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);

}

void Light4() {

	glLightfv(GL_LIGHT3, GL_POSITION, lightpos4);

	glLightfv(GL_LIGHT3, GL_AMBIENT, L2_AmbientLight);

	glLightfv(GL_LIGHT3, GL_DIFFUSE, L2_DiffuseLight);

	glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);

}