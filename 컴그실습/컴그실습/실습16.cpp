#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <ctime>
#define PI 3.141592

enum class Fig {
	sphere	// 구 
	,cube	//직육면체
	,cone	// 원뿔
	,teapot // 주전자
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
													// 필요한 변환 적용
	flr.draw();											// glPushMatrix 함수를 호출하여 기존의 좌표 시스템을 저장
	solid.draw();													// 필요한 경우 행렬 초기화 ( glLoadIdentity ( ); )
	wire.draw();													// 변환 적용: 이동, 회전, 신축 등 모델에 적용 할 변환 함수를 호출한다.
																	// 변환이 끝난 후에는 원래의 좌표시스템을 다시 저장하기 위하여 glPopMatrix 함수 호출
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
		0.0, 0.3, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}

// 필요한 콜백 함수 구현: 키보드 입력, 마우스 입력, 타이머 등
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
	
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
}

void TimerFunction(int value)
{
	angle -= 10;
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {
	glutPostRedisplay();
}