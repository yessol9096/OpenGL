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

bool rotate_mX = false;
bool rotate_mY = false;

bool rotate_eZ = false;
bool rotate_eX = false;

bool stop = false;
bool rotate = false;

float transX = 0.0;
float transY = 0.0;
float transZ = 0.0;
int random;

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
	GLfloat transX;
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
		glTranslatef(transX, -100, 100);
		glRotatef(angleY, 0, 1, 0);
			glutSolidCube(50);
			///////위에 크레인 
			glPushMatrix();
				if(rotate_mY == true)glRotatef(angle_mY, 0, 1, 0);
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
		if (dir == Dir::right) { transX += 10; if (transX > 150)dir = Dir::left; }
		else if (dir == Dir::left) { transX -= 10; if (transX < -150) dir = Dir::right; }
	}

}crain;

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
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	UpdateCam();
	glPushMatrix();
	glTranslatef(transX, transY, transZ);
	// 필요한 변환 적용
	flr.draw();											// glPushMatrix 함수를 호출하여 기존의 좌표 시스템을 저장
														// 필요한 경우 행렬 초기화 ( glLoadIdentity ( ); )
	crain.draw();													// 변환 적용: 이동, 회전, 신축 등 모델에 적용 할 변환 함수를 호출한다.

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
	if (key == 'y' ) {
		crain.angleY -= 5;
	}
	else if (key == 'Y') {
		crain.angleY += 5;
	}
	else if (key == 'a' ) {
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

	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
}

void TimerFunction(int value)
{
	crain.move();
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