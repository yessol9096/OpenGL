#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>

#define PI 3.141592
void UpdateCam();

int culling = 1;
// 조명
void Light1();
void Light2();

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

GLfloat lightpos[] = { -400, 200, -500, 1 };
GLfloat lightpos2[] = { 400, 200, -500, 1 };

GLfloat L1_AmbientLight[] = { L1_Ambient, L1_Ambient2, L1_Ambient3, 1.0f };
GLfloat L1_DiffuseLight[] = { L1_DiffuseLight1, L1_DiffuseLight2, L1_DiffuseLight3, 1.0f };

GLfloat L2_AmbientLight[] = { L2_Ambient, L2_Ambient2, L2_Ambient3, 1.0f };
GLfloat L2_DiffuseLight[] = { L2_DiffuseLight1, L2_DiffuseLight2, L2_DiffuseLight3, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };


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

bool L1_switch = false;
bool L2_switch = false;

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
		glTranslatef(0, -200, 200);
		glScalef(1.0, 0.1, 1.0);
		glutSolidCube(500);
		glPopMatrix();
	}

}flr;
class Ball {
public:
	GLfloat btransX;
	GLfloat btransZ = 100;
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
		glutSolidSphere(25, 30, 30);
		glPopMatrix();
	}

	void collision() {

	}
}ball;

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
		////////////밑에 크레인 
		glTranslatef(ctransX, -100, 100);
		glRotatef(angleY, 0, 1, 0);
		glutSolidCube(50);
		///////위에 크레인 
		glPushMatrix();
		if (rotate_mY == true)glRotatef(angle_mY, 0, 1, 0);
		if (rotate_mX == true)glRotatef(angle_mX, 1, 0, 0);
		glTranslatef(0, 40, 0);
		glColor3f(0, 1, 0);
		glScalef(0.5, 1.0, 0.5);
		glutSolidCube(30);
		///////작은 사각형
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
		if (dir == Dir::right) { ctransX += 10; if (ctransX > 150)dir = Dir::left; }
		else if (dir == Dir::left) { ctransX -= 10; if (ctransX < -150) dir = Dir::right; }
	}

	void collision(Ball ball)
	{
		// 중점 사이의 거리 구하기
		float d = sqrt(((float)(ball.btransX - ctransX)*(ball.btransX - ctransX))
			+ (float)((ball.btransZ - 100)*(ball.btransZ - 100)));
		if (25 >= d)
		{
			if (dir == Dir::right) dir = Dir::left;
			else if (dir == Dir::left) dir = Dir::right;
		}
	}

}crain;
class Rectangle_Tree
{
public:
	GLfloat rotateY;
public:
	void draw() {

		glPushMatrix();
		glColor3f(0.2f, 0.3f, 0.4f);
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
		glutSolidSphere(size, 20, 10);
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
		glColor3f(1.0f, 0.8f, 0.04f);
		glTranslatef(150, -100, 100);
		glScalef(1.0f, 5.0f, 1.0f);
		glutSolidCube(30);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.4f);
		glRotatef(90, 1, 0, 0);
		glTranslatef(140, 80, moveY);
		glutSolidTorus(10, 40, 20, 20);
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
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(-150, -150, 50);
		glRotatef(-90, 1, 0, 0);
		glScalef(1.1 - scale, 1.1 - scale, 1.1 - scale);
		glutSolidCone(25, 40, 20, 20);
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

class Light_Cone
{
public:
	float scale = 1.0f;
	int dir = 0;
	
public:
	void draw() {
		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(-400, 200, 500);
		glRotatef(90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(400, 200, 500);
		glRotatef(-90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix();
	}
}L_Cone;

class Pyramid {

public:
	void draw() {
		glPushMatrix();
		glBegin(GL_TRIANGLES);	//앞
		glNormal3f(0.0, 1.0, 0.0);
		glColor3f(0.3f, 0.3f, 0.2f);
		glVertex3f(0, -130, 150);   //1
		glVertex3f(50, -200, 100);   //2
		glVertex3f(-50, -200, 100);   //3
		glEnd();

		glBegin(GL_TRIANGLES);	// 뒤
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0, -130, 150);   //1
		glVertex3f(-50, -200, 200);   //4
		glVertex3f(50, -200, 200);   //5
		glEnd();

		glBegin(GL_TRIANGLES);	//옆
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0, -130, 150);   //1
		glVertex3f(50, -200, 100);   //5
		glVertex3f(50, -200, 200);   //5
		glEnd();

		glBegin(GL_TRIANGLES);	//옆
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0, -130, 150);   //1
		glVertex3f(-50, -200, 100);   //5
		glVertex3f(-50, -200, 200);   //5
		glEnd();
	glPopMatrix();
	}
}pyramid;

class Smallplanet {
private:
	int x = 0;
	int z = 0;
	int r = 0;
	int moveR = 20;
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
}small[2];
void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);

void main()
{
	// 윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Points Drawing");

	// 상태 변수 초기화 함수
	SetupRC();

	// 필요한 콜백 함수 설정
	glutDisplayFunc(DrawScene); // 출력 콜백 함수
	glutReshapeFunc(Reshape); // 다시 그리기 콜백 함수
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(100, TimerFunction, 1); // 타이머 콜백 함수
	glutMainLoop(); // 이벤트 루프 실행하기
}

// 초기화 함수 (Optional): 필요한 경우에 작성, 초기화해야 할 변수들이 많을 때는 만드는 것이 유리
void SetupRC() {
	// 필요한 변수들, 좌표값 등의 초기화
	// 기능 설정 초기화
	small[1].setR(0);
	small[1].setmoveR(15);
	small[1].setspeed(5);
	small[1].setcolor(1.0f);
	small[1].setSize(2);
}

//-------------------------------------------------------------------------------------------------------------------------
// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);      // 조명 활성화
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	if (L1_switch)
	{
		glEnable(GL_LIGHT0);
		glPushMatrix(); //Save
		glTranslatef(-400, 200, -500);
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
		glTranslatef(400, 200, -500);
		Light2();
		glPopMatrix();
	}
	else
	{
		glDisable(GL_LIGHT1);
	}

		
	
	UpdateCam();
	glPushMatrix();
	//glTranslatef(transX, transY, transZ);
	// 필요한 변환 적용
	flr.draw();											// glPushMatrix 함수를 호출하여 기존의 좌표 시스템을 저장
	r_tree.draw();
	s_tree.draw();												// 필요한 경우 행렬 초기화 ( glLoadIdentity ( ); 

	
	torus.draw();
	cone.draw();
	L_Cone.draw();
	pyramid.draw();
	small[0].draw();
	glPushMatrix();
	glTranslatef(small[0].getX(), 0, small[0].getZ());
	small[1].draw();
	glPopMatrix();
	glPopMatrix();


	glutSwapBuffers(); // 결과 출력
}

// 다시그리기 콜백 함수
// 처음 윈도우를 열 때, 윈도우 위치를 옮기거나 크기를 조절할 때 호출
// 뷰포트 설정, 투영 좌표계 설정, 관측 좌표 설정 등을 한다.
void Reshape(int w, int h)
{
	// 뷰포트 변환 설정: 출력 화면 결정
	glViewport(0, 0, w, h);
	// 클리핑 변환 설정: 출력하고자 하는 공간 결정
	// 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 600 / 400, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
	gluLookAt
	(
		0.0, 0.5, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}

// 필요한 콜백 함수 구현: 키보드 입력, 마우스 입력, 타이머 등
void Keyboard(unsigned char key, int x, int y)
{
	
	if (key == 'x') {
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
	else if (key == '1') {
		if (L1_switch == true) L1_switch = false;
		else if (L1_switch == false)L1_switch = true;
	}
	else if (key == '2') {
		if (L2_switch == true) L2_switch = false;
		else if (L2_switch == false)L2_switch = true;
	}
	else if (key == 'a') {
		L1_Ambient += 0.1f;
		L1_Ambient2 += 0.1f;
		L1_Ambient3 += 0.1f;
	}
	else if (key == 'A') {
		L1_Ambient -= 0.1f;
		L1_Ambient2 -= 0.1f;
		L1_Ambient3 -= 0.1f;
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
	else if (key == 's') {
		czRotate -= 1;
	}
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
}

void TimerFunction(int value)
{
	crain.move();
	crain.collision(ball);
	cone.move();
	door.open();
	r_tree.move();
	s_tree.move();
	torus.move();
	small[0].move();
	small[1].move();
	angle -= 10;
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {
	glutPostRedisplay();
}

void UpdateCam() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 600 / 400, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장

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