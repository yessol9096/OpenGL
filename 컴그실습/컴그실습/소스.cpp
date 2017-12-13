#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>

bool m_plane = false;
float viewX = 0;
float viewY = 0;
float viewZ = 0;

float LineX = 0;
float LineY = 0;
float LineZ = 0;
float rotateY = 0;
int point_Num = 30;
GLfloat ctrlpoints[30][3];

int spline_num = 1;
int num = 0;
int i = 0;
void vCalcMove();
bool collision();

typedef struct MovePlane {

	float moveX[100];

	float moveY[100];

	float moveZ[100];

}MovePlane;

MovePlane move_plane[30];

class Plane {
public:
	int x = 100;
	int y = 150;
	int z = -100;
	float move1 = 0;
	float moveR = 120;
	int speed = 10;
	int r = 120;

	void draw() {
		glColor3f(0, 0, 1);
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(90, 0, 1, 0);
		{
			glPushMatrix();	// 날개
			glColor3f(1, 1, 0);
			glTranslatef(0, -5, 0);
			glScalef(8.0, 0.5, 3.0);
			glutSolidCube(10);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0, 0, 1, 0.5);	// 몸통
			glScalef(1.0, 1.0, 2.0);
			glutSolidCube(25);
			glPopMatrix();

			glPushMatrix();	// 꼬리
			glColor3f(1, 0, 1);
			glTranslatef(0, 0, 25);
			glScalef(1.0, 1.0, 4.0);
			glutSolidCube(5);
			glTranslatef(0, 5, 1.5);
			glScalef(0.5, 2.0, 0.25);
			glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();	// 프로펠러
			glColor3f(1, 0, 0);
			glTranslatef(0, 0, -28);
			glRotatef(move1, 0, 0, 1);
			glScalef(4.0, 1.0, 1.0);
			glutSolidCube(5);

			glPopMatrix();

			glPushMatrix();	// 프로펠러
			glColor3f(0, 1, 1);
			glTranslatef(0, 0, -28);
			glRotatef(move1, 0, 0, 1);
			glScalef(1.0, 4.0, 1.0);
			glutSolidCube(5);

			glPopMatrix();

			glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0, 60, 0);
			glScalef(0.3, 0.7, 0.1);
			glutSolidCube(30);
			glPopMatrix();

			glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0, 40, 0);
			glScalef(0.3, 0.7, 0.1);
			glBegin(GL_TRIANGLES);	//앞
			glVertex3f(0, 0, 0);   //1
			glVertex3f(50, 20, 0);   //2
			glVertex3f(-50, 20, 0);   //3
			glEnd();
			glPopMatrix();
		}
		glPopMatrix();
	}


	void move()
	{
		x = move_plane[num].moveX[i];
		y = move_plane[num].moveY[i];
		z = move_plane[num].moveZ[i];
	}
	void prop_move()
	{
		move1 += speed;
	}
}plane;

class Map {
public:
	void draw()
	{
		glPushMatrix();

		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(150, 150, -150); // 1
		glVertex3f(-150, 150, -150); // 2
		glVertex3f(-150, -150, -150);  // 3
		glVertex3f(150, -150, -150); // 4	// 앞 
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-150, 150, 150); // 1
		glVertex3f(-150, 150, -150); // 2
		glVertex3f(-150, -150, -150);  // 3
		glVertex3f(-150, -150, 150); // 4	// 오른쪽옆
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(150, 150, 150); // 1
		glVertex3f(150, 150, -150); // 2
		glVertex3f(150, -150, -150);  // 3
		glVertex3f(150, -150, 150); // 4	// 왼쪽옆

		glBegin(GL_LINE_LOOP);
		glVertex3f(150, 150, 150); // 1
		glVertex3f(-150, 150, 150); // 2
		glVertex3f(-150, -150, 150);  // 3
		glVertex3f(150, -150, 150); // 4	// 뒤 
		glEnd();


		glPopMatrix();
	}
}MAP;

class Line {
public:
	void draw()
	{
		// X축 라인
		glPushMatrix();
		glLineWidth(2);            // 선 두께
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(10, 0x5555);
		glTranslatef(LineX, 0, LineZ);
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 300, 0); // 1
		glVertex3f(0, -300, 0); // 2
		glEnd();
		glPopMatrix();

		// Y축 라인
		glPushMatrix();
		glTranslatef(0, LineY, LineZ);
		glColor3f(0, 1, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(300, 0, 0); // 1
		glVertex3f(-300, 0, 0); // 2
		glEnd();
		glPopMatrix();

		// Z축 라인
		glPushMatrix();
		glTranslatef(LineX, LineY, 0);
		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 300); // 1
		glVertex3f(0, 0, -300); // 2
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glPopMatrix();
	}

}line;

class Star {
public:
	float red;
	float green;
	float blue;

	float x;
	float y;
	float z;

	bool shining = false;
	void draw() {
		glColor3f(red, green, blue);
		glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidSphere(1, 5, 5);
		glPopMatrix();
	}

	void Shining() {
		if (shining)
		{
			red += 0.3f;
			green += 0.3f;
			blue += 0.3f;
			shining = false;
		}
		else
		{
			red -= 0.3f;
			green -= 0.3f;
			blue -= 0.3f;
			shining = true;
		}
	}
}star[3500];


class Planet {
public:
	float x;
	float y;
	float z;

	float red;
	float green;
	float blue;
	float planet_ry = 0;
	float r;

	void draw()
	{
		glColor3f(red, green, blue);
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(planet_ry, 0, 1, 0);
		glutSolidSphere(r, 15, 20);
		glPopMatrix();
	}

	void move()
	{
		planet_ry += 10;
	}
}planet[20];

class House {
public:
	void draw()
	{
		glColor3f(0.960784, 0.960784, 0.862745);
		glutSolidCube(25);
		glBegin(GL_TRIANGLES);
		glVertex3f(12.5, 12.5, -12.5);
		glVertex3f(-12.5, 12.5, -12.5);
		glVertex3f(0, 30, -12.5);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(12.5, 12.5, 12.5);
		glVertex3f(-12.5, 12.5, 12.5);
		glVertex3f(0, 30, 12.5);
		glEnd();

		glPushMatrix();
		glColor3f(0.823529, 0.411765, 0.117647);
		glTranslatef(0, -3, -10);
		glScalef(0.5, 0.7, 0.3);
		glutSolidCube(30);
		glPopMatrix();
		// 지붕
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(10, 25, 0); glRotatef(40, 0, 0, 1);
		glScalef(0.4, 1, 1);
		glutSolidCube(30);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(-10, 25, 0); glRotatef(-40, 0, 0, 1);
		glScalef(0.4, 1, 1);
		glutSolidCube(30);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.8, 0.0, 0.0);
		glTranslatef(0, 40, 0);
		glScalef(0.5, 0.2, 1);
		glutSolidCube(30);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0, 80, 0);
		glScalef(0.3, 0.7, 0.1);
		glutSolidCube(30);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0, 60, 0);
		glScalef(0.3, 0.7, 0.1);
		glBegin(GL_TRIANGLES);	//앞
		glVertex3f(0, 0, 0);   //1
		glVertex3f(50, 20, 0);   //2
		glVertex3f(-50, 20, 0);   //3
		glEnd();
		glPopMatrix();
	}

}house;

class Tree {
public:
	float trans_X = 0;
	float trans_Y = 0;
	float trans_Z = 0;
	float trans_R = 0;
	float rotate = 0;
	float r_X = 0;
	float r_Y = 0;
	float r_Z = 0;
	float p_rY = 0;
	void draw()
	{
		glPushMatrix();	// 뿌리
		glTranslatef(trans_X, trans_Y, trans_Z);
		glRotatef(p_rY, 0, 1, 0);
		glRotatef(rotate, r_X, r_Y, r_Z);
		glTranslatef(0, trans_R, 0);

		glScalef(0.2, 0.2, 0.2);
		glPushMatrix();	// 뿌리
		glColor3f(0.960784, 0.860784, 0.862745);
		glTranslatef(0, 0, 0);
		glScalef(0.5, 2.0, 0.5);
		glutSolidCube(25);
		glPopMatrix();

		glPushMatrix();	// 잎사귀
		glColor3f(0.419608, 0.556863, 0.137255);
		glTranslatef(0, 10, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(20, 40, 20, 20);
		glPopMatrix();
		glPushMatrix();	// 잎사귀
		glColor3f(0.196078, 0.803922, 0.196078);
		glTranslatef(0, 20, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(20, 40, 20, 20);
		glPopMatrix();
		glEnd();
		glPopMatrix();
	}
}tree[20][12];

void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);
void Mouse(int x, int y);

void main()
{
	// 윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Points Drawing");

	// 상태 변수 초기화 함수
	SetupRC();

	glutMotionFunc(Mouse);
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

	for (int i = 0; i < 3500; ++i)
	{
		star[i].red = rand() % 10 * 0.1;
		star[i].green = rand() % 10 * 0.1;
		star[i].blue = rand() % 10 * 0.1;
		star[i].x = -800 + rand() % 1600;
		star[i].y = -800 + rand() % 1600;
		star[i].z = -150 + rand() % 300;
	}
	// 시작별
	planet[0].red = 1;	planet[0].green = 0.713725;	planet[0].blue = 0.756863;
	planet[0].r = 40;
	planet[0].x = 100;	planet[0].y = 100; planet[0].z = -100;

	// 목표별
	planet[17].red = rand() % 12 * 0.1;	planet[17].green = rand() % 12 * 0.1;	planet[17].blue = rand() % 12 * 0.1;
	planet[17].r = 40;
	planet[17].x = -100;	planet[17].y = -100; planet[17].z = 100;

	for (int i = 1; i < 16; ++i)
	{
		planet[i].red = rand() % 1000 * 0.001;	planet[i].green = rand() % 1000 * 0.001;	planet[i].blue = rand() % 1000 * 0.001;
		planet[i].r = 16 + rand() % 20;
	}
	planet[1].x = 10;
	planet[1].y = 80;
	planet[1].z = -100;

	planet[2].x = 40;
	planet[2].y = -100;
	planet[2].z = 50;

	planet[3].x = 80;
	planet[3].y = 20;
	planet[3].z = 40;

	planet[4].x = 80;
	planet[4].y = -40;
	planet[4].z = 100;

	planet[5].x = 70;
	planet[5].y = -110;
	planet[5].z = -110;

	planet[6].x = 70;
	planet[6].y = -110;
	planet[6].z = 110;

	planet[7].x = -110;
	planet[7].y = 110;
	planet[7].z = 110;

	planet[8].x = 120;
	planet[8].y = -110;
	planet[8].z = 110;

	planet[9].x = -40;
	planet[9].y = -110;
	planet[9].z = 10;

	planet[10].x = -120;
	planet[10].y = -110;
	planet[10].z = -120;

	planet[11].x = -100;
	planet[11].y = 90;
	planet[11].z = -120;

	planet[12].x = 70;
	planet[12].y = 110;
	planet[12].z = 110;

	planet[13].x = -70;
	planet[13].y = 110;
	planet[13].z = 0;

	planet[14].x = 100;
	planet[14].y = -10;
	planet[14].z = -80;

	planet[15].x = -120;
	planet[15].y = -40;
	planet[15].z = -100;

	planet[16].x = 120;
	planet[16].y = -40;
	planet[16].z = -100;

	ctrlpoints[0][0] = 100; ctrlpoints[0][1] = 150; ctrlpoints[0][2] = -100;

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			tree[i][j].trans_X = planet[i].x;
			tree[i][j].trans_Y = planet[i].y;
			tree[i][j].trans_Z = planet[i].z;
			tree[i][j].trans_R = planet[i].r;
			tree[i][j].rotate = j * 60;
			if (j < 6)
			{
				tree[i][j].r_X = 1;
				tree[i][j].r_Y = 0;
			}
			else
			{
				tree[i][j].r_X = 0;
				tree[i][j].r_Z = 1;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------
// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glPushMatrix();
	gluLookAt
	(
		0.0, 25.0, -500.0,
		viewX, viewY, -1.0,
		0.0, 1.0, 0.0
	);
	glRotatef(rotateY, 0, 1, 0);

	for (int i = 0; i < 3500; ++i)
	{
		star[i].draw();
	}

	for (int i = 0; i < 18; ++i)
		planet[i].draw();
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			tree[i][j].p_rY = planet[i].planet_ry;
			tree[i][j].draw();
		}
	}

	glPushMatrix();
	glTranslatef(-100, -50, 100);
	glScalef(1.2, 1, 1);
	house.draw();
	glPopMatrix();
	plane.draw();
	if (i >= 100) {

		i = 0;

		num += 1;

		if (num >= 30 - 2) {

			num = 0;

			glLoadIdentity();

		}
	}
	MAP.draw();
	line.draw();

	if (spline_num > 1)
	{
		for (int i = 0; i < spline_num; i += 3)
		{
			int n = spline_num;
			if (spline_num > 3) n = 4;
			glColor3f(1.0f, 1.0f, 1.0f);
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, n, &ctrlpoints[i][0]);
			glEnable(GL_MAP1_VERTEX_3);
			glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔
			glEvalMesh1(GL_LINE, 0, 10); // 선분으로 나눈 부분 0~10까지 선으로 그림
			glDisable(GL_MAP1_VERTEX_3);
		}
	}
	// 제어점에 점을 그린다.

	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < spline_num; ++i)
	{
		glPushMatrix();
		glTranslatef(ctrlpoints[i][0], ctrlpoints[i][1], ctrlpoints[i][2]);
		glutSolidCube(5);
		glPopMatrix();
	}
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
	//gluLookAt
	//(
	//	0.0, 25.0, -500.0,
	//	viewX, viewY, -1.0,
	//	0.0, 1.0, 0.0
	//);
	glMatrixMode(GL_MODELVIEW);
}

// 필요한 콜백 함수 구현: 키보드 입력, 마우스 입력, 타이머 등
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A')			rotateY += 10;
	else if (key == 'd' || key == 'D')		rotateY -= 10;

	else if (key == 'x' && LineX < 150)		LineX += 5;
	else if (key == 'X' && LineX > -150)	LineX -= 5;

	else if (key == 'y' && LineY < 150)		LineY += 5;
	else if (key == 'Y'&& LineY > -150)		LineY -= 5;

	else if (key == 'z' && LineZ < 150)		LineZ += 5;
	else if (key == 'Z'&& LineZ > -150)		LineZ -= 5;

	else if (key == 'Q' || key == 'q')		exit(0);
	if (key == 'p' || key == 'P')
	{
		if (collision())
		{
			for (int i = spline_num; i < point_Num; ++i)
			{
				ctrlpoints[i][0] = LineX;
				ctrlpoints[i][1] = LineY;
				ctrlpoints[i][2] = LineZ;
			}
			++spline_num;
			//if (spline_num > 20) spline_num = 0;
		}
	}

	if (key == 's')
	{
		if (m_plane == false)
		{
			m_plane = true;
		}
		else
			m_plane = false;
	}

	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
}


void TimerFunction(int value)
{
	for (int i = 0; i < 3500; ++i)
	{
		star[i].Shining();
	}

	for (int i = 0; i < 16; ++i)
	{
		if (i % 3 == 0) planet[i].move();
	}

	plane.prop_move();
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {
	glutPostRedisplay();
}

void Mouse(int x, int y)
{
	glutPostRedisplay();
}

bool collision()
{
	float c_X;
	float c_Y;
	float c_Z;
	for (int i = 0; i < 18; ++i)
	{
		c_X = abs(planet[i].x - LineX);
		c_Y = abs(planet[i].y - LineY);
		c_Z = abs(planet[i].z - LineZ);
		if (sqrt((c_X*c_X) + (c_Y*c_Y) + (c_Z*c_Z)) < planet[i].r)
		{
			return false;
			break;
		}
	}

	return true;

}
