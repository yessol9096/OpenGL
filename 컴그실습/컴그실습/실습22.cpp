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
			glPushMatrix();	// 날개
			glColor3f(1, 1, 0);
			glTranslatef(0, -5, 0);
			glScalef(8.0, 0.5, 3.0);
			glutSolidCube(10);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0, 0, 1,0.5);	// 몸통
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
	plane.draw();
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

	else if (key == 'p') {
		plane.speed = 10;
	}
	else if (key == 'm') {
		plane.speed = -10;
	}
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
}

void TimerFunction(int value)
{
	plane.move();
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