#include <glut.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);

void Mouse(int button, int state, int x, int y);
void TimerFunc(int value);
int num = 0;

class Figure {
public:
	float size = 10;
	int angle = 0;
	int x;
	int y;
	int figure;
	bool drawing = false;
public:
	void draw()
	{
		if (drawing == true)
		{
			glPushMatrix();

			glTranslatef(x, y, 0);
			glRotatef(angle, 0, 1, 0);
			if (figure == 0) glutWireCube(size);
			else if (figure == 1) glutWireSphere(size, 50, 50);
			else if (figure == 2) glutWireTorus(size / 2, size, 50, 50);
			else if (figure == 3)glutWireTeapot(size);
			glPopMatrix();
		}
	}

	void move1()
	{
		if (drawing == true)
		{
			angle += 10;
			size += 50;
			if (size > 500) { drawing = false; size = 10; }
		}
	}
}fig[20];
void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름)
	glutMouseFunc(Mouse);
	glutTimerFunc(300, TimerFunc, 1);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);

	
	glutReshapeFunc(reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glColor4f(0, 0, 0, 0);
	
	for (int i = 0; i < num; ++i)
		fig[i].draw();
	
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800.0, 0.0, 600.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned)time(NULL));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		fig[num].x = x;
		fig[num].y = 600-y;
		fig[num].figure = rand() % 4;
		fig[num].drawing = true;
		std::cout << x << ", " << fig[num].x << "num:" << num << std::endl;
		num++;
		if (num > 19) num = 0;
	}
}

void TimerFunc(int value)
{
	for (int i = 0; i < num; ++i)
		fig[i].move1();

	glutPostRedisplay();
	glutTimerFunc(300, TimerFunc, value);
};


void Keyboard(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q') {
		exit(0);
	}
	glutPostRedisplay();
}