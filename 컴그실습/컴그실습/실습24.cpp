#include <glut.h> 
#include <iostream>
#define PI 3.141592


void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);
void UpdateCam();

int depth = 1;
GLdouble cyRotate = 0.5;
GLdouble cxRotate = 0.0;
GLdouble czRotate = 0.0;

class Torus
{
public:
	GLfloat moveY;
	int dir = 0;
	int num;
	float angle;
	float height = 20;
	float ground = -50;
	float transX;
	float transY;
	float transZ = -100;
	bool Move = false;
public:
	void draw() {
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			glRotatef(90, 1, 0, 0);
			glTranslatef(transX, transY, transZ);
			glutWireTorus(10, 30, 20, 20);
			glTranslatef(-transX, -transY, -transZ);
			glRotatef(-90, 1, 0, 0);
		glPopMatrix();
	}

	void move()
	{
		if (transZ < height)
		{
			transX = 10 * cos(angle);
			transY = 10 * sin(angle);
			angle += 5;
			transZ += 5;
		}
	}

	void down()
	{
		height = (num * 20) + 30;
	}

	void reset(int i)
	{
		num = -i;
		transZ = -150 * i;
		angle = 0;
	}
}torus[7];

void main()
{
	// 윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
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

void SetupRC() {
	for (int i = 0; i < 7; ++i)
	{
		torus[i].num = -i;
		torus[i].transZ = -150 * i;
		torus[i].angle = 0;
	}
}
int rotateX = 0;
//-------------------------------------------------------------------------------------------------------------------------
// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	UpdateCam();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기


	glPushMatrix();
	//glEnable(GL_CULL_FACE);	// 컬링제거

	if (depth == 1) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}

	glPushMatrix();
	glColor3f(0.5, 0.5, 0);
	glTranslatef(0, -50, 0);
	glScalef(1.0, 0.05, 1.0);
	glutSolidCube(250);	// 바닥 
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.1, 5.0, 0.1);
	glutSolidCube(50);	// 기둥
	glPopMatrix();
	

	for (int i = 0; i < 7 ; i++)
	{
			torus[i].draw();
	}
	

	glPopMatrix();
	//glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); // 결과 출력
}

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
	glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장


	gluLookAt
	(
		0.0, 0.5, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);

}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd' || key == 'D') {
		if (depth == 0)depth = 1;
		else if (depth == 1)depth = 0;
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
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	for (int i = 0; i < 7; i++)
	{
			torus[i].move();
			torus[i].down();
	}
	if (torus[6].transZ == torus[6].height)
	{
		for (int i = 0; i < 7; i++)torus[i].reset(i);
	}
	glutPostRedisplay();
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

