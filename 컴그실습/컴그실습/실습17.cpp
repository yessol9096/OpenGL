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
	// 윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(500, 100);
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
// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
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
		0.0, 0.1, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}
bool flag = false;
// 필요한 콜백 함수 구현: 키보드 입력, 마우스 입력, 타이머 등
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
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
}

void TimerFunction(int value)
{
	small[0].move(); small[1].move();
	small[2].move(); small[3].move();
	small[4].move(); small[5].move();
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