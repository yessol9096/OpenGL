#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>

#define PI 3.141592

int culling = 1;
// 조명
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
		glPopMatrix();	// 오른쪽 앞

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(lightpos2[0], lightpos2[1], lightpos2[2]);
		glRotatef(-90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix();	// 왼쪽 앞

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(lightpos3[0], lightpos3[1], lightpos3[2]);
		glRotatef(-90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix(); //  왼쪽 뒤

		glPushMatrix();
		glColor3f(0.5f, 0.0f, 0.4f);
		glTranslatef(lightpos4[0], lightpos4[1], lightpos4[2]);
		glRotatef(90, 0, 1, 0);
		glScalef(scale, scale, scale);
		glutSolidCone(25, 40, 20, 20);
		glPopMatrix(); // 오른쪽 뒤
	}
}L_Cone;

class Pyramid {

public:
	void draw() {
		glPushMatrix();
		glBegin(GL_TRIANGLES);	//앞
		glColor3f(0.3f, 0.3f, 0.2f);
		if(vector_switch)
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0, -50, 150);   //1
		glVertex3f(50, -200, 100);   //2
		glVertex3f(-50, -200, 100);   //3
		glEnd();

		glBegin(GL_TRIANGLES);	// 뒤
		if (vector_switch)
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0, -50, 150);   //1
		glVertex3f(-50, -200, 200);   //4
		glVertex3f(50, -200, 200);   //5
		glEnd();

		glBegin(GL_TRIANGLES);	//옆
		if (vector_switch)
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0, -50, 150);   //1
		glVertex3f(50, -200, 100);   //5
		glVertex3f(50, -200, 200);   //5
		glEnd();

		glBegin(GL_TRIANGLES);	//옆
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
// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);      // 조명 활성화
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
	// 필요한 변환 적용
	flr.draw();											// glPushMatrix 함수를 호출하여 기존의 좌표 시스템을 저장
	
	L_Cone.draw();

	//눈 . 
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
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
	gluLookAt
	(
		0.0, 25.0, -500.0,
		0.0, -1.0, 0.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}

// 필요한 콜백 함수 구현: 키보드 입력, 마우스 입력, 타이머 등
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
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
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
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
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