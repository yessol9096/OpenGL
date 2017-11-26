#include <glut.h> 
#include <iostream>
#define PI 3.141592

void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
int num = 0;
int depth = 1;
GLdouble cyRotate = 0.5;
GLdouble cxRotate = 0.0;
GLdouble czRotate = 0.0;

GLfloat ctrlpoints[20][3] = { { 0,0,0 } };
void main()
{
	// 윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Points Drawing");
	glutMouseFunc(Mouse);
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

}

//-------------------------------------------------------------------------------------------------------------------------
// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	// 3차원 상의 제어점 설정
	GLfloat ctrlpoints[3][3][3] = { { { -4.0, 0.0, 4.0 },{ -2.0, 4.0, 4.0 },{ 4.0, 0.0, 4.0 } },
	{ { -4.0, 0.0, 0.0 },{ -2.0, 4.0, 0.0 },{ 4.0, 0.0, 0.0 } },
	{ { -4.0, 0.0, -4.0 },{ -2.0, 4.0, -4.0 },{ 4.0, 0.0, -4.0 } } };
	// 곡면 제어점 설정
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);
	glPointSize(2.0); glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints[i][j]);
	glEnd();

	glutSwapBuffers(); // 결과 출력
}

void Reshape(int w, int h)
{
	// 뷰포트 변환 설정: 출력 화면 결정
	//glViewport(0, 0, w, h);
	// 클리핑 변환 설정: 출력하고자 하는 공간 결정
	// 아래 3줄은 투영을 설정하는 함수
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	// 원근 투영을 사용하는 경우:
	//gluPerspective(60.0, 600 / 400, 1.0, 1000.0);
	//glTranslatef(0.0, 0.0, 0.0);
	glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장


	//gluLookAt
	//(
	//	0.0, 0.5, 0.0,
	//	0.0, 0.0, 1.0,
	//	0.0, 1.0, 0.0
	//);
	glMatrixMode(GL_MODELVIEW);

}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd' || key == 'D') {
		if (depth == 0)depth = 1;
		else if (depth == 1)depth = 0;
	}
	else if (key == 'r' || key == 'R') {
		num = 0;
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
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = num; i < 22; ++i)
		{
			ctrlpoints[i][0] = x;
			ctrlpoints[i][1] = y;
			ctrlpoints[i][2] = 0;
		}
		++num;
		if (num > 20) num = 0;
	}

}